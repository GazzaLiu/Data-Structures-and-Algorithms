#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

#define BUFFER_SIZE 256

using namespace std;

struct Record {
	string date;
	string currency;
	string exchange;
	float low;
	float high;
	long long caps;
};

class Dictionary {

	public:
		vector<Record> data;

		Dictionary(char*);
		~Dictionary();

		void processRequest ();
		//void processRequest (char*, char*);
		int queryFind (const string, const string, const string);
		float priceFind(const string, const string, const string);
		long long capsFind (const string, const string);
		void printAll() const;
		//void writeAll(char*) const;

	private:
		void sort();
		static bool dateCompare(const Record&, const Record&);
		static bool currencyCompare(const Record&, const Record&);
		static bool exchangeCompare(const Record&, const Record&);

};

Dictionary::Dictionary (char* fileName) {
	// read data file
	fstream file;
	string date, currency, exchange, low, high, caps;
	//char line[BUFFER_SIZE];
	file.open(fileName, ios::in);
	if (!file) {
		cout << "Reading file: [" << fileName << "] failed." << endl;
		return;
	}
	// construct data vector
	while (true) {
		//cout << file << endl;
		file >> date >> currency >> exchange >> low >> high >> caps;
		if (file.eof()) {
			break;
		}
		data.push_back({date, currency, exchange, stof(low), stof(high), stoll(caps)});
	}
	file.close();
	//cout << "Reading file: [" << fileName << "] finished." << endl;
	sort();
}

Dictionary::~Dictionary () {
	data.clear();
}

void Dictionary::sort () {
	// stable sort
	stable_sort(data.begin(), data.end(), exchangeCompare);
	stable_sort(data.begin(), data.end(), currencyCompare);
	stable_sort(data.begin(), data.end(), dateCompare);
	//cout << "Sorting data finished." << endl;
}

bool Dictionary::dateCompare (const Record& data_1, const Record& data_2) {
	if (data_1.date < data_2.date) {
		return true;
	}
	else {
		return false;
	}
}

bool Dictionary::currencyCompare (const Record& data_1, const Record& data_2) {
	if (data_1.currency < data_2.currency) {
		return true;
	}
	else {
		return false;
	}
}

bool Dictionary::exchangeCompare (const Record& data_1, const Record& data_2) {
	if (data_1.exchange < data_2.exchange) {
		return true;
	}
	else {
		return false;
	}
}

void Dictionary::processRequest () {

	/*fstream fin;
	fstream fout;
	fin.open(inputFileName, ios::in);
	fout.open(outputFileName, ios::out | ios::trunc);
	if (!fin || !fout) {
		cout << "Open file failed." << endl;
		return;
	}
	cout << "Received request file: [" << inputFileName << "]" << endl;*/

	string request, date, currency, exchange, type;
	cout << fixed << setprecision(4);

	while (true) {
		cin >> request;
		if (request == "query") {
			cin >> date >> currency >> exchange;
			int index = queryFind(date, currency, exchange);
			if (index == -1) {
				cout << "none" << endl;
			}
			else {
				cout << data[index].low << ' ' << data[index].high << ' ' << data[index].caps << endl;
			}
		}
		else if (request == "price") {
			cin >> type >> date >> currency;
			float result = priceFind(type, date, currency);
			if (result >= 0) {
				cout << result << endl;
			}
			else {
				cout << "none" << endl;
			}
		}
		else if (request == "cap") {
			cin >> date >> exchange;
			//cout << capsFind(date, exchange) << endl;
			int result = capsFind(date, exchange);
			if (result >= 0) {
				cout << result << endl;
			}
			else {
				cout << "none" << endl;
			}
		}
		else if (request == "end") {
			//cout << "End request program." << endl;
			break;
		}
		else {
			//cout << "Unknown command: [" << request << "]" << endl;
			//cout << "none" << endl;
		}
	}

}

