#include "KNN.h"
#include <vector>

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
	std::vector<double> distances;
	for (auto& e : trainningSet) {
		distances.push_back(distance(node, e, weights));
	}
	return 0;

}


