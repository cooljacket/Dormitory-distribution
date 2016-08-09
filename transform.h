#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

/*
由于从问卷星获取的数据里头，学生填写的学号有的是错的，所以输出结果应该以（学院提供）已有的学生列表为主。
处理过程相当于将学生列表和问卷结果表，两张表根据name列给join一下。
但是又有个问题，就是如果万一，有两个人是同名的话，那就真心不知道谁跟谁了，目测需要人为介入，当下的实现以没有重复名字来做。

还有一个要注意的点：同一个人可能会多次提交，应该以最后一次提交的数据为主！
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include "CSVReader.h"
using namespace std;


inline int str2int(const string& str);
void province2int(string& province);
void readStudentsList(const char* fileName, map<string, string>& list);
void transform(const char* inputFile, const char* outputFile, const char* studentsListFile);
int transform_original_data(const char* inputFile);

#endif