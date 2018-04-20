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
		if ((abs(sortedValues[i]-sortedValues[i + 1])>0.5) & (sortedTargets[i] != sortedTargets[i + 1])) {
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
// Get a list of unique values of val
vector<double> uniqueValues(vector<double> val) {
	sort(val.begin(), val.end());
	val.erase(unique(val.begin(),val.end()), val.end());
	//val.erase(unique(val.begin(), val.end(), [](double x, double y) { return (int(x) == int(y)); }), val.end());
	return val;
}

// Return the most frequent values of val
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

// Return the percentage frequency of a value
double computeFrequency(vector<double> cluster, vector<double> uniqueTargets, double mostFrequentVal) {
	int index;
	vector<double> frequency;
	int* Count = new int[uniqueTargets.size()]{ 0 };

	for (int i = 0; i < cluster.size(); ++i) {
		for (int j = 0; j < uniqueTargets.size(); ++j) {
			Count[j] = int(count(cluster.begin(), cluster.end(), uniqueTargets[j]));
		}
	}

	for (int i = 0; i < uniqueTargets.size(); ++i) {
		frequency.push_back((double)(Count[i] / cluster.size()));
		if (uniqueTargets[i] == mostFrequentVal) { index = i; }
	}
	return frequency[index];
}

//Calculate the entropy
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
Tree::Tree(double p) : StopCriteria(p) { Depth = 0; Leaf = false; }

void Tree::setDecisionNode(int& inputDecisionNode) { DecisionNode = inputDecisionNode; }

void Tree::setBranch(string& inputBranch) { Branch = inputBranch; }

void Tree::addChild(Tree* inputChild) { Child.push_back(inputChild); }

void Tree::setLeaf(bool inputLeaf) { Leaf = inputLeaf; }

void Tree::setDepth(int& inputDepth) { Depth = inputDepth; }

int Tree::getDecisionNode() const { return DecisionNode; }

string Tree::getBranch() const { return Branch; }

vector<Tree*> Tree::getChild() const { return Child; }

bool Tree::isLeaf() const { return Leaf; }

int Tree::getDepth() const { return Depth; }

double Tree::getStopCriteria() const { return StopCriteria; }

Tree* Tree::buildTree(Tree* tree, vector<Node> dataSet, int depth, vector<int> attributes) {

	vector<double> cluster = getTargets(dataSet);
	vector<double> uniqueTargets = uniqueValues(cluster);
	int leaf;
	int mostFrequentVal = int(frequentValues(cluster));
	double frequency = computeFrequency(cluster, uniqueTargets, mostFrequentVal);
	
	//cout << "Build Tree Continue! Depth = " << depth << ", DataSet Size = " << dataSet.size() << endl;

	// DecisionNode here is Leaf Node
	if (uniqueTargets.size() == 1) {
		leaf = int(uniqueTargets[0]);
		tree->setDecisionNode(leaf);
		tree->setLeaf(true);
		tree->setDepth(depth);
		//cout << "Depth: " << depth << endl;
		//cout << "Unique Leaf: " << leaf << '\n' << endl;
		return tree;
	}
	// Stop if reach 95% similarity
	else if (frequency >= tree->getStopCriteria()) {
		leaf = mostFrequentVal;
		tree->setDecisionNode(leaf);
		tree->setLeaf(true);
		tree->setDepth(depth);
		//cout << "Depth: " << depth << endl;
		//cout << "95% Leaf: " << leaf << '\n' << endl;
		return tree;
	}
	//Stop cluster's size <= 15
	else if (cluster.size() <= 15) {
		leaf = mostFrequentVal;
		tree->setDecisionNode(leaf);
		tree->setLeaf(true);
		tree->setDepth(depth);
		//cout << "Depth: " << depth << endl;
		//cout << "Size<=10 Leaf: " << leaf << '\n' << endl;
		return tree;
	}
	// Stop if all attributes are used
	else if (attributes.size() == 0) {
		leaf = mostFrequentVal;
		tree->setDecisionNode(leaf);
		tree->setLeaf(true);
		tree->setDepth(depth);
		//cout << "Depth: " << depth << endl;
		//cout << "No Attributes Leaf: " << leaf << '\n' << endl;
		return tree;
	}

	// Determine attribute and cutoff point for the attribute with max info gain
	double infoGain = 0, gainRatio = 0;
	double tempGainRatio, tempInfoGain, maxCutOff;
	int maxAttributeIndex = 0;
	for (int i = 0; i < attributes.size(); ++i) {
		vector<double> cutOff = getCutOffs(dataSet, i);
		//cout << "AttributeUsed:" << attributes[i] << endl;

		for (int j = 0; j < cutOff.size(); ++j) {
			tempInfoGain = computeInfoGain(dataSet, attributes[i], cutOff[j]);
			if (tempInfoGain > infoGain) {
				infoGain = tempInfoGain;
				maxCutOff = cutOff[j];
			}
		}

		if ((cutOff.size() != 0) && (infoGain != 0)) {
			tempGainRatio = computeGainRatio(dataSet, attributes[i], maxCutOff);
			if (tempGainRatio > gainRatio) {
				gainRatio = tempGainRatio;
				maxAttributeIndex = attributes[i];
			}
		}
	}

	// Stop if no additional info gain
	if (gainRatio == 0) {
		leaf = mostFrequentVal;
		tree->setDecisionNode(leaf);
		tree->setLeaf(true);
		tree->setDepth(depth);
		//cout << "Depth: " << depth << endl;
		//cout << "No InfoGain: " << leaf << '\n' << endl;
		return tree;
	}

	// Construct the node and branches
	tree->setDepth(depth);
	tree->setDecisionNode(maxAttributeIndex);
	auto ita = find(attributes.begin(), attributes.end(), maxAttributeIndex);
	auto it = attributes.erase(ita);
	vector<string> values = { "lowerValue","upperValue" };
	string leftBranch = "< " + to_string(maxCutOff);
	string rightBranch = "> " + to_string(maxCutOff);
	vector<string> branches = { leftBranch,rightBranch };

	// Construct dataSet for each branches
	map<string, vector<Node>> parts;
	vector<Node> row1, row2;
	for (int i = 0; i < dataSet.size(); ++i) {
		double attributeValue = dataSet[i].getFactor(maxAttributeIndex);
		if (attributeValue < maxCutOff) { row1.push_back(dataSet[i]); }
		else { row2.push_back(dataSet[i]); }
	}
	//Try to release memory
	dataSet.clear();
	dataSet.shrink_to_fit();

	parts["lowerValue"] = row1;
	parts["upperValue"] = row2;

	//cout << "Depth: " << depth << endl;
	//cout << "MaxCutOff: " << maxCutOff << endl;
	//cout << "MaxAttribute: " << maxAttributeIndex << '\n' << endl;

	// Build the tree
	for (int i = 0; i < branches.size(); ++i) {
		Tree* newTree = new Tree(tree->getStopCriteria());
		newTree->setBranch(branches[i]);
		vector<Node> dataSetRemain = parts[values[i]];

		if(dataSetRemain.size() != 0){
			buildTree(newTree, dataSetRemain, depth + 1,attributes);
			tree->addChild(newTree);
		}
	}

	return tree;
}

void Tree::display(vector<string> attributeName, int depth) {
	// when display, display the header instead of attribute index

	for (int i = 0; i < depth; ++i) { 
		std::cout << "\t"; 
	}
	if (this->Branch != "") {
		std::cout << this->Branch << endl;
		for (int i = 0; i < depth + 1; ++i) { 
			std::cout << "\t";
		}
	}

	//string attribute = attributeName[this->DecisionNode];
	//std::cout << attribute << endl;
	if (this->isLeaf()) { cout << this->DecisionNode << "(Leaf Node)" << endl; }
	else { cout << this->DecisionNode << endl; }
	
	for (int i = 0; i < this->Child.size(); ++i) {
		(this->Child[i])->display(attributeName, depth + 1);
	}
}

int Tree::predictNode(Node point) {
	while (!isLeaf()) {
		int attributeIndex = getDecisionNode();
		double attributeVal = point.getFactor(attributeIndex);
		string branch = getChild()[0]->getBranch();
		double cutoff = stod(branch.substr(2));
		if (attributeVal < cutoff) { return (this->getChild()[0])->predictNode(point); }
		else if (attributeVal > cutoff) { return (this->getChild()[1])->predictNode(point); }
	}
	return this->getDecisionNode();
}

vector<int> Tree::predict(vector<Node> dataSet) {
	vector<int> result;

	for (int i = 0; i < dataSet.size(); ++i) {
		result.push_back(predictNode(dataSet[i]));
	}

	return result; 
}