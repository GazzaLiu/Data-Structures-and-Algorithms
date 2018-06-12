#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string>
#include <bitset>
#include <unordered_map>

using namespace std;

const int N = 24;
const double EPSILON = 0.000001;

template<typename map_key, typename map_val>
void printUnorderedMap(std::unordered_map<map_key, map_val> const &map) {
	for (auto const& pair : map) {
		std::cout << pair.first << " => " << pair.second << endl;
	}
}

class Problem {

	public:
		Problem();
		~Problem();

		void addPoint(const int, const pair<long long int, long long int>);
		const bool isDoubleEqual(const double, const double);
		const bool isFormParabola(const pair<long long int, long long int>&, const pair<long long int, long long int>&);
		const bitset<N> getNextState(const bitset<N>&, const bitset<N>&);
		int getLeastParabola(bitset<N>);
		int solve();

	private:
		unordered_map<int, pair<long long int, long long int>> pointMap;
		unordered_map<bitset<N>, bitset<N>> parabolaMap;
		unordered_map<bitset<N>, int> stateMap; // For DP

};

Problem::Problem () {

}

Problem::~Problem () {
	pointMap.clear();
	parabolaMap.clear();
	stateMap.clear();
}

void Problem::addPoint (const int index, const pair<long long int, long long int> point) {
	pointMap.insert({index, point});
}

const bool Problem::isDoubleEqual (const double number_1, const double number_2) {
	return fabs(number_1 - number_2) <= EPSILON;
}

const bool Problem::isFormParabola (const pair<long long int, long long int> &point_a, const pair<long long int, long long int> &point_b) {

	//cout << "Check a: (" << point_a.first << ", " << point_a.second << "), b: (" << point_b.first << ", " << point_b.second << ") could form parabola." << endl;
	if (point_a.first == point_b.first) return false; // If a.y = b.y

	double m_a = (double)point_a.second / point_a.first;
	double v_b = ((double)point_b.second - point_a.second) / (point_b.first - point_a.first);
	if (v_b >= m_a) return false;

	return true;

}

const bitset<N> Problem::getNextState (const bitset<N> &state, const bitset<N> &parabola) {

	//cout << "State: " << state << "\t" << "Parabola: " << parabola << endl;
	pair<long long int, long long int> point_a, point_b;
	pair<long long int, long long int>* pointer = &point_a;
	for (int i = 0; i < pointMap.size(); i++) {
		if (parabola[i] == 1) {
			*pointer = pointMap.find(i)->second;
			if (pointer == &point_a) {
				pointer = &point_b;
			}
			else {
				break;
			}
		}
	}

	bitset<N> result(state);
	if (!isFormParabola(point_a, point_b)) {
		for (int i = 0; i < pointMap.size(); i++) {
			if (result[i] == 1) {
				result[i] = 0;
				//cout << "Result: " << result << endl;
				return result;
			}
		}
	}

	result &= (~parabola);
	//cout << "Result: " << result << endl;
	//double firstEff = point_a.second / point_a.first / (point_a.first - point_b.first);
	//double secondEff = point_b.second / point_b.first / (point_b.first - point_a.first);
	long long int firstEff = point_a.first * (point_a.first - point_b.first);
	long long int secondEff = point_b.first * (point_b.first - point_a.first);

	for (int i = 0; i < pointMap.size(); i++) {
		if (result[i] == 1) {
			pair<long long int, long long int> target = pointMap.find(i)->second;
			//cout << point_a.first << "\t" << point_a.second << "\t" << point_b.first << "\t" << point_b.second << endl;
			//cout << firstEff << "\t" << secondEff << "\t" << fabs(firstEff * target.first * (target.first - point_b.first) + secondEff * target.first * (target.first - point_a.first) - target.second) << endl;
			//if (isDoubleEqual(firstEff * target.first * (target.first - point_b.first) + secondEff * target.first * (target.first - point_a.first), target.second)) result[i] = 0;
			if (point_a.second * target.first * (target.first - point_b.first) * secondEff + point_b.second * target.first * (target.first - point_a.first) * firstEff == target.second * firstEff * secondEff) result[i] = 0;
		}
	}
	//cout << "Result: " << result << endl;
	return result;

}

int Problem::getLeastParabola (bitset<N> state) {

	// Dynimaic programming
	auto got = stateMap.find(state);
	if (got != stateMap.end()) {
		//cout << got->second << endl;
		return got->second;
	}

	int bestCount = N; // N is the worst case
	bitset<N> bestState;
	for (int i = 0; i < pointMap.size(); i++) {
		if (state[i] == 1) {
			for (int j = i + 1; j < pointMap.size(); j++) {
				if (state[j] == 1) {
					bitset<N> parabola = 0;
					parabola[i] = 1;
					parabola[j] = 1;
					int count = getLeastParabola(getNextState(state, parabola));
					if (count < bestCount) {
						bestCount = count;
						bestState = state;
					}
				}
			}
			break;
		}
	}

	bestCount++;
	//cout << bestCount << endl;
	stateMap.insert({bestState, bestCount});
	return bestCount;

}

int Problem::solve () {

	/*for (auto it = pointMap.begin(); it != pointMap.end(); it++) {
		cout << it->first << "\t(" << it->second.first << ", " << it->second.second << ")" << endl;
	}*/

	stateMap.insert({0, 0});
	for (int i = 0, j = 1; i < N; i++, j <<= 1) {
		stateMap.insert({j, 1});
	}
	//printUnorderedMap(stateMap);

	bitset<N> initialState = 0;
	for (int i = 0; i < pointMap.size(); i++) {
		initialState[i] = 1;
	}
	//cout << initialState << endl;

	return getLeastParabola(initialState);

}

int main (int argc, char* argv[]) {
	int count;
	scanf("%d", &count);
	for (int i = 0; i < count; i++) {
		int pointsCount;
		Problem problem;
		scanf("%d", &pointsCount);
		for (int j = 0; j < pointsCount; j++) {
			long long int x, y;
			scanf("%lld%lld", &x, &y);
			problem.addPoint(j, make_pair(x, y));
		}
		printf("%d\n", problem.solve());
	}
}
