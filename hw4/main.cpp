#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <unordered_map>

using namespace std;

const unsigned PRIME_BASE = 53;
const unsigned PRIME_MOD = 1000000007;

class Problem {

	public:
		Problem();
		~Problem();

		void processRequest();
		void updatePowerTable(const int);
		void constructHashMap(const int);
		void updateHashMap(const bool);
		const long long int getNeedleHashCode(const string&);
		const long long int getRangedHaystackHashCode (const int);
		const int getSubstringCount(const string&);

	private:
		int maxWindowSize;
		deque<char> haystack;
		vector<long long int> powerTable;
		unordered_map<long long int, int> hashMap;

};

Problem::Problem () {
	maxWindowSize = 0;
	powerTable.push_back(1);
}

Problem::~Problem () {
	haystack.clear();
	powerTable.clear();
	hashMap.clear();
}

void Problem::processRequest () {

	char request, modifier;
	int count, result;
	string target, query;

	cin >> target >> count;
	//cout << target << endl;
	//cout << count << endl;
	haystack.assign(target.begin(), target.end());
	//cout << haystack.size() << endl;

	maxWindowSize = 20;
	updatePowerTable(maxWindowSize);
	for (int i = 1; i <= maxWindowSize; i++) {
		constructHashMap(i);
	}
	/*for (unordered_map<long long int, int>::iterator it = hashMap.begin() ; it != hashMap.end(); ++it) {
		cout << it->first << "\t" << it->second << endl;
	}*/

	for (int i = 0; i < count; i++) {
		cin >> request;
		if (request == '1') {
			cin >> modifier;
			haystack.push_front(modifier);
			updateHashMap(true);
		}
		else if (request == '2') {
			cin >> modifier;
			haystack.push_back(modifier);
			updateHashMap(false);
		}
		else {
			cin >> query;
			//cout << query << endl;
			if (powerTable.size() < query.length()) updatePowerTable(query.length());
			/*for (vector<long long int>::iterator it = powerTable.begin() ; it != powerTable.end(); ++it) {
				cout << *it << "\t";
			}
			cout << endl;*/
			if (query.length() > maxWindowSize) {
				result = getSubstringCount(query);
			}
			else {
				auto got = hashMap.find(getNeedleHashCode(query));
				if (got != hashMap.end()) result = got->second;
				else result = 0;
			}
			cout << result << endl;
		}
	}

}

void Problem::updatePowerTable (const int power) {
	for (int i = powerTable.size(); i < power; i++) {
		powerTable.push_back((powerTable[i - 1] * PRIME_BASE) % PRIME_MOD);
	}
}

void Problem::constructHashMap (const int windowSize) {
	if (windowSize > haystack.size()) return;
	long long int hashValue = getRangedHaystackHashCode(windowSize);
	for (int i = 0; i <= haystack.size() - windowSize; i++) {
		//cout << hashValue << "\t";
		unordered_map<long long int, int>::iterator got = hashMap.find(hashValue);
		if (got != hashMap.end()) got->second++;
		else {
			pair<long long int, int> record(hashValue, 1);
			hashMap.insert(record);
		}
		if (i < haystack.size() - windowSize) {
			hashValue = ((hashValue - haystack[i] * powerTable[windowSize - 1]) * PRIME_BASE + haystack[windowSize + i]) % PRIME_MOD;
			if (hashValue < 0) hashValue += PRIME_MOD;
		}
	}
	//cout << endl;
}

void Problem::updateHashMap (const bool isHead) {
	int count = maxWindowSize < (haystack.size() + 1) ? maxWindowSize : (haystack.size() + 1);
	long long int hashValue = 0;
	//cout << count << endl;
	if (isHead) {
		for (int i = 1; i <= count; i++){
			hashValue = 0;
			for (int j = 0; j < i; j++) {
				hashValue += powerTable[i - j - 1] * int(haystack[j]);
				hashValue %= PRIME_MOD;
			}
			//cout << i << ": " << hashValue << endl;
			auto got = hashMap.find(hashValue);
			if (got != hashMap.end()) got->second++;
			else {
				pair<long long int, int> record(hashValue, 1);
				hashMap.insert(record);
			}
		}
	}
	else {
		for (int i = 1; i <= count; i++) {
			hashValue = 0;
			for (int j = 0; j < i; j++) {
				hashValue += powerTable[j] * int(haystack[haystack.size() - 1 - j]);
				hashValue %= PRIME_MOD;
			}
			//cout << i << ": " << hashValue << endl;
			auto got= hashMap.find(hashValue);
			if (got != hashMap.end()) got->second++;
			else {
				pair<long long int, int> record(hashValue, 1);
				hashMap.insert(record);
			}
		}
	}
}

const long long int Problem::getNeedleHashCode (const string& str) {
	long long int result = 0;
	for (int i = 0; i < str.length(); i++) {
		result += powerTable[str.length() - i - 1] * int(str[i]);
		result %= PRIME_MOD;
	}
	return result;
}

const long long int Problem::getRangedHaystackHashCode (const int windowSize) {
	long long int result = 0;
	auto it = haystack.begin();
	for (int i = 0; i < windowSize; i++) {
		result += powerTable[windowSize - i - 1] * int(*it);
		result %= PRIME_MOD;
		it++;
	}
	return result;
}

const int Problem::getSubstringCount (const string& needle) {

	/*cout << "Needle: " << needle << ", Length: " << needle.length() << endl;
	cout << "Haystack: ";
	for (auto it = haystack.begin(); it != haystack.end(); it++) {
		cout << *it;
	}
	cout << ", Length: " << haystack.size() << endl;*/

	if (needle.length() > haystack.size()) return 0;
	int result = 0;
	long long int needleHash = getNeedleHashCode(needle);
	long long int haystackHash = getRangedHaystackHashCode(needle.length());

	for (int i = 0; i <= haystack.size() - needle.length(); i++) {
		//cout << "Needle hash: " << needleHash << " Haystack hash: " << haystackHash << endl;
		if (needleHash == haystackHash) result++;
		if (i < haystack.size() - needle.length()) {
			haystackHash = ((haystackHash - haystack[i] * powerTable[needle.length() - 1]) * PRIME_BASE + haystack[needle.length() + i]) % PRIME_MOD;
			if (haystackHash < 0) haystackHash += PRIME_MOD;
		}
	}

	return result;

}

int main (int argc, char* argv[]) {
	Problem problem;
	problem.processRequest();
}
