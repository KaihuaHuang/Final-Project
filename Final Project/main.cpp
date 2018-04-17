#include <iostream>
#include <string>
#include "Node.h"
#include "ExcelReader.h"
#include "KNN.h"
#include "Preprocess.h"
using namespace std;

int main() {
	string fileName("dataSet.csv");
	ExcelReader reader(fileName);
	vector<Node> dataSet = reader.readFile();
	/*for (auto it = dataSet.begin(); it != dataSet.end(); it++) {
		cout << *it << endl;
	}*/
	double balanceWeights[3] = { 1,2,1 };

	vector<Node> balanceSet = PRERPOCESS::rebalanceSet(dataSet, balanceWeights);

	double* weights = NULL;
	//cout << distance(dataSet[0], dataSet[1], weights) << endl;

	KNN cif;
	cif.fit(dataSet, dataSet.size());
	cout << "Predict Label: " << cif.predictNode(dataSet[0]) << endl;


}
