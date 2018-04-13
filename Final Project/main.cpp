#include <iostream>
#include <string>
#include "Node.h"
#include "ExcelReader.h"
using namespace std;

int main() {
	string fileName("dataSet.csv");
	ExcelReader reader(fileName);
	vector<Node> dataSet = reader.readFile();
	for (auto it = dataSet.begin(); it != dataSet.end(); it++) {
		cout << *it << endl;
	}
	double* weights = NULL;
	cout << distance(dataSet[0], dataSet[1], weights) << endl;

}
