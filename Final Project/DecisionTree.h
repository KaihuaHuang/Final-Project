#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include <iostream>
#include <vector>
#include "Node.h"
using namespace std;

class DecisionTree {
private:
	double stopCriteria;

public:
	DecisionTree(int p = 0.95) : stopCriteria(p) {}


};

#endif // DECISIONTREE_H

