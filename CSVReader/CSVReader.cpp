#include "CSVReader.h"

char CSVReader::cell_delimiter = ',';
char CSVReader::line_delimiter= '\n';


// read the original csv file data into the Container
void CSVReader::read(const char* fileName, CSVContainerAdapter* adapter, bool haveHeader) {
	fstream in(fileName, ios::in);
	string line;

	if (haveHeader)
		getline(in, line, line_delimiter);

	while (getline(in, line, line_delimiter)) {
		line_to_cells(line, adapter);
	}

	in.close();
}


// split a line to be a sort of cells according to CSV format
void CSVReader::line_to_cells(const string& line, CSVContainerAdapter* adapter) {
	bool half_cell = false, have_comma = false;
	int now = -1, left = 0, len = line.length();
	string cell;

	while (++now <= len) {
		have_comma = have_comma || (line[now] == cell_delimiter);
		if (now == len || (have_comma && !half_cell)) {
			adapter->addToRow(cell);
			cell.clear();
			left = now + 1;
			have_comma = false;
			continue;
		}

		if (line[now] == DOUBLE_QUOTS) {
			if (!half_cell)
				half_cell = true;
			else if (now < len-1 && line[now+1] != DOUBLE_QUOTS) {
				++now;
				adapter->addToRow(cell);
				cell.clear();
				left = now + 1;
				have_comma = false;
				half_cell = false;
			} else {
				cell.push_back(line[now++]);
			}
			continue;
		}

		cell.push_back(line[now]);
	}
	adapter->addToRowDone();
}


void CSVReader::set_cell_delimiter(char delimiter) {
	cell_delimiter = delimiter;
}


void CSVReader::set_line_delimiter(char delimiter) {
	line_delimiter = delimiter;
}


// not used now
// To DO: escap the double quotions in the str
void CSVReader::escape_double_quots(string& str) {
	string tmp;
	bool last_is_quot = false;
	int len = str.length();
	for (int i = 0; i < len; ++i) {
		if (last_is_quot && str[i] == DOUBLE_QUOTS) {
			tmp.erase(tmp.size()-1, 1);
			last_is_quot = false;
		} else {
			last_is_quot = str[i] == DOUBLE_QUOTS;
			tmp.push_back(str[i]);
		}
	}

	str = tmp;
}