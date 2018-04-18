#include <string>
#include <cmath>
#include <algorithm>
#include "DecisionTree.h"
using namespace std;



// DataSet Processor
vector<double> getTargets(vector<Node> dataSet) {
	vector<double> result3mo;
	for (int i = 0; i < dataSet.size(); ++i) {
		result3mo.push_back((double)(dataSet[i].getLabel()));
	}
	return result3mo;
}

vector<double> getAttributeValues(vector<Node> dataSet, int attributeIndex) {
	vector<double> values;
	for (int i = 0; i < dataSet.size(); ++i) {
		values.push_back(dataSet[i].getFactor(attributeIndex));
	}
	return values;
}

vector<double> sortAttributeValues(vector<Node> dataSet, int attributeIndex) {
	vector<double> values = getAttributeValues(dataSet, attributeIndex);
	sort(values.begin(), values.end());
	return values;
}

vector<double> sortTargetValues(vector<Node> dataSet, int attributeIndex) {
	vector<double> values = getAttributeValues(dataSet, attributeIndex);
	vector<double> targets = getTargets(dataSet);
	double temp;

	for (int i = 0; i < values.size() - 1; ++i) {
		for (int j = i + 1; j < values.size(); j++) {
			if ((values[i] - values[j]) > 1.e-8) {
				temp = values[i];
				values[i] = values[j];
				values[j] = temp;

				temp = targets[i];
				targets[i] = targets[j];
				targets[j] = temp;
			}
		}
	}
	return targets;
}

vector<double> getCutOffs(vector<Node> dataSet, int attributeIndex) {
	vector<double> cutOffs;
	vector < double > sortedValues = sortAttributeValues(dataSet, attributeIndex);
	vector < double > sortedTargets = sortTargetValues(dataSet, attributeIndex);
	for (int i = 0; i < sortedValues.size() - 1; i++) {
		//if ((sortedValues[i] != sortedValues[i + 1]) & (sortedTargets[i] != sortedTargets[i + 1])) {
		if ((abs(sortedValues[i]-sortedValues[i + 1])>1) & (sortedTargets[i] != sortedTargets[i + 1])) {
			cutOffs.push_back((sortedValues[i] + sortedValues[i + 1]) / 2.);
		}
	}
	return cutOffs;
}

map<string, vector<double>> getAttributeBisectParts(vector<Node> dataSet, int attributeIndex, double cutoff) {
	map <string, vector<double>> bisectParts;
	vector < double > sortedValues = sortAttributeValues(dataSet, attributeIndex);
	vector < double > sortedTargets = sortTargetValues(dataSet, attributeIndex);
	vector < double > row1, row2, row3, row4;
	for (int i = 0; i < sortedValues.size(); ++i) {
		if (sortedValues[i] < cutoff) {
			row1.push_back(sortedTargets[i]);
			row3.push_back(sortedValues[i]);
		}
		else {
			row2.push_back(sortedTargets[i]);
			row4.push_back(sortedValues[i]);
		}
	}
	bisectParts["Lower_Scores"] = row1;
	bisectParts["Upper_Scores"] = row2;
	bisectParts["Lower_Values"] = row3;
	bisectParts["Upper_Values"] = row4;
	return bisectParts;
}



// C4.5 Entrogy and Information Gain Calculations
vector<double> uniqueValues(vector<double> val) {
	sort(val.begin(), val.end());
	val.erase(unique(val.begin(),val.end()), val.end());
	//val.erase(unique(val.begin(), val.end(), [](double x, double y) { return (int(x) == int(y)); }), val.end());
	return val;
}

double frequentValues(vector<double> val) {
	vector<double> uniqueVal = uniqueValues(val);
	int* Count = new int[uniqueVal.size()]{ 0 };
	for (int i = 0; i < val.size(); i++) {
		for (int j = 0; j < uniqueVal.size(); j++) {
			Count[j] = int(count(val.begin(), val.end(), uniqueVal[j]));
		}
	}

	int maxCount = 0, maxIndex;
	for (int i = 0; i < uniqueVal.size(); i++) {
		if (Count[i] > maxCount) {
			maxCount = Count[i];
			maxIndex = i;
		}
	}
	return uniqueVal[maxIndex];
}

double computeEntropy(vector<double> values) {

	// get a list of unique values
	vector<double> valueRange = uniqueValues(values);

	double entropy = 0.;
	int* count = new int[valueRange.size()]{ 0 };
	if (valueRange.size() == 0) { return 0.; }
	else {
		for (int i = 0; i < values.size(); ++i) {
			for (int j = 0; j < valueRange.size(); ++j) {
				if (values[i] == valueRange[j]) { count[j] += 1; }
			}
		}
	}

	double tempP, tempEntropy;
	for (int j = 0; j < valueRange.size(); ++j) {
		tempP = (double)count[j] / (double)(values.size());
		tempEntropy = -tempP * log2(tempP);
		entropy += tempEntropy;
	}

	return entropy;
}

double computeAttributeEntropy(vector<Node> dataSet, int attributeIndex) {
	// get a vector of values associated with given attribute
	vector<double> values = getAttributeValues(dataSet, attributeIndex);
	return computeEntropy(values);
}

double computeInfoGain(vector<Node> dataSet, int attributeIndex, double cutOff) {
	double originalEntropy = 0., afterEntropy = 0., gainedEntropy = 0.;
	
	vector<double> targets = getTargets(dataSet);
	originalEntropy = computeEntropy(targets);
	
	map<string, vector<double>> parts = getAttributeBisectParts(dataSet, attributeIndex, cutOff);
	double lowerLen = (double)(parts["Lower_Scores"].size());
	double upperLen = (double)(parts["Upper_Scores"].size());
	double len = lowerLen + upperLen;
	afterEntropy = lowerLen / len * computeEntropy(parts["Lower_Scores"]) 
				   + upperLen / len * computeEntropy(parts["Upper_Scores"]);
	gainedEntropy = originalEntropy - afterEntropy;
	return gainedEntropy;
}

