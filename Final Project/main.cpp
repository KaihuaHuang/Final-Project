#include <iostream>
#include <string>
#include "Node.h"
#include "ExcelReader.h"
#include "KNN.h"
#include "Preprocess.h"
#include "DecisionTree.h"
#define SPLITWEIGHT 0.8
using namespace std;

int main() {
	//Read from csv file
	string fileName("dataSet.csv");
	ExcelReader reader(fileName);
	set dataSet = reader.readFile();

	//Coyp DataSet for KNN and normalize it
	set dataSetCopy = dataSet;
	PRERPOCESS::normalizeAllFactorsExcept(dataSetCopy, 11);


	//Seperate data into trainingSet and testSet
	std::tuple<set, set> setPair = PRERPOCESS::seperateSet(dataSetCopy, SPLITWEIGHT);
	set trainningSet = get<0>(setPair);
	set testSet = get<1>(setPair);

	//Rebalance trainingSet
	double balanceWeights[3] = { 1,2,1 };
	vector<Node> balanceSet = PRERPOCESS::rebalanceSet(trainningSet, balanceWeights);


	double weights[12] = {1,1,1,1,1,1,1,1,1,1,1,1};

	KNN cif;
	cif.fit(balanceSet, balanceSet.size());
	cout << "Predict Label: " << cif.predictNode(testSet[0]) << endl;

	// Decision Tree Implementation
	Tree tree;
	Tree * DT = &tree;
	//DT = DT->buildTree(DT, dataSet);
	//vector<string> attributeName;
	//DT->display(attributeName,0);

}
