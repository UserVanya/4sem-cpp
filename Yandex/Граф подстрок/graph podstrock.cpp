#include <iostream>
#include <cmath>
#include <iomanip>
#include <utility>
#include <map>
#include <string>
#include <set>
using namespace std;

int main() {
	map<pair<string, string>, int> freq;
	set<string> top;
	int numbers;
	cin >> numbers;
	string str1, subf, subs;
	for (int i = 0; i < numbers; i++) {
		cin >> str1;
		subf = str1.substr(0, 3);
		top.insert(subf);
		for (int j = 1; j < str1.size() - 2; j++) {
			subs = str1.substr(j, 3);
			freq[make_pair(subf, subs)]++;
			subf = subs;
			top.insert(subs);
		}
	}
	cout << top.size() << endl << freq.size() << endl;
	for (auto x : freq) {
		cout << x.first.first << " " << x.first.second << " " << x.second << endl;
	}
	return 0;
}