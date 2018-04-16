#include <map>
#include <cmath>
#include <algorithm>
#include "DecisionTree.h"
using namespace std;

// DataSet Processor
vector<double> getTargets(vector<Node> dataSet) {
	vector<double> result3mo;
	for (int i = 0; i < dataSet.size(); ++i) {
		result3mo.push_back(double(dataSet[i].getLabel()));
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

map<string, vector<double>> getAttributeBisectParts(vector<Node> dataSet, int attributeIndex, double cutoff) {
	map <string, vector<double>> bisectParts;
	vector < double > SortedValues = sortAttributeValues(dataSet, attributeIndex);
	vector < double > SortedTargets = sortTargetValues(dataSet, attributeIndex);
	vector < double > Row_1, Row_2, Row_3, Row_4;
	for (int i = 0; i < SortedValues.size(); ++i) {
		if ((SortedValues[i] - cutoff) < -1.e-8) {
			Row_1.push_back(SortedTargets[i]);
			Row_3.push_back(SortedValues[i]);
		}
		else {
			Row_2.push_back(SortedTargets[i]);
			Row_4.push_back(SortedValues[i]);
		}
	}
	bisectParts["Lower_Scores"] = Row_1;
	bisectParts["Upper_Scores"] = Row_2;
	bisectParts["Lower_Values"] = Row_3;
	bisectParts["Upper_Values"] = Row_4;
	return bisectParts;
}

// C4.5 Entrogy and Information Gain Calculations
vector<double> uniqueValues(vector<double> val) {
	sort(val.begin(), val.end());
	unique(val.begin(), val.end());
	//unique(val.begin(), val.end(), [](double x, double y) { return (int(x) == int(y)); });
	return val;
}

double computeEntropy(vector<double> values) {

	// get a list of unique values
	vector<double> valueRange = uniqueValues(values);

	//count the 
	double entropy = 0.;
	int count[valueRange.size()] = { 0 };
	if (valueRange.size() == 0) { return 0.; }
	else {
		for (int i = 0; i < values.size(); ++i) {
			for (int j = 0; j < valueRange.size(); ++j) {
				if (values[i] == values[j]) { count[j] += 1; }
			}
		}
	}

	double tempP, tempEntropy;
	for (int j = 0; j < valueRange.size(); ++j) {
		tempP = count[j] / values.size();
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

double computeInfoGain(vector<Node> dataSet, int attributeIndex, double cutOff = 0) {
	double originalEntropy = 0., afterEntropy = 0., gainedEntropy = 0.;
	
	vector<double> targets = getTargets(dataSet);
	originalEntropy = computeEntropy(targets);
	
	map<string, vector<double>> parts = getAttributeBisectParts(dataSet, attributeIndex, cutOff);
	double lowerLen = parts["Lower_Scores"].size();
	double upperLen = parts["Upper_Scores"].size();
	double len = lowerLen + upperLen;
	afterEntropy = lowerLen / len * computeEntropy(parts["Lower_Scores"]) 
				   + upperLen / len * computeEntropy(parts["Upper_Scores"]);
	gainedEntropy = originalEntropy - afterEntropy;
	
	return gainedEntropy;
}

double gainRatio(vector<Node> dataSet, int attributeIndex, double cutOff = 0) {
	double attributeEntropy = computeAttributeEntropy(dataSet, attributeIndex);
	double attributeInfoGain = computeInfoGain(dataSet, attributeIndex, cutOff);
	return (attributeInfoGain / attributeEntropy);
}

// Decision Tree
Tree::Tree(double p = 0.95) : StopCriteria(p) { DecisionNode = 0; Branch = ""; }

void Tree::setDecisionNode(int& inputDecisionNode) { DecisionNode = inputDecisionNode; }

void Tree::setBranch(string& inputBranch) { Branch = inputBranch; }

void Tree::addChild(Tree* inputChild) { Child.push_back(inputChild); }

int Tree::getDecisionNode() const { return DecisionNode; }

string Tree::getBranch() const { return Branch; }

vector<Tree*> Tree::getChild() const { return Child; }

Tree* Tree::buildTree(Tree* tree, vector<Node> dataSet) {

}

void Tree::display(int Depth) {

}
