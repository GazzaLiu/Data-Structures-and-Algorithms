#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const unsigned PRIME_MOD = 1000000007;

int main (int argc, char* argv[]) {

	int count, maxCountIndex;
	int maxCount = -1;
	unsigned long long int maxMethodCount;
	vector<long long int> arr;
	vector<int> len;
	vector<unsigned long long int> cnt;
	vector<int> pre;

	scanf("%d", &count);
	arr.push_back(-1);
	for (int i = 0; i < count; i++) {
		long long int temp;
		scanf("%lld", &temp);
		arr.push_back(temp);
	}
	//cout << count << endl;
	//cout << arr.size() << endl;

	// Boundary condition
	len.push_back(-1);
	len.push_back(1);
	cnt.push_back(-1);
	cnt.push_back(1);
	pre.push_back(-1);
	pre.push_back(0);

	// Main loop start from day 2
	for (int i = 2; i < arr.size(); i++) {
		//cout << "Today's count: " << arr[i] << endl;
		int bestCount = 1;
		unsigned long long int methodCount = 1;
		int earliestDay = 0;
		int temp = 1;
		for (int j = 1; j < i; j++) {
			//cout << "temp: " << temp << ", bestCount: " << bestCount << endl;
			if (arr[i] >= arr[j]) {
				temp = len[j] + 1;
				if (temp > bestCount) {
					bestCount = temp;
					methodCount = cnt[j];
					earliestDay = j;
				}
				else if (temp == bestCount) {
					methodCount += cnt[j];
					methodCount %= PRIME_MOD;
				}
			}
		}
		if (bestCount > maxCount) {
			maxCount = bestCount;
			maxCountIndex = i;
			maxMethodCount = methodCount;
		}
		else if (bestCount == maxCount) {
			maxMethodCount += methodCount;
			maxMethodCount %= PRIME_MOD;
		}
		len.push_back(bestCount);
		cnt.push_back(methodCount);
		pre.push_back(earliestDay);
	}

	printf("%d\n%lld\n", maxCount, maxMethodCount);
	stack<int> result;
	while (maxCountIndex != 0) {
		result.push(maxCountIndex);
		maxCountIndex = pre[maxCountIndex];
	}
	while (!result.empty()) {
		if (result.size() != 1) printf("%d ", result.top());
		else printf("%d\n", result.top());
		result.pop();
	}

	/*cout << "len:\t";
	for (vector<int>::iterator it = len.begin(); it != len.end(); it++) {
		cout << *it << "\t";
	}
	cout << endl;
	cout << "cnt:\t";
	for (vector<long long int>::iterator it = cnt.begin(); it != cnt.end(); it++) {
		cout << *it << "\t";
	}
	cout << endl;
	cout << "pre:\t";
	for (vector<int>::iterator it = pre.begin(); it != pre.end(); it++) {
		cout << *it << "\t";
	}
	cout << endl;*/

}
