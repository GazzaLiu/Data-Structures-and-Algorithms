#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <unordered_map>

#define BOARD_SIZE 25

using namespace std;

class Problem {

	public:
		Problem();
		~Problem();

		const void processRequest(istream&);
		const void printGameStateBinary(long long int);
		const void printGameStateGraph(long long int);
		const vector<long long int> getSuccessors(long long int, bool);
		const int evaluateBoard (const long long int);
		int solveBoard (long long int, bool, int, int, int);
		const string getResultString (int);

	private:
		unordered_map<long long int, int> database_1;
		unordered_map<long long int, int> database_2;
		unordered_map<long long int, int> database_3;

};

Problem::Problem () {

}

Problem::~Problem () {
	database_1.clear();
	database_2.clear();
	database_3.clear();
}

const void Problem::processRequest (istream& is) {

	long long int gameState = 0;
	string line;
	getline(is, line);
	//cout << "Play count: " << line << endl;

	for (int count = 1; getline(is, line);) {
		for (string::size_type i = 0; i < line.size(); count++, ++i) {
			//cout << count;
			//cout << line[i];
			if (line[i] == 'O') {
				//cout << 'O' << '\t';
				gameState++;
			}
			else if (line[i] == 'X') {
				//cout << 'X' << '\t';
				gameState += 2;
			}
			/*else {
				cout << '.' << '\t';
			}*/
			//printGameStateBinary(gameState);
			if (count == BOARD_SIZE) {
				int empty = 0;
				long long int temp = gameState;
				for (int i = 1; i <= 25; temp >>= 2, i++) {
					if ((temp & 3) == 0) empty++;
				}
				cout << getResultString(solveBoard(gameState, empty % 4 == 1, (25 - empty) / 2, -2, 2));
				cout << endl;
				gameState = 0;
				count = 0;
			}
			else {
				gameState <<= 2;
			}
		}
	}

}

const void Problem::printGameStateBinary (long long int gameState) {
	bitset<BOARD_SIZE * 2> number(gameState);
	cout << number << endl;
}

const void Problem::printGameStateGraph (long long int gameState) {
	for (int pointer = 1; pointer <= BOARD_SIZE; gameState >>= 2, pointer++) {
		int temp = gameState & 3;
		if (temp == 0) {
			cout << '.';
		}
		else if (temp == 1) {
			cout << 'O';
		}
		else if (temp == 2) {
			cout << 'X';
		}
		else {
			cout << '?';
		}
		if (pointer % 5 == 0) {
			cout << endl;
		}
	}
}

const vector<long long int> Problem::getSuccessors (long long int gameState, bool turn) {

	long long int temp = gameState;
	vector<int> empty;

	for (int pointer = 1; pointer <= 25; temp >>= 2, pointer++) {
		if ((temp & 3) == 0) {
			//cout << "Find empty at: " << 26 - pointer << endl;
			empty.push_back(pointer);
		}
	}

	vector<long long int> result;

	if (turn) {
		for (int back = 0; back < empty.size(); back++) {
			for (int front = back + 1; front < empty.size(); front++) {
				//cout << 26 - empty[front] << "," << 26 - empty[back] << endl;
				temp = 1;
				//printGameStateBinary(temp);
				temp <<= (2 * (empty[front] - empty[back]));
				temp |= 1;
				//printGameStateBinary(temp);
				temp <<= (2 * empty[back] - 2);
				//printGameStateBinary(temp);
				//printGameStateBinary(gameState);
				//printGameStateBinary(gameState | temp);
				result.push_back(gameState | temp);
			}
		}
	}
	else {
		for (int back = 0; back < empty.size(); back++) {
			for (int front = back + 1; front < empty.size(); front++) {
				temp = 2;
				temp <<= (2 * (empty[front] - empty[back]));
				temp |= 2;
				temp <<= (2 * empty[back] - 2);
				result.push_back(gameState | temp);
			}
		}
	}

	return result;

}

