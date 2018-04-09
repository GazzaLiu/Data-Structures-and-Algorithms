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
	long long int caps;
};

class Dictionary {

	public:
		vector<Record*> data_1;
		vector<Record*> data_3;

		Dictionary(char*);
		~Dictionary();

		void processRequest ();
		//void processRequest (char*, char*);
		int queryFind (const string, const string, const string);
		float priceFind(const string, const string, const string);
		long long int capsFind (const string, const string);
		//void printAll() const;
		//void writeAll(char*) const;

	private:
		void sort();
		static bool dateCompare(const Record*, const Record*);
		static bool currencyCompare(const Record*, const Record*);
		static bool exchangeCompare(const Record*, const Record*);

};

Dictionary::Dictionary (char* fileName) {
	fstream file;
	string date, currency, exchange, low, high, caps;
	file.open(fileName, ios::in);
	if (!file) {
		//cout << "Reading file: [" << fileName << "] failed." << endl;
		return;
	}
	for (string line; getline(file, line);) {
	if (file.eof()) {
			break;
	}
	string request[6] = {"", "", "", "", "", ""};
	int tabCount = 5;
	for (string::size_type i = 0; i < line.size(); ++i) {
		if (line[i] == '\t' && tabCount > 0) {
			tabCount--;
		}
		else {
			request[5 - tabCount] += line[i];
		}
	}
	struct Record *record = new Record ({request[0], request[1], request[2], stof(request[3]), stof(request[4]), stoll(request[5])});
	data_1.push_back(record);
	}
	/*while (true) {
		//cout << file << endl;
		file >> date >> currency >> exchange >> low >> high >> caps;
		if (file.eof()) {
			break;
		}
		struct Record *record = new Record ({date, currency, exchange, stof(low), stof(high), stoll(caps)});
		data_1.push_back(record);
	}*/
	file.close();
	//cout << "Reading file: [" << fileName << "] finished." << endl;
	sort();
}

Dictionary::~Dictionary () {
	data_1.clear();
	data_3.clear();
}

void Dictionary::sort () {
	// stable sort
	stable_sort(data_1.begin(), data_1.end(), exchangeCompare);
	data_3.assign(data_1.begin(), data_1.end());
	stable_sort(data_1.begin(), data_1.end(), currencyCompare);
	stable_sort(data_1.begin(), data_1.end(), dateCompare);
	stable_sort(data_3.begin(), data_3.end(), dateCompare);
	//cout << "Sorting data finished." << endl;
}

bool Dictionary::dateCompare (const Record* previousData, const Record* postData) {
	if (previousData->date < postData->date) {
		return true;
	}
	else {
		return false;
	}
}

bool Dictionary::currencyCompare (const Record* previousData, const Record* postData) {
	if (previousData->currency < postData->currency) {
		return true;
	}
	else {
		return false;
	}
}

