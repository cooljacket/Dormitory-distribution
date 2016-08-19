#ifndef __CSV_CONTAINER_ADAPTER_H__
#define __CSV_CONTAINER_ADAPTER_H__

#include <string>
using namespace std;


class CSVContainerAdapter
{
public:
	virtual void addToRow(const string& cell) = 0;
	virtual void addToRowDone() = 0;
	virtual void display() const = 0;
};

#endif