#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

struct Record {
	string date, currency, exchange;
	float low, high;
	long long int caps;
};

class Dictionary {

	public:
		vector<Record*> data_1;
		vector<Record*> data_3;

		Dictionary(char*);
		~Dictionary();

		void processRequest ();
		int queryFind (const string, const string, const string);
		float priceFind(const string, const string, const string);
		long long int capsFind (const string, const string);
		//void printAll() const;
		//void writeAll(char*) const;

	private:
		void sort();
		static bool compare_1(const Record*, const Record*);
		static bool compare_2(const Record*, const Record*);
		static bool compare_3(const Record*, const Record*);

};

Dictionary::Dictionary (char* fileName) {
	fstream file;
	string date, currency, exchange, low, high, caps;
	file.open(fileName, ios::in);
	if (!file) {
		//cout << "Reading file: [" << fileName << "] failed." << endl;
		return;
	}
	while (true) {
		//cout << file << endl;
		file >> date >> currency >> exchange >> low >> high >> caps;
		if (file.eof()) {
			break;
		}
		struct Record *record = new Record ({date, currency, exchange, stof(low), stof(high), stoll(caps)});
		data_1.push_back(record);
		data_3.push_back(record);
	}
	file.close();
	//cout << "Reading file: [" << fileName << "] finished." << endl;
	sort();
}

Dictionary::~Dictionary () {
	data_1.clear();
	data_3.clear();
}

void Dictionary::sort () {
	stable_sort(data_1.begin(), data_1.end(), compare_1);
	stable_sort(data_3.begin(), data_3.end(), compare_3);
}

bool Dictionary::compare_1 (const Record* record_1, const Record* record_2) {
	if (record_1->date != record_2->date)
		return record_1->date < record_2->date;
	else if (record_1->currency != record_2->currency)
		return record_1->currency < record_2->currency;
	else
		return record_1->exchange < record_2->exchange;
}

bool Dictionary::compare_2 (const Record* record_1, const Record* record_2) {
	if (record_1->date != record_2->date)
		return record_1->date < record_2->date;
	else
		return record_1->currency < record_2->currency;
}

bool Dictionary::compare_3 (const Record* record_1, const Record* record_2) {
	if (record_1->date != record_2->date)
		return record_1->date < record_2->date;
	else
		return record_1->exchange < record_2->exchange;
}

void Dictionary::processRequest () {

	cout << fixed << setprecision(4);
	for (string line; getline(cin, line);) {
		int tabCount = 3;
		string request[4] = {"", "", "", ""};
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
			long long int result = capsFind(request[1], request[2]);
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
	struct Record *key = new Record ({.date = date, .currency = currency, .exchange = exchange});
	vector<Record*>::iterator lower = lower_bound(data_1.begin(), data_1.end(), key, compare_1);
	vector<Record*>::iterator upper = upper_bound(lower, data_1.end(), key, compare_1);
	if (upper <= lower) {
		return -1;
	}
	return lower - data_1.begin();
}

float Dictionary::priceFind (const string type, const string date, const string currency) {
	struct Record *key = new Record ({.date = date, .currency = currency, .exchange = ""});
	vector<Record*>::iterator lower = lower_bound(data_1.begin(), data_1.end(), key, compare_2);
	vector<Record*>::iterator upper = upper_bound(lower, data_1.end(), key, compare_2);
	if (upper <= lower) {
		return -1;
	}
	//cout << lower - data.begin() << endl;
	if (type == "min") {
		float result = (*lower)->low;
		//cout << result << endl;
		for (; lower != upper; ++lower) {
			float record = ((*lower)->low);
			if (record < result) {
				result = record;
			}
		}
		return result;
	}
	else if (type == "max") {
		float result = (*lower)->high;
		for (; lower != upper; ++lower) {
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
	struct Record *key = new Record ({.date = date, .currency = "", .exchange = exchange});
	vector<Record*>::iterator lower = lower_bound(data_3.begin(), data_3.end(), key, compare_3);
	vector<Record*>::iterator upper = upper_bound(lower, data_3.end(), key, compare_3);
	if (upper <= lower) {
		return -1;
	}
	long long int sum = 0;
	for (; lower != upper; ++lower) {
		sum += ((*lower)->caps);
	}
	return sum;
}

/*void Dictionary::printAll () const {
	for (int i = 0; i < data.size(); i++) {
		cout << data.at(i).date << '\t' << data.at(i).currency << '\t' << data.at(i).exchange << '\t' << data.at(i).low << '\t' << data.at(i).high << '\t' << data.at(i).caps << '\t' << endl;
	}
}

void Dictionary::writeAll (char* fileName) const {
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
	dictionary.processRequest();
}
