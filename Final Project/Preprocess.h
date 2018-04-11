#ifndef PRERPOCESS_H
#define PRERPOCESS_H
#include "Node.h"
#include <vector>
class PRERPOCESS {
public:
	//Do the normalize for n th factor
	static void normalizeFactor(std::vector<Node>& dataSet, int& size, int& n);

	//Normalize all the factors except n th factor
	//N th factor would be represent for industry
	static void normalizeAllFactors(std::vector<Node>& dataSet, int& size, int& n);

};

#endif