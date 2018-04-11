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

Node::Node(Node & inputNode)
{

}

void Node::setFactors(double * inputFactors)
{
}

void Node::setLabel(int & inputLabel)
{
}

void Node::setFactorNum(int & inputNum)
{
}

double Node::getFactor(int & n)
{
	return 0.0;
}

int Node::getLabel()
{
	return 0;
}

double * Node::getFactors()
{
	return nullptr;
}

int Node::getFactorNum()
{
	return 0;
}