int Dictionary::queryFind (const string date, const string currency, const string exchange) {
	// binary search
	//printRecord(data);
	struct Record key = {.date = date, .currency = currency, .exchange = exchange};
	vector<Record>::iterator lower;
	vector<Record>::iterator upper;
	lower = lower_bound(data.begin(), data.end(), key, dateCompare);
	upper = upper_bound(lower, data.end(), key, dateCompare);
	//cout << "Date lower bound at position: " << (lower - data.begin()) << endl;
	//cout << "Date upper bound at position: " << (upper - data.begin()) << endl;
	lower = lower_bound(lower, upper, key, currencyCompare);
	upper = upper_bound(lower, upper, key, currencyCompare);
	//cout << "Currency lower bound at position: " << (lower - data.begin()) << endl;
	//cout << "Currency upper bound at position: " << (upper - data.begin()) << endl;
	lower = lower_bound(lower, upper, key, exchangeCompare);
	upper = upper_bound(lower, upper, key, exchangeCompare);
	//cout << "Exchange lower bound at position: " << (lower - data.begin()) << endl;
	//cout << "Exchange upper bound at position: " << (upper - data.begin()) << endl;
	if (upper <= lower) { // cannot find data
		return -1;
	}
	else {
		return lower - data.begin(); // find data
	}
}

float Dictionary::priceFind (const string type, const string date, const string currency) {
	struct Record key = {.date = date, .currency = currency};
	vector<Record>::iterator lower;
	vector<Record>::iterator upper;
	lower = lower_bound(data.begin(), data.end(), key, dateCompare);
	upper = upper_bound(lower, data.end(), key, dateCompare);
	lower = lower_bound(lower, upper, key, currencyCompare);
	upper = upper_bound(lower, upper, key, currencyCompare);
	if (upper <= lower) { // cannot find data
		return -1;
	}
	//cout << lower - data.begin() << endl;
	if (type == "min") {
		float result = (*lower).low;
		//cout << result << endl;
		for (; lower != upper; ++lower) {
			float record = (*lower).low;
			if (record < result) {
				result = record;
			}
		}
		return result;
	}
	else if (type == "max") {
		float result = (*lower).high;
		for (; lower != upper; ++lower) {
			float record = (*lower).high;
			if (record > result) {
				result = record;
			}
		}
		return result;
	}
	else {
		cout << "Unknown price type: [" << type << "]" << endl;
		return -1;
	}
}

long long Dictionary::capsFind (const string date, const string exchange) {
	// binary search
	struct Record key = {.date = date};
	vector<Record>::iterator lower;
	vector<Record>::iterator upper;
	lower = lower_bound(data.begin(), data.end(), key, dateCompare);
	upper = upper_bound(lower, data.end(), key, dateCompare);
	// linear search
	bool isFind = false;
	long long sum = 0;
	for (; lower != upper; ++lower) {
		if ((*lower).exchange == exchange) {
			sum += (*lower).caps;
			isFind = true;
		}
	}
	if (!isFind) { // cannot find data
		return -1;
	}
	return sum;
}

void Dictionary::printAll () const {
	for (int i = 0; i < data.size(); i++) {
		cout << data.at(i).date << '\t' << data.at(i).currency << '\t' << data.at(i).exchange << '\t' << data.at(i).low << '\t' << data.at(i).high << '\t' << data.at(i).caps << '\t' << endl;
	}
}

/*void Dictionary::writeAll (char* fileName) const {
	fstream file;
	file.open(fileName, ios::out | ios::trunc);
	if (!file) {
		cout << "Writing file: [" << fileName << "] failed." << endl;
		return;
	}
	for (int i = 0; i < data.size(); i++) {
		file << data.at(i).date << '\t' << data.at(i).currency << '\t' << data.at(i).exchange << '\t' << data.at(i).low << '\t' << data.at(i).high << '\t' << data.at(i).caps << endl;
	}
	file.close();
	cout << "Writing file: [" << fileName << "] finished." << endl;
}*/

int main (int argc, char* argv[]) {
	Dictionary dictionary(argv[1]);
	//dictionary.writeAll(argv[2]);
	dictionary.processRequest();
}