const int Problem::evaluateBoard (const long long int gameState) {

	int tempScore = 0;
	int score = 0;
	long long int temp = gameState;
	int result;

	//printGameStateGraph(gameState);

	for (int i = 1; i <= BOARD_SIZE; temp >>= 2, i++) {
		if ((temp & 3) == 1) tempScore++;
		else tempScore--;
		if (i % 5 == 0) {
			if (tempScore >= 3) score++;
			else if (tempScore <= -3) score--;
			tempScore = 0;
		}
	}
	//cout << score << endl;

	tempScore = 0;
	for (int i = 1; i <= 5; i++) {
		temp = gameState;
		temp >>= (2 * i) - 2;
		for (int j = 1; j <= 5; temp >>= 10, j++) {
			if ((temp & 3) == 1) tempScore++;
			else tempScore--;
		}
		if (tempScore >= 3) score++;
		else if (tempScore <= -3) score--;
		tempScore = 0;
	}
	//cout << score << endl;

	tempScore = 0;
	temp = gameState;
	for (int i = 1; i <= 5; temp >>= 12, i++) {
		if ((temp & 3) == 1) tempScore++;
		else tempScore--;
	}
	if (tempScore >= 3) score++;
	else if (tempScore <= -3) score--;
	//cout << score << endl;

	tempScore = 0;
	temp = gameState;
	temp >>= 8;
	for (int i = 1; i <= 5; temp >>= 8, i++) {
		if ((temp & 3) == 1) tempScore++;
		else tempScore--;
	}
	if (tempScore >= 3) score++;
	else if (tempScore <= -3) score--;

	//cout << "Score: " << score << endl;
	if (score > 0) {
		result = 1;
	}
	else if (score < 0) {
		result = -1;
	}
	else {
		result = 0;
	}

	//cout << result << endl;
	return result;

}

int Problem::solveBoard (long long int gameState, bool turn, int round, int alpha, int beta) {

	//cout << "Round count: " << round << endl;
	//printGameStateGraph(gameState);
	unordered_map<long long int, int> *pointer;
	unordered_map<long long int, int>::const_iterator got;
	if (beta >= 1 && alpha <= -1) {
		got = database_1.find(gameState);
		if (got != database_1.end()) return got -> second;
		else pointer = &database_1;
	}
	else if (beta == 0 && alpha <= -1) {
		got = database_2.find(gameState);
		if (got != database_2.end()) return got -> second;
		else pointer = &database_2;
	}
	else {
		got = database_3.find(gameState);
		if (got != database_3.end()) return got -> second;
		else pointer = &database_3;
	}

	if (round >= 11) {
		//cout << "Fianl board." << endl;
		return evaluateBoard(gameState);
	}
	round++;

	int result;
	int nextResult;
	vector<long long int> successors(getSuccessors(gameState, turn));

	if (turn) {
		// O's turn
		result = -2;
		for (vector<long long int>::iterator it = successors.begin(); it != successors.end(); ++it) {
			nextResult = solveBoard(*it, !turn, round, alpha, beta);
			result = max(result, nextResult);
			alpha = max(alpha, result);
			if (beta <= alpha) {
				result = alpha;
				break;
			}
		}
	}
	else {
		// X's turn
		result = 2;
		for (vector<long long int>::iterator it = successors.begin(); it != successors.end(); ++it) {
			nextResult = solveBoard(*it, !turn, round, alpha, beta);
			result = min(result, nextResult);
			beta = min(beta, result);
			if (beta <= alpha) {
				result = beta;
				break;
			}
		}
	}

	pair<long long int, int> record (gameState, result);
	(*pointer).insert(record);

	return result;

}

const string Problem::getResultString (int result) {
	if (result > 0) {
		return "O win";
	}
	else if (result < 0) {
		return "X win";
	}
	else {
		return "Draw";
	}
}

int main (int argc, char* argv[]) {
	Problem problem;
	problem.processRequest(cin);
}
