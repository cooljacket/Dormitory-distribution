#include "transform.h"

const char* file_after_process = "data/data.csv";


int transform_original_data(const char* inputFile) {
	const char* outputFile = file_after_process;
	const char* studentsListFile = "data/students_list_2016.csv";
	transform(inputFile, outputFile, studentsListFile);
	return 0;
}


inline int str2int(const string& str) {
	stringstream ss(str);
	int num;
	ss >> num;
	return num;
}


void province2int(string& province) {
	if (province.find("广东") != string::npos)
		province = "0";
	else
		province = "1";
}


void readStudentsList(const char* fileName, map<string, string>& list) {
	CSVReader reader;
	vector<vector<string> > data;
	reader.read(fileName, data);
	for (int i = 0; i < data.size(); ++i)
		list[data[i][1]] = data[i][0];
}


void transform(const char* inputFile, const char* outputFile, const char* studentsListFile) {
	map<string, string> list;
	readStudentsList(studentsListFile, list);

	CSVReader reader;
	vector<vector<string> > data;
	reader.read(inputFile, data);

	fstream out(outputFile, ios::out);

	bool mask[] = {0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1};

	for (int i = 0; i < data.size(); ++i) {
		if (list.find(data[i][7]) == list.end()) {
			cout << "ERROR!!!!!No such man " << data[i][7] << endl;
			return ;
		}

		province2int(data[i][9]);
		out << list[data[i][7]];
		for (int j = 7; j < data[i].size(); ++j) {
			if (!mask[j-7])
				out << ',' << data[i][j];
			else
				out << ',' << str2int(data[i][j]) - 1;
		}
		out << endl;
	}

	out.close();
}