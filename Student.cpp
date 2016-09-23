#include "Student.h"
#include <stdio.h>
#include <iostream>
using namespace std;



const double Student::question_ratio[] = {0, 0, 0.2, 0.2, 
	0.15*0.2, 0.15*0.1, 0.15*0.05, 0.15*0.5, 0.15*15, 0, 
	0.15, 0.1, 0.1, 0.05, 0.05};
// const double Student::hobby_ratio[] = {0.2, 0.1, 0.05, 0.5, 0.15, 0};
const double Student::MIN[size] = {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
const double Student::MAX[size] = {1, 1, 16, 16, 0.2, 0.1, 0.05, 0.5, 0.15, 0, 3, 2, 16, 1, 2};
const string Student::answers[size][6] = {
	{"男", "女"},
	{"广东省内", "广东省外"},
	{"7:00及以前", "7:00-8:30", "看上课时间安排", "倾向于睡懒觉"},
	{"22:30及以前", "22:30-24:00", "24:00-01:00", "\"01:00以后，越晚越精神\""},
	{"", "户外运动"},
	{"", "看电影电视剧"},
	{"", "阅读"},
	{"", "打游戏"},
	{"", "外出聚会"},
	{"", "其他"},
	{"安静型", "能静能动，收放自如", "活跃型"},
	{"是", "不清楚", "否"},
	{"有", "无"},
	{"500及以下", "500-1500", "1500-3000", "3000及以上"},
	{"是", "无所谓", "否"}
};


Student::Student()
: Element(size, question_ratio) {}


Student::Student(const vector<string>& row)
: Element(size, question_ratio), id(row[0]), name(row[1]) {
	for (int i = 2; i < row.size(); ++i)
		data[i-2] = str2int(row[i]);

	raw_data = data;

	data[2] = sqrt_trans(data[2] += 1);	// 起床时间
	data[3] = sqrt_trans(data[3] += 1);	// 就寝时间
	data[12] = sqrt_trans(data[12] += 1);// 家庭收入水平
	data[10] *= MAX[10];	// 性格分明，尽量不要出现三个安静+1个活跃
	for (int i = 0; i < size; ++i)
		if (MAX[i] > MIN[i])
			data[i] = (data[i] - MIN[i]) / (MAX[i] - MIN[i]);
}


istream& operator >> (istream& is, Student& stu) {
	vector<string> row(Student::size);
	for (int i = 0; i < Student::size; ++i)
		is >> row[i];
	stu = Student(row);
	return is;
}


double Student::sqrt_trans(double x) {
	return x * x;
}


void Student::display() const {
	printf("Id is %s", id.c_str());
	for (int i = 0; i < size; ++i)
		printf(", %.3lf", data[i]);
	printf("\n");
}


void Student::output(ostream& out) const {
	out << id << ',' << name;

	for (int i = 0; i < size; ++i) {
		if (i == 4) {
			out << ",\"";
			bool have = false;
			for (int j = 0; j < 6; ++i, ++j) {
				if (!have && answers[i][int(raw_data[i])].size() > 0) {
					have = true;
					out << answers[i][int(raw_data[i])];
				}
				else if (answers[i][int(raw_data[i])].size() > 0)
					out << ',' << answers[i][int(raw_data[i])];
			}
			out << "\"";
			--i;
		}
		else
			out << ',' << answers[i][int(raw_data[i])];
	}
	out << endl;
}


int Student::getKind() {
	return data[0] * 2 + data[1];
}