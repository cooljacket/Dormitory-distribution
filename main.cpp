#include <iostream>
#include <vector>
#include <fstream>
#include "Student.h"
#include "KMeans.h"

using namespace std;

vector<vector<Student> > divide(vector<Student>& GroupA, vector<Student>& GroupB);

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cout << "usage: main input_data" << endl;
		return 0;
	}

	fstream data(argv[1], ios::in);
	vector<vector<Student> > all_stus(4);
	Student tmp;
	while (data >> tmp)
		all_stus[tmp.getKind()].push_back(tmp);
	data.close();

	vector<vector<Student> > result = divide(all_stus[Student::GIRLS_IN], all_stus[Student::GIRLS_OUT]);

	cout << "宿舍号,学号,性别,生源地,起床时间,就寝时间,性格,兴趣爱好,易受他人影响,集体住宿经历,家庭人均收入,喜欢开空调" << endl;
	for (int i = 0; i < result.size(); ++i) {
		cout << i+1;
		for (int j = 0; j < result[i].size(); ++j) {
			cout << ',';
			result[i][j].output();
		}
		cout << endl;
	}

	return 0;
}

vector<vector<Student> > divide(vector<Student>& GroupA, vector<Student>& GroupB) {
	if (GroupA.size() > GroupB.size())
		swap(GroupA, GroupB);

	int num = (GroupB.size() - GroupA.size()) / 2;
	for (int i = 0; i < num; ++i) {
		GroupA.push_back(*(GroupB.rbegin()));
		GroupB.pop_back();
	}

	vector<vector<Student> > result;
	vector<Student> special;
	
	for (int i = 0; i < GroupA.size(); i += 2) {
		vector<Student> unit;
		unit.push_back(GroupA[i]);
		unit.push_back(GroupA[i+1]);
		unit.push_back(GroupB[i]);
		unit.push_back(GroupB[i+1]);
		result.push_back(unit);
	}

	return result;
}