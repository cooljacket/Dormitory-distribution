#ifndef __CSV_READER_H__
#define __CSV_READER_H__

#include "CSVContainerAdapter.h"

#include <vector>
#include <fstream>
using namespace std;

class CSVReader
{
public:
	static void read(const char* fileName, CSVContainerAdapter* adapter, bool haveHeader=true);
	static void set_cell_delimiter(char delimiter);
	static void set_line_delimiter(char delimiter);

private:
	static char cell_delimiter, line_delimiter;
	static const char DOUBLE_QUOTS = '"';

	static void line_to_cells(const string& line, CSVContainerAdapter* adapter);
	static void escape_double_quots(string& str);
};

#endif