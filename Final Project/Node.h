#pragma once
class Node {
private:
	double* factores;
	int label;
	int factorNum;
public:
	friend double distance(Node& anotherNode);
	double getFactor(int& n);
	int getLabel();
	double* getFactors();
	int getFactorNum();
};