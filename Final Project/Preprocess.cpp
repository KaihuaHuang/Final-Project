#include "Preprocess.h"
#include <algorithm>
#define LABELNUM 3
set PRERPOCESS::normalizeFactor(set & dataSet, int & size, int & n)
{
	return set();
}

set PRERPOCESS::normalizeAllFactors(set & dataSet, int & size, int & n)
{
	return set();
}

std::tuple<set, set> PRERPOCESS::seperateSet(set & dataSet, double * splitWeights)
{

	return std::tie(dataSet, dataSet);

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
	std::cout << count1 << std::endl;
	std::cout << count2 << std::endl;
	std::cout << count3 << std::endl;
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
	/*std::cout << x << std::endl;
	std::vector<int> temp;
	for (int i = 0; i < count1; ++i)
	{
		temp.push_back(i + 1);
	}
	std::random_shuffle(temp.begin(), temp.end());
	for (int i = 0; i < x; ++i)
	{
		index1.push_back(temp[i]);
	}
	temp.clear();

	for (int i = 0; i < count2; ++i)
	{
		temp.push_back(i + 1);
	}
	std::random_shuffle(temp.begin(), temp.end());
	for (int i = 0; i < x; ++i)
	{
		index2.push_back(temp[i]);
	}
	temp.clear();
	for (int i = 0; i < count3; ++i)
	{
		temp.push_back(i + 1);
	}
	std::random_shuffle(temp.begin(), temp.end());
	for (int i = 0; i < x; ++i)
	{
		index3.push_back(temp[i]);
	}
	temp.clear();
	std::vector<Node> newDataSet;
	for (int i = 0; i < x; i++)
	{
		newDataSet.push_back(up[index1[i]]);
		newDataSet.push_back(no_change[index2[i]]);
		newDataSet.push_back(down[index3[i]]);
	}

	return newDataSet;*/
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
