#include <iostream>
#include <string>
#include "Node.h"
#include "ExcelReader.h"
using namespace std;

int main() {
	double test[5] = { 0,1,2,3,4 };
	int a = 0;
	int b = 5;
	Node node((double*)test, a, b);
	cout << node;

	string fileName("dataSet.csv");
	ExcelReader reader(fileName);

}
