#include "ExcelReader.h"
#include <map>
#define FACTORNUMBER 12
using namespace std;



void ExcelReader::parser(Node & node, std::stringstream & ss)
{
	string part;
	int count = 0;
	int index = 0;
	static int code = 0;
	double* facArray = new double[FACTORNUMBER];
	static map<string, int> industryCode;

	while (getline(ss, part, ',')) {
		if (count == 0) {
			count++;
			continue;
		}
		if (count == 11) {
			int industry;
			if (industryCode.find(part) != industryCode.end()) {
				industry = industryCode[part];
			}
			else {
				industryCode.insert(map<string, int>::value_type(part, code));
				industry = code;
				code++;
			}
			/*try {
				industry = industryCode.at(part);
			}
			catch (...) {
				industryCode.insert(map<string, int>::value_type(part, code));
				//industryCode[part] = code;
				industry = code;
				code++;
			}*/
			facArray[FACTORNUMBER - 1] = industry;
			count++;
			continue;
		}
		if (count == 13) {
			node.setFactorNum(FACTORNUMBER);
			node.setLabel(stoi(part));
			node.setFactors(facArray);
			delete[] facArray;
			break;
		}
		facArray[index] = stof(part);
		count++;
		index++;


	}

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

std::vector<Node> ExcelReader::readFile()
{
	string readline;
	if (header) {
		getline(file, readline);
	}

	vector<Node> result;
	int count = 0;
	while (getline(file, readline)) {
		stringstream ss;
		ss << readline;
		try {
			Node* nodeP = new Node;
			parser(*nodeP, ss);
			result.push_back(*nodeP);
			//count++;
		}
		catch(...){
			//cerr << "Error: " << readline << endl;
		}
	}
	
	return result;
}
