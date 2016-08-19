#ifndef __CSV_VECTOR_CONTAINER_H__
#define __CSV_VECTOR_CONTAINER_H__

#include "CSVContainerAdapter.h"
#include <vector>
using namespace std;


class CSVVectorContainer : public CSVContainerAdapter
{
public:
	void addToRow(const string& cell);
	void addToRowDone();
	void display() const;
	vector<vector<string> >& getData();
	void getColData(vector<string>& data, size_t indexOfCol) const;

private:
	vector<string> m_row;
	vector<vector<string> > m_table;
};

#endif