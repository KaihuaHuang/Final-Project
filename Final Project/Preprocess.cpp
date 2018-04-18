#include "Preprocess.h"
#include <algorithm>
#define LABELNUM 3
void PRERPOCESS::normalizeFactor(set& dataSet, int n)
{
	int size = dataSet.size();
	double min = 99999;
	double max = -1;
	double factor;
	for (int i = 0; i < size; i++) {
		factor = dataSet[i].getFactor(n);
		if (factor < min) {
			min = factor;
		}
		if (factor > max) {
			max = factor;
		}
	}
	for (int i = 0; i < size; i++) {
		factor = dataSet[i].getFactor(n);
		dataSet[i].setFactor((factor - min) / (max - min), n);
	}
}

void PRERPOCESS::normalizeAllFactorsExcept(set & dataSet,int n)
{
	int factorNum = dataSet[0].getFactorNum();
	for (int i = 0; i < factorNum; i++) {
		if (i != n) {
			normalizeFactor(dataSet, i);
		}
	}
}

std::tuple<set, set> PRERPOCESS::seperateSet(set & dataSet, double splitWeights)
{
	if (splitWeights < 0 || splitWeights > 1) {
		std::cerr << "Split Weight is not between 0 and 1" << std::endl;
	}
	int size = dataSet.size();
	auto it = dataSet.begin();
	set trainningSet = set(it, it + (int)(size*splitWeights));
	set testSet = set(it + (int)(size*splitWeights), dataSet.end());
	return std::tie(trainningSet, testSet);
}

set PRERPOCESS::rebalanceSet(set & dataSet, double * balanceWeights)
{
	std::vector<Node> up;
	std::vector<Node> no_change;
	std::vector<Node> down;
	std::vector<int> index1;
	std::vector<int> index2;
	std::vector<int> index3;
	int count1 = 0, count2 = 0, count3 = 0;
	for (int i = 0; i < dataSet.size(); i++)
	{
		if (dataSet[i].getLabel() == 1)
		{
			up.push_back(dataSet[i]);
			count1++;
		}
		else if (dataSet[i].getLabel() == 0)
		{
			no_change.push_back(dataSet[i]);
			count2++;
		}
		else
		{
			down.push_back(dataSet[i]);
			count3++;
		}
	}
	int x = 0;
	if (balanceWeights[0] > balanceWeights[1] && balanceWeights[0] > balanceWeights[2])
	{
		x = count1;
		while (count2 <= balanceWeights[1] / balanceWeights[0] * x||count3 <= balanceWeights[2] / balanceWeights[0] * x)
		{
			x--;
		}
		count1 = x;
		count2 = balanceWeights[1] / balanceWeights[0] * x;
		count3 = balanceWeights[2] / balanceWeights[0] * x;

	}
	else if (balanceWeights[1] > balanceWeights[0] && balanceWeights[1] > balanceWeights[2])
	{
		x = count2;
		while (count1 <= balanceWeights[0] / balanceWeights[1] * x||count3 <= balanceWeights[2] / balanceWeights[1] * x)
		{
			x--;
		}
		count1 = balanceWeights[0] / balanceWeights[1] * x;
		count2 = x;
		count3 = balanceWeights[2] / balanceWeights[1] * x;
	}
	else
	{
		x = count3;
		while (count1 <= balanceWeights[0] / balanceWeights[2] * x||count2 <= balanceWeights[1] / balanceWeights[2] * x)
		{
			x--;
		}
		count1 = balanceWeights[0] / balanceWeights[2] * x;
		count2 = balanceWeights[1] / balanceWeights[2] * x;
		count3 = x;
	}
	
	std::vector<Node> newDataSet;
	std::random_shuffle(up.begin(), up.end());
	std::random_shuffle(no_change.begin(), no_change.end());
	std::random_shuffle(down.begin(), down.end());
	for (int i = 0; i < count1; i++) {
		newDataSet.push_back(up[i]);
	}
	for (int i = 0; i < count2; i++) {
		newDataSet.push_back(no_change[i]);
	}
	for (int i = 0; i < count3; i++) {
		newDataSet.push_back(down[i]);
	}
	return newDataSet;
}
