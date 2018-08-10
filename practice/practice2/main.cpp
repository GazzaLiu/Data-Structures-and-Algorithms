#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int main (int argc, char* argv[]) {

	int n;
	scanf("%d", &n);
	long long int* sequence = new long long int[n];

	long long int torque = 0;
	long long int weightSum = 0;
	for (int i = 0; i < n; i++) {
		long long int a;
		scanf("%lld", &a);
		//cout << a << "\t";
		sequence[i] = a;
		torque += a * i;
		weightSum += a;
	}
	//cout << endl << "Torque: " << torque << ", Weight sum: " << weightSum << endl;

	//int x = floor(n / 2) > 1 ? floor(n / 2) : 1;
	//cout << "X: " << x << endl;
	for (int i = 0; i < n; i++) {
		if (torque % weightSum == 0) {
			//cout << torque;
			printf("%d %d", i, (int)(torque / weightSum));
			break;
		}
		torque += (n - 2 * i - 1) * (sequence[i] - sequence[n - 1 - i]);
		//cout << torque << "\t" << weightSum << endl;
	}

}
