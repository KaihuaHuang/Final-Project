#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include <iostream>
#include <vector>
#include "Node.h"
using namespace std;

class Tree {
private:
	int DecisionNode;	// attribute index with max. info gain
	string Branch;	// either "<cutOff" or ">cutOff"
	vector<Tree*> Child; // 2 children if bisection
	double StopCriteria;
	
public:
	Tree(double p = 0.95);
	void setDecisionNode(int& inputDecisionNode);
	void setBranch(string& inputBranch);
	void addChild(Tree* inputChild);
	int getDecisionNode() const;
	string getBranch() const;
	vector<Tree*> getChild() const;
	double getStopCriteria() const;

	Tree* buildTree(Tree* tree, vector<Node> dataSet);
	void display(int Depth);
};

#endif // DECISIONTREE_H

