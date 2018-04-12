#ifndef NODE_H
#define NODE_H
#include <iostream>
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
	Node(const Node& inputNode);
	
	void setFactors(double* inputFactors);
	void setLabel(int& inputLabel);
	void setLabel(int inputLabel);
	void setFactorNum(int& inputNum);
	void setFactorNum(int inputNum);
	friend double distance(Node& node, Node & anotherNode);
	double getFactor(int& n);
	int getLabel() const;
	double* getFactors() const;
	int getFactorNum() const;
	friend std::ostream& operator<<(std::ostream& os, const Node& node);
};

#endif