
#include <algorithm>
#include "C4_5Algorithm.h"

using namespace std;

// DataSet Process
vector<double> getTargets(vector<Node> dataSet) {
	vector<double> result3mo;
	for (int i = 0; i < dataSet.size(); ++i) {
		result3mo.push_back((double)(dataSet[i].getLabel()));
	}
	return result3mo;
}

vector<double> getAttributeValues(vector<Node> dataSet, int attributeIndex) {
	vector<double> values;
	for (int i = 0; i < dataSet.size(); ++i) {
		values.push_back(dataSet[i].getFactor(attributeIndex));
	}
	return values;
}

vector<double> sortAttributeValues(vector<Node> dataSet, int attributeIndex) {
	vector<double> values = getAttributeValues(dataSet, attributeIndex);
	sort(values.begin(), values.end());
	return values;
}

vector<double> sortTargetValues(vector<Node> dataSet, int attributeIndex) {
	vector<double> values = getAttributeValues(dataSet, attributeIndex);
	vector<double> targets = getTargets(dataSet);
	double temp;

	for (int i = 0; i < values.size() - 1; ++i) {
		for (int j = i + 1; j < values.size(); j++) {
			if ((values[i] - values[j]) > 1.e-8) {
				temp = values[i];
				values[i] = values[j];
				values[j] = temp;

				temp = targets[i];
				targets[i] = targets[j];
				targets[j] = temp;
			}
		}
	}
	return targets;
}

vector<double> getCutOffs(vector<Node> dataSet, int attributeIndex) {
	vector<double> cutOffs;
	vector < double > sortedValues = sortAttributeValues(dataSet, attributeIndex);
	vector < double > sortedTargets = sortTargetValues(dataSet, attributeIndex);
	for (int i = 0; i < sortedValues.size() - 1; i++) {
		if ((abs(sortedValues[i] - sortedValues[i + 1])>0.5) & (sortedTargets[i] != sortedTargets[i + 1])) {
			cutOffs.push_back((sortedValues[i] + sortedValues[i + 1]) / 2.);
		}
	}
	return cutOffs;
}

map<string, vector<double>> getAttributeBisectParts(vector<Node> dataSet, int attributeIndex, double cutoff) {
	map <string, vector<double>> bisectParts;
	vector < double > sortedValues = sortAttributeValues(dataSet, attributeIndex);
	vector < double > sortedTargets = sortTargetValues(dataSet, attributeIndex);
	vector < double > row1, row2, row3, row4;
	for (int i = 0; i < sortedValues.size(); ++i) {
		if (sortedValues[i] < cutoff) {
			row1.push_back(sortedTargets[i]);
			row3.push_back(sortedValues[i]);
		}
		else {
			row2.push_back(sortedTargets[i]);
			row4.push_back(sortedValues[i]);
		}
	}
	bisectParts["Lower_Scores"] = row1;
	bisectParts["Upper_Scores"] = row2;
	bisectParts["Lower_Values"] = row3;
	bisectParts["Upper_Values"] = row4;
	return bisectParts;
}



// C4.5 Entrogy and Information Gain Calculations
// Get a list of unique values of val
vector<double> uniqueValues(vector<double> val) {
	sort(val.begin(), val.end());
	val.erase(unique(val.begin(), val.end()), val.end());
	//val.erase(unique(val.begin(), val.end(), [](double x, double y) { return (int(x) == int(y)); }), val.end());
	return val;
}

// Return the most frequent values of val
double frequentValues(vector<double> val) {
	vector<double> uniqueVal = uniqueValues(val);
	int* Count = new int[uniqueVal.size()]{ 0 };
	for (int i = 0; i < val.size(); i++) {
		for (int j = 0; j < uniqueVal.size(); j++) {
			Count[j] = int(count(val.begin(), val.end(), uniqueVal[j]));
		}
	}

	int maxCount = 0, maxIndex;
	for (int i = 0; i < uniqueVal.size(); i++) {
		if (Count[i] > maxCount) {
			maxCount = Count[i];
			maxIndex = i;
		}
	}
	return uniqueVal[maxIndex];
}

// Return the percentage frequency of a value
double computeFrequency(vector<double> cluster, vector<double> uniqueTargets, double mostFrequentVal) {
	int index;
	vector<double> frequency;
	int* Count = new int[uniqueTargets.size()]{ 0 };

	for (int i = 0; i < cluster.size(); ++i) {
		for (int j = 0; j < uniqueTargets.size(); ++j) {
			Count[j] = int(count(cluster.begin(), cluster.end(), uniqueTargets[j]));
		}
	}

	for (int i = 0; i < uniqueTargets.size(); ++i) {
		frequency.push_back((double)(Count[i] / cluster.size()));
		if (uniqueTargets[i] == mostFrequentVal) { index = i; }
	}
	return frequency[index];
}

//Calculate the entropy
double computeEntropy(vector<double> values) {

	// get a list of unique values
	vector<double> valueRange = uniqueValues(values);

	double entropy = 0.;
	int* count = new int[valueRange.size()]{ 0 };
	if (valueRange.size() == 0) { return 0.; }
	else {
		for (int i = 0; i < values.size(); ++i) {
			for (int j = 0; j < valueRange.size(); ++j) {
				if (values[i] == valueRange[j]) { count[j] += 1; }
			}
		}
	}

	double tempP, tempEntropy;
	for (int j = 0; j < valueRange.size(); ++j) {
		tempP = (double)count[j] / (double)(values.size());
		tempEntropy = -tempP * log2(tempP);
		entropy += tempEntropy;
	}

	return entropy;
}

double computeAttributeEntropy(vector<Node> dataSet, int attributeIndex) {
	// get a vector of values associated with given attribute
	vector<double> values = getAttributeValues(dataSet, attributeIndex);
	return computeEntropy(values);
}

double computeInfoGain(vector<Node> dataSet, int attributeIndex, double cutOff) {
	double originalEntropy = 0., afterEntropy = 0., gainedEntropy = 0.;

	vector<double> targets = getTargets(dataSet);
	originalEntropy = computeEntropy(targets);

	map<string, vector<double>> parts = getAttributeBisectParts(dataSet, attributeIndex, cutOff);
	double lowerLen = (double)(parts["Lower_Scores"].size());
	double upperLen = (double)(parts["Upper_Scores"].size());
	double len = lowerLen + upperLen;
	afterEntropy = lowerLen / len * computeEntropy(parts["Lower_Scores"])
		+ upperLen / len * computeEntropy(parts["Upper_Scores"]);
	gainedEntropy = originalEntropy - afterEntropy;
	return gainedEntropy;
}

double computeGainRatio(vector<Node> dataSet, int attributeIndex, double cutOff) {
	double attributeEntropy = computeAttributeEntropy(dataSet, attributeIndex);
	double attributeInfoGain = computeInfoGain(dataSet, attributeIndex, cutOff);
	return (attributeInfoGain / attributeEntropy);
}