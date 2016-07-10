#include "Element.h"

Element::Element() {}

Element::Element(size_t size, const double ratio[])
: data(size), weights(size) {
	for (int i = 0; i < size; ++i)
		weights[i] = ratio[i];
}


double Element::dist(const Element& e) const {
	double d = 0.0, tmp;
	for (size_t i = 0; i < data.size(); ++i) {
		tmp = data[i] - e.data[i];
		d += tmp * tmp * weights[i];
	}

	return d;
}

void Element::clear() {
	for (size_t i = 0; i < data.size(); ++i)
		data[i] = 0.0;
}


Element& Element::operator += (const Element& e) {
	for (size_t i = 0; i < data.size(); ++i)
		data[i] += e.data[i];
	return *this;
}


Element& Element::operator /= (double divisor) {
	for (size_t i = 0; i < data.size(); ++i)
		data[i] /= divisor;
	return *this;
}


void Element::display() const {
	for (size_t i = 0; i < data.size(); ++i)
		printf("%.3lf%c", data[i], ((i == data.size()-1) ? '\n' : ' '));
}