#include <stdio.h>
#include <stack>
#include <queue>
#include <string>

using namespace std;

int main (int argc, char* argv[]) {

	int n, request, value;
	bool isStack = true;
	bool isQueue = true;
	stack<int> stack;
	queue<int> queue;

	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		if (scanf("%d%d", &request, &value) == EOF) break;
		//printf("%d %d\n", request, value);
		if (request == 1) {
			if (isStack) stack.push(value);
			if (isQueue) queue.push(value);
		}
		else {
			if (isStack && stack.top() != value) isStack = false;
			if (isQueue && queue.front() != value) isQueue = false;
			stack.pop();
			queue.pop();
		}
		if (!isStack && !isQueue) break;
	}
	//printf("%d %d\n", isStack, isQueue);

	if (isStack && isQueue) {
		printf("both\r\n");
	}
	else if (isStack && !isQueue) {
		printf("stack\r\n");
	}
	else if (!isStack && isQueue) {
		printf("queue\r\n");
	}
	else {
		printf("neither\r\n");
	}

}