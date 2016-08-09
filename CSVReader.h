#ifndef __CSV_READER_H__
#define __CSV_READER_H__

#include <vector>
#include <fstream>
using namespace std;

class CSVReader
{
public:
	CSVReader();
	void read(const char* fileName, vector<vector<string> >& data, bool haveHeader=true);
	void set_cell_delimiter(char delimiter);
	void set_line_delimiter(char delimiter);

private:
	char cell_delimiter, line_delimiter;
	static const char DOUBLE_QUOTS = '"';

	void line_to_cells(const string& line, vector<string>& cells);
	void escape_double_quots(string& str);
};

#endif