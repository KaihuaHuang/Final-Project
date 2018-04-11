#pragma once
#include <iostream>
#include<fstream>
#include<sstream>
#include<vector>
class Node {
public:
	float *feature;
	int label;
};
// the node structure should be same as all from above
//standarlize the data
vector<Node> dataset;//should be initialize ahead

double standarlize(dataset)
{
	double max[10];
	double min[10];
	double temp_max[10];
	double temp_min[10];
	for (int i = 0; i < 1088; i++)
	{
		temp_max[i] = dataset[i].feature[0];
		temp_min[i] = dataset[i].feature[0];
		for (int j = 0; j < 10; j++)
		{
			if (temp_max[j] <= dataset[i].feature[j])
			{
				temp_max[j] = dataset[i].feature[j];
			}
			if (temp_min[j] >= dataset[i].feature[j])
			{
				temp_min[j] = dataset[i].feature[j];
			}
		}
		
	}
	for (int i = 0; i < 1088; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			dataset[i].feature[j] = dataset[i].feature[j] / (temp_max[j] - temp_min[j]);
		}
	}
}
//calculate the distance between points
float Node:: distance_calculation(const Node1, const Node2)
{
	double distance=0;
	for (int i = 0; i < 10; i++)
	{
		distance = (Node1.feature[i] - Node2.feature[i]) ^ 2 + distance;
	}
	distance = sqrt(distance);
	return distance;
}
//distance comparision

void def test() {}