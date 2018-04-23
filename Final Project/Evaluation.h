#pragma once
#include <vector>
class Evaluation
{
public:
	//Number of Predict right/ Number of total sample
	static double accuracy(std::vector<int> original, std::vector<int> predict);

	static void confusionMatrix(std::vector<int> original, std::vector<int> predict);

	static std::vector<int> vote(std::vector<int> KNNpredict, std::vector<int> DTpredict);
};