double computeGainRatio(vector<Node> dataSet, int attributeIndex, double cutOff) {
	double attributeEntropy = computeAttributeEntropy(dataSet, attributeIndex);
	double attributeInfoGain = computeInfoGain(dataSet, attributeIndex, cutOff);
	return (attributeInfoGain / attributeEntropy);
}



// Decision Tree
Tree::Tree(double p) : StopCriteria(p) { DecisionNode = 0; Branch = ""; }

void Tree::setDecisionNode(int& inputDecisionNode) { DecisionNode = inputDecisionNode; }

void Tree::setBranch(string& inputBranch) { Branch = inputBranch; }

void Tree::addChild(Tree* inputChild) { Child.push_back(inputChild); }

int Tree::getDecisionNode() const { return DecisionNode; }

string Tree::getBranch() const { return Branch; }

vector<Tree*> Tree::getChild() const { return Child; }

double Tree::getStopCriteria() const { return StopCriteria; }

Tree* Tree::buildTree(Tree* tree, vector<Node> dataSet) {	//attribute need to be taken off once used
	
	cout << "Build Tree Continue!" << endl;

	vector<double> cluster = getTargets(dataSet);
	vector<double> uniqueTargets = uniqueValues(cluster);
	int leaf;

	// DecisionNode here is Leaf Node
	if (uniqueTargets.size() == 1) {
		leaf = int(uniqueTargets[0]);
		tree->setDecisionNode(leaf);
		return tree;
	}

	//Stop cluster's size <= 10
	if(cluster.size() <= 10) {
		leaf = int(frequentValues(cluster));
		tree->setDecisionNode(leaf);
		return tree;
	}

	// Stop if reach 95% similarity
	int* Count = new int[uniqueTargets.size()]{ 0 };
	for (int i = 0; i < cluster.size(); ++i) {
		for (int j = 0; j < uniqueTargets.size(); ++j) {
			Count[j] = int(count(cluster.begin(), cluster.end(), uniqueTargets[j]));
		}
	}
	for (int i = 0; i < uniqueTargets.size(); ++i) {
		if ((Count[i] / cluster.size()) >= 0.95) {
			leaf = int(uniqueTargets[i]);
			tree->setDecisionNode(leaf);
			return tree;
		}
	}

	// Determine attribute and cutoff point for the attribute with max info gain
	double infoGain = 0, gainRatio = 0;
	double tempGainRatio, tempInfoGain, maxCutOff;
	int maxAttributeIndex = 0;
	int numAttribute = dataSet[0].getFactorNum();
	for (int i = 0; i < numAttribute; ++i) {
		// int attributeIndex = i;
		vector<double> cutOff = getCutOffs(dataSet, i);
		for (int j = 0; j < cutOff.size(); ++j) {
			tempInfoGain = computeInfoGain(dataSet, i, cutOff[j]);
			if (tempInfoGain > infoGain) {
				infoGain = tempInfoGain;
				maxCutOff = cutOff[j];
			}
		}

		tempGainRatio = computeGainRatio(dataSet, i, maxCutOff);
		if (tempGainRatio > gainRatio) {
			gainRatio = tempGainRatio;
			maxAttributeIndex = i;
		}
	}

	// Construct the node and branches
	tree->setDecisionNode(maxAttributeIndex);
	vector<string> values = { "lowerValue","upperValue" };
	string leftBranch = "< " + to_string(maxCutOff);
	string rightBranch = "< " + to_string(maxCutOff);
	vector<string> branches = { leftBranch,rightBranch };

	// Construct dataSet for each branches
	map<string, vector<Node>> parts;
	vector<Node> row1, row2;
	for (int i = 0; i < dataSet.size(); ++i) {
		double attributeValue = dataSet[i].getFactor(maxAttributeIndex);
		if (attributeValue < maxCutOff) { row1.push_back(dataSet[i]); }
		else { row2.push_back(dataSet[i]); }
	}
	parts["lowerValue"] = row1;
	parts["upperValue"] = row2;

	// Build the tree
	for (int i = 0; i < branches.size(); ++i) {
		Tree* newTree = new Tree(tree->getStopCriteria());
		newTree->setBranch(branches[i]);

		vector<Node> dataSetRemain = parts[values[i]];
		vector<double> cluster = getTargets(dataSetRemain);
		vector<double> newUniqueTargets = uniqueValues(cluster);

		if (newUniqueTargets.size() == 1) { 
			int leaf = int(newUniqueTargets[0]);
			newTree->setDecisionNode(leaf);
		}
		else {
			buildTree(newTree, dataSetRemain);
		}
		tree->addChild(newTree);
	}

	return tree;
}

void Tree::display(vector<string> attributeName, int depth) {
	// when display, display the header instead of attribute index
	for (int i = 0; i < depth; ++i) { std::cout << "\t"; }
	if (this->Branch != "") {
		std::cout << this->Branch << endl;
		//for (int i = 0; i < depth + 1; ++i) { std::cout << "\t";}
	}

	//string attribute = attributeName[this->DecisionNode];
	//std::cout << attribute << endl;
	cout << this->DecisionNode << endl;
	
	for (int i = 0; i < this->Child.size(); ++i) {
		(this->Child[i])->display(attributeName, depth + 1);
	}
}