#include "CSVReader.h"


CSVReader::CSVReader()
: cell_delimiter(','), line_delimiter('\n')
{}


void CSVReader::read(const char* fileName, vector<vector<string> >& data, bool haveHeader) {
	fstream in(fileName, ios::in);
	string line;

	if (haveHeader)
		getline(in, line, line_delimiter);

	while (getline(in, line, line_delimiter)) {
		vector<string> cells;
		line_to_cells(line, cells);
		data.push_back(cells);
	}

	in.close();
}


void CSVReader::line_to_cells(const string& line, vector<string>& cells) {
	bool half_cell = false, have_comma = false;
	int now = -1, left = 0, len = line.length();
	while (++now <= len) {
		have_comma = have_comma || (line[now] == cell_delimiter);
		if (now == len || (have_comma && !half_cell)) {
			cells.push_back(line.substr(left, now-left));
			left = now + 1;
			have_comma = false;
			continue;
		}

		if (line[now] == DOUBLE_QUOTS) {
			if (!half_cell)
				half_cell = true;
			else if (now < len-1 && line[now+1] != DOUBLE_QUOTS) {
				++now;
				string cell = line.substr(left, now-left);
				escape_double_quots(cell);
				cells.push_back(cell);
				left = now + 1;
				have_comma = false;
				half_cell = false;
			} else
				++now;
		}
	}
}


void CSVReader::set_cell_delimiter(char delimiter) {
	cell_delimiter = delimiter;
}


void CSVReader::set_line_delimiter(char delimiter) {
	line_delimiter = delimiter;
}


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