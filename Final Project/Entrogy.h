#ifndef C4_5ALGORITHM_H
#define C4_5ALGORITHM_H

#include <iostream>
#include <vector>
#include <map>
#include "Node.h"


// DataSet Process
vector<double> getTargets(vector<Node> dataSet);
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

#endif
