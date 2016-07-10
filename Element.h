#ifndef __ELEMENT__H
#define __ELEMENT__H

#include <stdio.h>
#include <vector>
using namespace std;

class Element
{
protected:
	vector<double> data;
	vector<double> weights;

public:
	Element();

	Element(size_t size, const double ratio[]);
	
	// Element(const vector<double>& raw_data)
	// : data(raw_data) {}


	double dist(const Element& e);
	void clear();
	Element& operator += (const Element& e);
	Element& operator /= (double divisor);
	void display() const;
};

#endif