#include "Node.h"

std::ostream& operator<<(std::ostream& os, const Node& node) {
	os << "Factors: ";
	for (int i = 0; i < node.factorNum; i++) {
		os << node.factors[i] << " ";
	}
	os << "\n" << "Label: " << node.label << std::endl;
	return os;
}

double distance(Node & anotherNode)
{
	return 0.0;
}


Node::Node()
{
	factors = NULL;
}

Node::Node(double * inputFactors, int & inputLabel, int & inputFactorNum)
{
	factorNum = inputFactorNum;
	label = inputLabel;
	factors = new double[factorNum];
	for (int i = 0; i < factorNum; i++) {
		factors[i] = inputFactors[i];
	}
}

Node::Node(const Node& inputNode)
{
	factorNum = inputNode.factorNum;
	label = inputNode.label;
	double* inputFactors = inputNode.getFactors();
	factors = new double[factorNum];
	
	for (int i = 0; i < factorNum; i++) {
		factors[i] = inputFactors[i];
	}
}

void Node::setFactors(double * inputFactors)
{
	if (factors != NULL) {
		delete[] factors;
	}
	factors = new double[factorNum];
	for (int i = 0; i < factorNum; i++) {
		factors[i] = inputFactors[i];
	}
}

void Node::setLabel(int & inputLabel)
{
	label = inputLabel;
}

void Node::setLabel(int inputLabel)
{
	label = inputLabel;
}

void Node::setFactorNum(int & inputNum)
{
	factorNum = inputNum;
}

void Node::setFactorNum(int inputNum)
{
	factorNum = inputNum;
}

double Node::getFactor(int & n) 
{
	if (n < factorNum && n >= 0)
		return factors[n];
	else
		return -99999;
}

int Node::getLabel() const
{
	return label;
}

double * Node::getFactors() const
{
	return factors;
}

int Node::getFactorNum() const
{
	return factorNum;
}
