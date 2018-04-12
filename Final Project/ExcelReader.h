#ifndef EXCELREADER_H
#define EXCELREADER_H
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Node.h"
class ExcelReader {
private:
	std::string fileName;
	std::ifstream file;
	bool header;
	void parser(Node& node,std::stringstream& ss);
public:
	ExcelReader(std::string& inputFileName,bool inputHeader = true);
	std::vector<Node> readFile();


};
#endif