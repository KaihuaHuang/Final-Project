#pragma once
class Node {
private:
	double* factors;
	int label;
	int factorNum;
public:
	Node();
	//Array Deep Copy
	Node(double* inputFactors, int& inputLabel, int& inputFactorNum);
	//Copy Construction
	Node(Node& inputNode);
	
	void setFactors(double* inputFactors);
	void setLabel(int& inputLabel);
	void setFactorNum(int& inputNum);
	friend double distance(Node& anotherNode);
	double getFactor(int& n);
	int getLabel();
	double* getFactors();
	int getFactorNum();
};