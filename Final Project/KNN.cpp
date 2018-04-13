#include "KNN.h"
#include <vector>
#include <map>


KNN::KNN(int k, double * inputWeights, int weightNum)
{
	kNeighbor = k;
	if (inputWeights != NULL) {
		weights = new double[weightNum];
		for (int i = 0; i < weightNum; i++) {
			try {
				weights[i] = inputWeights[i];
			}
			catch (std::exception &e) {
				std::cerr << e.what() << std::endl;
				break;
			}
		}
	}
	else {
		weights = NULL;
	}
}

void KNN::setWeights(double * inputWeights,int weightNum)
{
	if (weights != NULL) {
		delete[] weights;
	}
	weights = new double[weightNum];
	for (int i = 0; i < weightNum; i++) {
		weights[i] = inputWeights[i];
	}
}

void KNN::fit(std::vector<Node>& dataSet, const int & num)
{
	trainningSet = dataSet;
	trainningSetNum = num;
}

int * KNN::predict(std::vector<Node>& dataSet, const int & num)
{
	return nullptr;
}

int KNN::predictNode(Node & node)
{
	std::multimap<double, int> index_distance;
	int index = 0;
	for (auto& e : trainningSet) {
		index_distance.insert(std::pair<double, int>(distance(node, e, weights), index));
		index++;
	}

	std::map<int, int> labelCounter;
	int count = 0;
	for (auto it = index_distance.begin(); it != index_distance.end() & count < kNeighbor; it++,count++) {
		int index = it->second;
		int label = trainningSet[index].getLabel();
		try {
			labelCounter.at(label);
			labelCounter[label] = labelCounter[label] + 1;
		}
		catch (std::exception & e) {
			labelCounter[label] = 1;
		}
	}

	int finalLabel = -1;
	int highestCount = -1;
	for (auto& e : labelCounter) {
		//If they are equal what shold you do
		if (e.second > highestCount) {
			highestCount = e.second;
			finalLabel = e.first;
		}
	}
	return finalLabel;

}


