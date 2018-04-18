#include "Evaluation.h"
#include <iostream>
#include <iomanip>
using namespace std;




double Evaluation::accuracy(std::vector<int> original, std::vector<int> predict)
{
	int size = original.size();
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (original[i] == predict[i]) {
			count++;
		}
	}
	return double(count) / size;
}

void Evaluation::confusionMatrix(std::vector<int> original, std::vector<int> predict)
{
	int matrix[3][3] = { {0,0,0},{ 0,0,0 },{ 0,0,0 }};
	for (int i = 0; i < original.size(); i++) {
		int real = original[i];
		int predictLabel = predict[i];
		matrix[real + 1][predictLabel + 1]+= 1;
	}
	std::cout << "----Confusion Matrix----" << std::endl;
	cout << setw(4) << " " << setw(4) << "-1" << setw(4) << "0" << setw(4) << "1" << endl;
	cout << setw(4) << "-1" << setw(4) << matrix[0][0] << setw(4) << matrix[0][1] << setw(4) << matrix[0][2] << endl;
	cout << setw(4) << "0" << setw(4) << matrix[1][0] << setw(4) << matrix[1][1] << setw(4) << matrix[1][2] << endl;
	cout << setw(4) << "1" << setw(4) << matrix[2][0] << setw(4) << matrix[2][1] << setw(4) << matrix[2][2] << endl;
}
