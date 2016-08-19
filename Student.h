#ifndef __STUDENT__H
#define __STUDENT__H

#include "Element.h"
#include <iostream>
#include <vector>
using namespace std;

extern int str2int(const string& str);

class Student : public Element
{
	static const int size = 15;
	static const double question_ratio[size];
	static const double hobby_ratio[];
	static const double MIN[size];
	static const double MAX[size];
	static const string answers[size][6];
	string id, name;
	vector<double> raw_data;
	
	
public:
	Student();
	Student(const vector<string>& row);
	friend istream& operator >> (istream& is, Student& stu);
	double sqrt_trans(double x);
	void display() const;
	void output(ostream& out) const;
	int getKind();

	enum KIND {
		BOYS_IN, BOYS_OUT, GIRLS_IN, GIRLS_OUT
	};
};

#endif