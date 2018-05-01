#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main (int argc, char* argv[]) {

	int n, m, u, v;

	scanf("%d", &n);
	scanf("%d", &m);

	vector< vector<int> > database(10000);
	//cout << database[0] << endl;

	for (int i = 0; i < m; i++) {
		if (scanf("%d%d", &u, &v) == EOF) break;
		database[u].push_back(v);
	}

	for (vector< vector<int> >::iterator it = database.begin(); it != database.end(); it++) {
		for (vector<int> jt = (*it).begin(); jt != (*it).end(); jt++) {
			jt
		}
	}

	/*while (true) {
		file >> predecessor >> name;
		if (file.eof()) {
			break;
		}
		for (vector<Record*>::iterator it = database.begin(); it != database.end(); it++) {
			if (it->name == name && it->predecessor != predecessor) {
				cout << "no" << endl;
				break;
			}
			if (==) {
				
			}
		}
		struct City *city = new City ({name, predecessor});
		database.push_back(city);
	}
	file.close();
	cout << "yes" << endl;*/

}