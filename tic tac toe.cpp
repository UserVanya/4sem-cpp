#include <iostream>
#include <map>
#include <vector>
#include <set>
using namespace std;
const int X = 1;
const int O = 2;
const int onlyWins = 1;
const int exactMoves = 2;
bool thisCollocIsWinning(map<int, int>& t) {
	for (int i = 0; i < 3; i++) {
		if ((t[1 + 3 * i] == t[2 + 3 * i] && t[2 + 3 * i] == t[3 + 3 * i] && t[3 + 3 * i] != 0)
			|| (t[1 + i] == t[4 + i] && t[4 + i] == t[7 + i] && t[7 + i] != 0)) {
			return true;
		}
	}
	if (t[1] == t[5] && t[5] == t[9] && t[9] != 0) {
		return true;
	}
	if (t[3] == t[5] && t[5] == t[7] && t[7] != 0) {
		return true;
	}
	return false;
}
void PrintCombination(map<int, int> tmp) {
	for (int i = 1; i <= 9; i++) {
		if (tmp[i] == X) {
			cout << "x ";
		}
		if (tmp[i] == O) {
			cout << "o ";
		}
		if (tmp[i] == 0) {
			cout << "_ ";
		}
		if (i % 3 == 0) {
			cout << endl;
		}
	}
	cout << endl;
}
void printCombinations(set<map<int, int>> comb) {
	int count = 0;
	for (auto item : comb) {
		if (!thisCollocIsWinning(item)) {
			count++;
			PrintCombination(item);
		}
	}
	cout << "amount of draws = " << count << endl;
}

void makeAMove(int currDepth, map<int, int> currCollocation, int lastStep, set<map<int, int>>& comb, int& amount, int flag) {
	if (flag == exactMoves) {
		if (thisCollocIsWinning(currCollocation)) {
			comb.insert(currCollocation);
			amount++;
			return;
		}
		if (currDepth == (lastStep - 1)) {
			for (int i = 0; i < 9; i++) {
				if (currCollocation[i + 1] == 0) {
					if ((lastStep - 1) % 2 == 0) {
						currCollocation[i + 1] = X;
					}
					else {
						currCollocation[i + 1] = O;
					}
					comb.insert(currCollocation);
					currCollocation[i + 1] = 0;
				}
			}
			amount++;
			return;
		}
	}
	else {
		if (thisCollocIsWinning(currCollocation) && currDepth == lastStep) {
			comb.insert(currCollocation);
			amount++;
			return;
		}
		else if (thisCollocIsWinning(currCollocation) && currDepth != lastStep){
			return;
		}
	}
	
	if (currDepth % 2 == 0) {
		for (int i = 0; i < 9; i++) {
			if (currCollocation[i + 1] == 0) {
				currCollocation[i + 1] = X;
				makeAMove(currDepth + 1, currCollocation, lastStep, comb, amount, flag);
				currCollocation[i + 1] = 0;
			}
		}
	}
	else {
		for (int i = 0; i < 9; i++) {
			if (currCollocation[i + 1] == 0) {
				currCollocation[i + 1] = O;
				makeAMove(currDepth + 1, currCollocation, lastStep, comb, amount, flag);
				currCollocation[i + 1] = 0;
			}
		}
	}
	return;
}


int main() {
	map<int, int> currCollocation;
	set<map<int, int>> comb;
	for (int i = 1; i <= 9; i++) {
		currCollocation.insert(make_pair(i, 0));
	}
	int amount = 0;
	makeAMove(0, currCollocation, 9, comb, amount, exactMoves); // onlyWins exactMoves
	printCombinations(comb);
	cout << "uniq comb = " << comb.size() << endl;
	cout << "possible batches = " << amount << endl;

	system("pause");

}
