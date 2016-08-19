#ifndef __UTILS_H__
#define __UTILS_H__


#include <string>
#include <sstream>
using namespace std;

const char* GuangDong = "广东";
const char* file_after_process = "data/data.csv";
const char* not_in_the_list = "results/not_in_the_list.txt";

int str2int(const string& str) {
	stringstream ss(str);
	int num;
	ss >> num;
	return num;
}

#endif