#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <tuple>

#include "Node.h"
using namespace std;

class DecisionTree {
private:
	// map< ID, tuple<tags of 0&1, label> >
	map<string, tuple<vector<int>,int>> IDcode;
	// vector< index of factor, cut-off point >
	vector<pair<int,int>> Attributes;
	double StopCriteria;

public:
	DecisionTree(int p = 0.95) : StopCriteria(p) {}
	double computeEntropy(vector<Node>& dataSet);
	double computeGain(vector<Node>& dataSet);
	double isLeafNode();
};

#endif // DECISIONTREE_H

