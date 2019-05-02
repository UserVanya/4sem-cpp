#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <fstream>
#include<algorithm>
using namespace std;
inline void printNumbers(map<int, int>& compounds) {
	ios_base::sync_with_stdio(false);
	for (auto it = compounds.begin(); it != compounds.end(); it++) {
		cout << it->first << " ";
	}
}
inline bool check(const map<int, int>& compounds, int& m) {
	int product = 1;
	for (auto it = compounds.begin(); it != compounds.end(); it++) {
		product *= it->second;
	}
	if (product == m) {
		return true;
	}
	else return false;
}
inline bool intermediateCheck(map<int, int>& compounds, int& m, int tmp) {
	int product = 1;
	for (auto it = compounds.begin(); it != compounds.end(); it++) {
		product *= it->second;
	}
	product *= tmp;
	if (product > m) {
		return false;
	}
	
	return true;
}
inline void generate(multimap<int, int>& numbers, map<int, int>& compounds, int& k, int& m, int p, bool* isFound) {
	if (*isFound) {
		return;
	}
	if (compounds.size() == k) {
		if (check(compounds, m)) {
			printNumbers(compounds);
			*isFound = true;
		}
		return;
	}
	else if (p + k - compounds.size() <= numbers.size()){
		int i = p;
		auto it = numbers.begin();
		if (p < numbers.size()) {
			advance(it, p);
		}
		for (it; it != numbers.end(); it++) {
			if (intermediateCheck(compounds, m, it->first)) {
				compounds.insert(make_pair(it->second, it->first));
				if (*isFound) {
					return;
				}
				generate(numbers, compounds, k, m, i + 1, isFound);
				compounds.erase(it->second);
			}
			else{
				return;
			}
			i++;
		}
	}
	else {
		return;
	}
	return;
}
int main() {
	ifstream fin;
	ofstream fout;
	fin.open("input.txt");
	fout.open("output.txt");
	map<int, int> numbers;
	int n, m, k;
	fin >> n >> m >> k;
	int tmp;
	map<int, int> compounds;
	if (m == 0) {
		for (int i = 0; i < n; i++) {
			fin >> tmp;
			numbers.insert(make_pair(i + 1, tmp));
		}
		for (auto it = numbers.begin(); it != numbers.end(); it++) {
			if (compounds.size() != k - 1 && it->second != 0) {
				compounds.insert(make_pair(it->first, it->second));
			}
		}
		for (auto it = numbers.begin(); it != numbers.end(); it++) {
			if (it->second == 0) {
				compounds.insert(make_pair(it->first, it->second));
				printNumbers(compounds);
				system("pause");
				exit(0);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		fin >> tmp;
		int count = 0, countM = 0;
		if (tmp == 1) {
			count++;
		}
		if (tmp == m) {
			countM++;
		}
		if (tmp != 0) {
			if (m % tmp == 0) {
				bool isJustified = true;
				for (auto it = numbers.begin(); it != numbers.end(); it++) {
					if (it->second == tmp && it->second * tmp > m) {
						isJustified = false;
						break;
					}
				}
				if (count > k || countM > 1) {
					isJustified = false;
				}
				if (isJustified) {
					numbers.insert(make_pair(i + 1, tmp));
				}
			}
		}
	}
	bool isFound = false;
	multimap<int, int> values;
	for (auto it = numbers.begin(); it != numbers.end(); it++) {
		values.insert(make_pair(it->second, it->first));
	}
	generate(values, compounds, k, m, 0, &isFound);
	system("pause");
	return 0;
}