#include "Node.h"
#define INDUSTRY_DISTANCE 3
std::ostream& operator<<(std::ostream& os, const Node& node) {
	os << "Factors: ";
	for (int i = 0; i < node.factorNum; i++) {
		os << node.factors[i] << " ";
	}
	os << "\n" << "Label: " << node.label << std::endl;
	return os;
}

double distance(Node& node,Node & anotherNode, double* weights)
{
	double distance = 0;
	for (int i = 0; i < (node.factorNum-1); i++) {
		if(weights == NULL){
			distance += (node.factors[i] - anotherNode.factors[i])* (node.factors[i] - anotherNode.factors[i]);
		}
		else {
			distance += (node.factors[i] - anotherNode.factors[i])* (node.factors[i] - anotherNode.factors[i])*weights[i];
		}
	}
	if (node.factors[node.factorNum - 1] == anotherNode.factors[node.factorNum - 1]) {
		return distance;
	}
	else {
		return distance + INDUSTRY_DISTANCE * INDUSTRY_DISTANCE;
	}
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

void Node::setFactor(double value, int n)
{
	factors[n] = value;
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
