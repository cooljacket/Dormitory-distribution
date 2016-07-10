#ifndef __STUDENT__H
#define __STUDENT__H

#include "Element.h"
#include <istream>
#include <vector>
using namespace std;

class Student : public Element
{
	static const int size = 15;
	static const double question_ratio[size];
	static const double hobby_ratio[];
	static const double MIN[size];
	static const double MAX[size];
	static const string answers[size][6];
	int id;
	vector<double> raw_data;
	
	
public:
	Student();
	friend istream& operator >> (istream& is, Student& stu);
	double sqrt_trans(double x);
	void display() const;
	void output() const;
	int getKind();

	enum KIND {
		BOYS_IN, BOYS_OUT, GIRLS_IN, GIRLS_OUT
	};
};

#endif