#include <iostream>
#include <vector>
#include <fstream>
#include "Student.h"
#include "KMeans.h"

using namespace std;

size_t findNearestExclude(const Student& key, const vector<Student>& group, size_t exclude);
void CombGroupIntoPairs(vector<Student>& group, vector<Student>& comb, vector<pair<Student, Student> >& pairs, vector<Student>& special);
void divide(vector<Student>& GroupA, vector<Student>& GroupB, ostream& out);


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

	fstream girls_output("女生宿舍分配情况.csv", ios::out);
	fstream boys_output("男生宿舍分配情况.csv", ios::out);

	divide(all_stus[Student::GIRLS_IN], all_stus[Student::GIRLS_OUT], girls_output);
	divide(all_stus[Student::BOYS_IN], all_stus[Student::BOYS_OUT], boys_output);

	boys_output.close();
	girls_output.close();

	return 0;
}


/*
[函数功能]
找出group里下标不是exclude的并且与key最相似的人

[参数含义]
key：要比对的对象
group：组内的所有人
exclude：要排除的人在group里的下标
*/
size_t findNearestExclude(const Student& key, const vector<Student>& group, size_t exclude) {
	double d = 1e10;
	size_t ans = exclude;

	for (size_t i = 0; i < group.size(); ++i) {
		if (i != exclude && key.dist(group[i]) < d) {
			d = key.dist(group[i]);
			ans = i;
		}
	}

	return ans;
}


/*
[函数功能]
对group里的所有人按照相似度两两配对

[参数含义]
group：组内的所有人
comb：配对后平均化的特征
pairs：配对的结果
special：落单的人，后续流程会单独对其进行处理
*/
void CombGroupIntoPairs(vector<Student>& group, vector<Student>& comb, vector<pair<Student, Student> >& pairs, vector<Student>& special) {
	random_shuffle(group.begin(), group.end());
	size_t len;
	while ((len = group.size()) >= 2) {
		// 给当前group里最后一个人配对，将配对的结果也交换到group的最后，方便删除
		size_t goal = findNearestExclude(group[len-1], group, len);
		if (goal != len-2)
			swap(group[goal], group[len-2]);
		pairs.push_back(make_pair(group[len-1], group[len-2]));

		// 两者取平均作为组合的特征
		Student tmp(group[len-2]);
		tmp += group[len-1];
		tmp /= 2;
		comb.push_back(tmp);

		// 将两个人从group中删掉
		group.pop_back();
		group.pop_back();
	}

	if (group.size() == 1)
		special.push_back(group[0]);
}


/*
[函数功能]
将GropuA和GroupB划分成每4个人一个宿舍，同一个宿舍的人要尽量满足以下约束：
1）尽量均匀出现在GroupA和GroupB中，比如2个来自A同时两个来自B；
2）同个宿舍的人的各项指标尽量相似，如兴趣爱好相近，生活习惯相近，家庭收入相近等等。
*/
void divide(vector<Student>& GroupA, vector<Student>& GroupB, ostream& out) {
	if (GroupA.size() > GroupB.size())
		swap(GroupA, GroupB);

	// Step 1: 使用kmeans抽取GroupB中尽量不同的人到GroupA中
	int num = (GroupB.size() - GroupA.size()) / 2;
	KMeans<Student> km(GroupB, num, 15);
	km.train_inc();
	km.explain();
	vector<size_t> reps = km.getSortedRepresentative();
	for (int i = reps.size()-1, j=GroupB.size()-1; i >= 0; --i, --j) {
		swap(GroupB[reps[i]], GroupB[j]);
	}
	for (int i = 0; i < num; ++i) {
		GroupA.push_back(*(GroupB.rbegin()));
		GroupB.pop_back();
	}


	// Step 2: 每个组内按相似度两两结合，没法结合的元素单独放到“special宿舍”中
	vector<Student> special;
	vector<Student> CombA, CombB;
	vector<pair<Student, Student> > CombAPairs, CombBPairs;
	CombGroupIntoPairs(GroupA, CombA, CombAPairs, special);
	CombGroupIntoPairs(GroupB, CombB, CombBPairs, special);


	// Step 3: 对于每个两两组合后的“平均者”，CombA在CombB中寻找最相似的，作为同个宿舍的划分
	// 从CombA的最后面开始配对，将CombB中与其最相似的那个交换到尾部，方便降低删除的复杂度
	vector<vector<Student> > result;
	for (int i = CombA.size()-1; i >= 0; --i) {
		vector<Student> unit;
		size_t goal = findNearestExclude(CombA[i], CombB, CombB.size());
		unit.push_back(CombAPairs[i].first);
		unit.push_back(CombAPairs[i].second);
		unit.push_back(CombBPairs[goal].first);
		unit.push_back(CombBPairs[goal].second);
		result.push_back(unit);
		
		if (goal != CombB.size()-1) {
			swap(CombB[goal], *(CombB.rbegin()));
			swap(CombBPairs[goal], *(CombBPairs.rbegin()));
		}
		CombB.pop_back();
		CombBPairs.pop_back();
	}

	// CombB最后的size只可能是0或1
	if (CombB.size() == 1) {
		special.push_back(CombBPairs[0].first);
		special.push_back(CombBPairs[0].second);
	}

	if (!special.empty())
		result.push_back(special);

	out << "宿舍号,学号,性别,生源地,起床时间,就寝时间,性格,兴趣爱好,易受他人影响,家庭人均收入,集体住宿经历,喜欢开空调" << endl;
	for (int i = 0; i < result.size(); ++i) {
		out << i+1;
		for (int j = 0; j < result[i].size(); ++j) {
			out << ',';
			result[i][j].output(out);
		}
		out << endl;
	}
}