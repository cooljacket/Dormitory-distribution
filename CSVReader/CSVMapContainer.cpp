#include "CSVMapContainer.h"
#include <iostream>
#include <stdexcept>
using namespace std;



CSVMapContainer::CSVMapContainer(size_t indexOfKeyRow)
: m_indexOfKeyRow(indexOfKeyRow) {}



void CSVMapContainer::addToRow(const string& cell) {
	m_row.push_back(cell);
}


void CSVMapContainer::addToRowDone() {
	if (m_indexOfKeyRow >= m_row.size())
		throw logic_error("The key's index is large than the size of row.");
	if (m_table.find(m_row[m_indexOfKeyRow]) != m_table.end())
		throw logic_error("The key is duplicate.");
	m_table[m_row[m_indexOfKeyRow]] = m_row;
	m_row.clear();
}


void CSVMapContainer::display() const {
	map<string, vector<string> >::const_iterator it = m_table.begin();
	while (it != m_table.end()) {
		const vector<string>& row = it->second;
		for (int i = 0; i < row.size(); ++i)
			cout << row[i] << '\t';
		cout << endl;
		++it;
	}
}



map<string, vector<string> >& CSVMapContainer::getData() {
	return m_table;
}


void CSVMapContainer::getColData(map<string, string>& data, size_t indexOfCol) const {
	map<string, vector<string> >::const_iterator it = m_table.begin();
	while (it != m_table.end()) {
		const vector<string>& row = it->second;
		if (indexOfCol >= row.size())
			throw logic_error("The index of column is large than the row's size.");
		data[it->first] = row[indexOfCol];
		++it;
	}
}