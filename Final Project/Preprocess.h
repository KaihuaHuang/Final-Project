#ifndef PRERPOCESS_H
#define PRERPOCESS_H
#include "Node.h"
#include <vector>
#include <tuple>
using set = std::vector<Node>;
class PRERPOCESS {
public:
	//Do the normalize for n th factor
	static void normalizeFactor(set& dataSet, int n);

	//Normalize all the factors except n th factor
	//N th factor would be represent for industry
	static void normalizeAllFactorsExcept(set& dataSet, int n = -1);

	//According splitWeights to split dataset into training set and test set
	static std::tuple<set, set> seperateSet(set& dataSet, double splitWeights);

	static set rebalanceSet(set& dataSet, double* balanceWeights);


};

#endif