#include "Student.h"
#include <stdio.h>


const double Student::question_ratio[] = {0, 0, 0.2, 0.2, 0.15, 0.15, 0.1, 0.1, 0.05, 0.05};
const double Student::hobby_ratio[] = {0.2, 0.1, 0.05, 0.5, 0.15, 0};
const double Student::MIN[size] = {0};
const double Student::MAX[size] = {1, 1, 9, 9, 2, 0.2, 0.1, 0.05, 0.5, 0.15, 0, 2, 9, 1, 2};
const string Student::answers[size][6] = {
	{"男", "女"},
	{"广东省内", "广东省外"},
	{"7:00及以前", "7:00-8:30", "看上课时间安排", "倾向于睡懒觉"},
	{"22:30及以前", "22:30-24:00", "24:00-01:00", "\"01:00以后，越晚越精神\""},
	{"安静型", "能静能动，收放自如", "活跃型"},
	{"", "户外运动"},
	{"", "看电影电视剧"},
	{"", "阅读"},
	{"", "打游戏"},
	{"", "外出聚会"},
	{"", "其他"},
	{"是", "不清楚", "否"},
	{"500及以下", "500-1500", "1500-3000", "3000及以上"},
	{"有", "无"},
	{"是", "无所谓", "否"}
};


Student::Student()
: Element(size, question_ratio) {}


istream& operator >> (istream& is, Student& stu) {
	char buf;
	is >> stu.id;
	for (int i = 0; i < stu.size; ++i)
		is >> buf >> stu.data[i];
	stu.raw_data = stu.data;

	stu.data[2] = stu.sqrt_trans(stu.data[2]);
	stu.data[3] = stu.sqrt_trans(stu.data[3]);
	stu.data[12] = stu.sqrt_trans(stu.data[12]);
	for (int i = 0; i < 6; ++i)
		stu.data[i+5] *= stu.hobby_ratio[i];
	for (int i = 0; i < stu.size; ++i)
		if (i != 10)
			stu.data[i] = (stu.data[i] - stu.MIN[i]) / (stu.MAX[i] - stu.MIN[i]);
	return is;
}


double Student::sqrt_trans(double x) {
	return x * x;
}


void Student::display() const {
	printf("Id is %d", id);
	for (int i = 0; i < size; ++i)
		printf(", %.3lf", data[i]);
	printf("\n");
}


void Student::output() const {
	printf("%d", id);
	for (int i = 0; i < size; ++i) {
		if (i == 5) {
			printf(",\"");
			bool have = false;
			for (int j = 0; j < 6; ++i, ++j) {
				if (!have && answers[i][int(raw_data[i])].size() > 0) {
					have = true;
					printf("%s", answers[i][int(raw_data[i])].c_str());
				}
				else if (answers[i][int(raw_data[i])].size() > 0)
					printf(",%s", answers[i][int(raw_data[i])].c_str());
			}
			printf("\"");
			--i;
		}
		else
			printf(",%s", answers[i][int(raw_data[i])].c_str());
	}
	printf("\n");
}


int Student::getKind() {
	return data[0] * 2 + data[1];
}