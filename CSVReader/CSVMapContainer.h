#ifndef __CSV_MAP_CONTAINER_H__
#define __CSV_MAP_CONTAINER_H__

#include "CSVContainerAdapter.h"
#include <vector>
#include <map>
using namespace std;


class CSVMapContainer : public CSVContainerAdapter
{
public:
	CSVMapContainer(size_t indexOfKeyRow=0);
	void addToRow(const string& cell);
	void addToRowDone();
	void display() const;
	map<string, vector<string> >& getData();
	void getColData(map<string, string>& data, size_t indexOfCol) const;

private:
	vector<string> m_row;
	map<string, vector<string> > m_table;
	size_t m_indexOfKeyRow;
};

#endif