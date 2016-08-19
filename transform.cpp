#include "transform.h"


extern const char* GuangDong;
extern const char* file_after_process;
extern const char* not_in_the_list ;
extern int str2int(const string& str);


int transform_original_data(const char* inputFile) {
	const char* outputFile = file_after_process;
	const char* studentsListFile = "data/students_list_2016.csv";
	transform(inputFile, outputFile, studentsListFile);
	return 0;
}


void province2int(string& province) {
	if (province.find(GuangDong) != string::npos)
		province = "0";
	else
		province = "1";
}


void readStudentsList(const char* fileName, map<string, string>& list) {
	// CSVReader reader;
	// vector<vector<string> > data;
	// reader.read(fileName, data);
	// for (int i = 0; i < data.size(); ++i)
	// 	list[data[i][1]] = data[i][0];

	CSVMapContainer mc(1);
	CSVReader::read(fileName, &mc);
	mc.getColData(list, 0);
}


void transform(const char* inputFile, const char* outputFile, const char* studentsListFile) {
	map<string, string> list;
	readStudentsList(studentsListFile, list);

	CSVVectorContainer vec;
	CSVReader::read(inputFile, &vec);
	vector<vector<string> >& data = vec.getData();

	fstream out(outputFile, ios::out);
	set<string> names;

	bool mask[] = {0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1};

	for (int i = 0; i < data.size(); ++i) {
		if (names.find(data[i][7]) != names.end())
			continue;
		names.insert(data[i][7]);

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


	// 最后还要输出没有填问卷的那部分学生的名字
	fstream others(not_in_the_list, ios::out);
	map<string, string>::iterator it = list.begin();
	while (it != list.end()) {
		if (names.find(it->first) == names.end())
			others << it->second << ", " << it->first << endl;
		++it;
	}
	others.close();
}