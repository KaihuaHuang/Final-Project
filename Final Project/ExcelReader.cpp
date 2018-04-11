#include "ExcelReader.h"
void ExcelReader::parser(Node & node, std::stringstream & ss)
{
}
ExcelReader::ExcelReader(std::string & inputFileName, bool inputHeader)
{
	fileName = inputFileName;
	header = inputHeader;
	file = std::ifstream(inputFileName);
	if (file.fail()) {
		std::cerr << "Fail to open file";
		return;
	}
}
