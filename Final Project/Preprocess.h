#ifndef PRERPOCESS_H
#define PRERPOCESS_H
#include "Node.h"
#include <vector>
#include <utility>
using set = std::vector<Node>;
class PRERPOCESS {
public:
	//Do the normalize for n th factor
	static set normalizeFactor(set& dataSet, int& size, int& n);

	//Normalize all the factors except n th factor
	//N th factor would be represent for industry
	static set normalizeAllFactors(set& dataSet, int& size, int& n);

	//According splitWeights to split dataset into training set and test set
	static std::tuple<set, set> seperateSet(set& dataSet, double* splitWeights);

	static set rebalanceSet(set& dataSet, double* balanceWeights);
};

#endif