bool Dictionary::exchangeCompare (const Record* previousData, const Record* postData) {
	if (previousData->exchange < postData->exchange) {
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

	//string request, date, currency, exchange, type = "";
	cout << fixed << setprecision(4);

	/*while (true) {*/
	for (string line; getline(cin, line);) {
		string request[4] = {"", "", "", ""};
		int tabCount = 3;
		for (string::size_type i = 0; i < line.size(); ++i) {
			if (line[i] == '\t' && tabCount > 0) {
				tabCount--;
			}
			else {
				request[3 - tabCount] += line[i];
			}
		}
		//cin >> request[0];
		if (request[0] == "query") {
			//cin >> request[1] >> request[2] >> request[3];
			int index = queryFind(request[1], request[2], request[3]);
			if (index == -1) {
				cout << "none" << endl;
			}
			else {
				cout << data_1[index]->low << ' ' << data_1[index]->high << ' ' << data_1[index]->caps << endl;
			}
		}
		else if (request[0] == "price") {
			//cin >> request[1] >> request[2] >> request[3];
			float result = priceFind(request[1], request[2], request[3]);
			if (result >= 0) {
				cout << result << endl;
			}
			else {
				cout << "none" << endl;
			}
		}
		else if (request[0] == "cap") {
			//cin >> request[1] >> request[2];
			int result = capsFind(request[1], request[2]);
			if (result >= 0) {
				cout << result << endl;
			}
			else {
				cout << "none" << endl;
			}
		}
		else if (request[0] == "end") {
			//cout << "End request program." << endl;
			break;
		}
		else {
			//cout << "Unknown command: [" << request << "]" << endl;
			cout << "none" << endl;
		}
	}

}

int Dictionary::queryFind (const string date, const string currency, const string exchange) {
	//printRecord(data);
	struct Record *key = new Record ({.date = date, .currency = currency, .exchange = exchange});
	vector<Record*>::iterator lower;
	vector<Record*>::iterator upper;
	lower = lower_bound(data_1.begin(), data_1.end(), key, dateCompare);
	upper = upper_bound(lower, data_1.end(), key, dateCompare);
	//cout << "Date lower bound at position: " << (lower - data.begin()) << endl;
	//cout << "Date upper bound at position: " << (upper - data.begin()) << endl;
	if (upper <= lower) { // cannot find data
		return -1;
	}
	lower = lower_bound(lower, upper, key, currencyCompare);
	upper = upper_bound(lower, upper, key, currencyCompare);
	//cout << "Currency lower bound at position: " << (lower - data.begin()) << endl;
	//cout << "Currency upper bound at position: " << (upper - data.begin()) << endl;
	if (upper <= lower) { // cannot find data
		return -1;
	}
	lower = lower_bound(lower, upper, key, exchangeCompare);
	upper = upper_bound(lower, upper, key, exchangeCompare);
	//cout << "Exchange lower bound at position: " << (lower - data.begin()) << endl;
	//cout << "Exchange upper bound at position: " << (upper - data.begin()) << endl;
	if (upper <= lower) { // cannot find data
		return -1;
	}
	return lower - data_1.begin(); // find data
}

float Dictionary::priceFind (const string type, const string date, const string currency) {
	struct Record *key = new Record ({.date = date, .currency = currency});
	vector<Record*>::iterator lower;
	vector<Record*>::iterator upper;
	lower = lower_bound(data_1.begin(), data_1.end(), key, dateCompare);
	upper = upper_bound(lower, data_1.end(), key, dateCompare);
	if (upper <= lower) { // cannot find data
		return -1;
	}
	lower = lower_bound(lower, upper, key, currencyCompare);
	upper = upper_bound(lower, upper, key, currencyCompare);
	if (upper <= lower) { // cannot find data
		return -1;
	}
	//cout << lower - data.begin() << endl;
	if (type == "min") {
		float result = (*lower)->low;
		//cout << result << endl;
		for (; lower != upper; lower++) {
			float record = ((*lower)->low);
			if (record < result) {
				result = record;
			}
		}
		return result;
	}
	else if (type == "max") {
		float result = (*lower)->high;
		for (; lower != upper; lower++) {
			float record = ((*lower)->high);
			if (record > result) {
				result = record;
			}
		}
		return result;
	}
	else {
		//cout << "Unknown price type: [" << type << "]" << endl;
		return -1;
	}
}

long long int Dictionary::capsFind (const string date, const string exchange) {
	/*Record *key = new Record();
	key->date = date;
	key->exchange = exchange;
	vector<Record*>::iterator lower;
	vector<Record*>::iterator upper;
	lower = lower_bound(data_3.begin(), data_3.end(), key, dateCompare);
	upper = upper_bound(lower, data_3.end(), key, dateCompare);
	//cout << "Date lower bound at position: " << (lower - data_3.begin()) << endl;
	//cout << "Date upper bound at position: " << (upper - data_3.begin()) << endl;
	if (upper <= lower) { // cannot find data
		return -1;
	}
	lower = lower_bound(lower, upper, key, exchangeCompare);
	upper = upper_bound(lower, upper, key, exchangeCompare);
	//cout << "Exchange lower bound at position: " << (lower - data_3.begin()) << endl;
	//cout << "Exchange upper bound at position: " << (upper - data_3.begin()) << endl;
	if (upper <= lower) { // cannot find data
		return -1;
	}
	long long int sum = 0;
	for (; lower != upper; lower++) {
		sum += ((*lower)->caps);
	}
	return sum;*/
	Record *key = new Record();
	key->date = date;
	vector<Record*>::iterator lower = lower_bound(data_3.begin(), data_3.end(), key, dateCompare);
	if (!(lower!=data_3.end() && !(key->date<(*lower)->date))) { // cannot find data
		return -1;
	}
	bool isFind = false;
	long long int sum = 0;
	for (; lower != data_3.end(); ++lower) {
		//cout << ((*lower)->date) << ((*lower)->exchange) << ((*lower)->caps) << endl;
		if (((*lower)->exchange) == exchange) {
			sum += ((*lower)->caps);
			isFind = true;
		}
		else if (isFind && ((*lower)->exchange) != exchange) {
			break;
		}
	}

	return sum;
}

/*void Dictionary::printAll () const {
	for (int i = 0; i < data.size(); i++) {
		cout << data.at(i).date << '\t' << data.at(i).currency << '\t' << data.at(i).exchange << '\t' << data.at(i).low << '\t' << data.at(i).high << '\t' << data.at(i).caps << '\t' << endl;
	}
}*/

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
