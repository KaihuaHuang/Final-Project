#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include <iostream>
#include <vector>
#include <map>
#include "Node.h"
using namespace std;

class Tree {
private:
	int DecisionNode;	// attribute index with max. info gain
	string Branch;	// either "<cutOff" or ">cutOff"
	vector<Tree*> Child; // 2 children if bisection
	bool Leaf;	//whether this is a leaf node
	int Depth;
	double StopCriteria;
public:
	Tree(double p = 0.95);
	// Setter ang getter
	void setDecisionNode(int& inputDecisionNode);
	void setBranch(string& inputBranch);
	void addChild(Tree* inputChild);
	void setLeaf(bool inputLeaf);
	void setDepth(int& inputDepth);
	int getDecisionNode() const;
	string getBranch() const;
	vector<Tree*> getChild() const;
	bool isLeaf() const;
	int getDepth() const;
	double getStopCriteria() const;
	// Build and display tree
	Tree* buildTree(Tree* tree, vector<Node> dataSet, int depth);
	void display(vector<string> attributeName, int depth = 0);

	// Return the predict labels
	int predictNode(Node node);
	vector<int> predict(vector<Node> dataSet);
};

// DataSet Processor
vector<double> uniqueValues(vector<double> val);
vector<double> getAttributeValues(vector<Node> dataSet, int attributeIndex);
vector<double> sortAttributeValues(vector<Node> dataSet, int attributeIndex);
vector<double> sortTargetValues(vector<Node> dataSet, int attributeIndex);
vector<double> getCutOffs(vector<Node> dataSet, int attributeIndex);
map<string, vector<double>> getAttributeBisectParts(vector<Node> dataSet, int attributeIndex, double cutoff);

// C4.5 Entrogy and Information Gain Calculations
vector<double> uniqueValues(vector<double> val);
double frequentValues(vector<double> val);
double computeFrequency(vector<double> cluster, vector<double> uniqueTargets, double mostFrequentVal);
double computeEntropy(vector<double> values);
double computeAttributeEntropy(vector<Node> dataSet, int attributeIndex);
double computeInfoGain(vector<Node> dataSet, int attributeIndex, double cutOff = 0);
double computeGainRatio(vector<Node> dataSet, int attributeIndex, double cutOff = 0);


#endif // DECISIONTREE_H

