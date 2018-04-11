#ifndef EXCELREADER_H
#define EXCELREADER_H
#include <sstream>
#include <string>
#include "Node.h"
class ExcelReader {
private:
	std::string fileName;
	void parser(Node& node,std::stringstream& ss);
public:




};
#endif