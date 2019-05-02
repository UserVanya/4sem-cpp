#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <utility>
#include <sstream>
using namespace std;

pair<int, string> Temp_to_key(const string& s) {
	string result;
	bool flag = false;
	int count = 0;
	for (auto x : s) {
		if (isdigit(x)) {
			result += x;
		}
		else if (x == 'X') {
			flag = true;
			count++;
		}
		else if (flag || x == '-') {
			return { count, result };
		}
	}
	return { count, result };
}

string Temp_to_string(const string& s) {
	string result;
	for (auto x : s) {
		if (isdigit(x)) {
			result += x;
		}
	}
	return result;
}

int main() {
	//istringstream cin("1\n1777\n4\n+9 (365) XXXXXX - A\n +0 (000) XXX - B\n + 1 (777)  -para 0\n+ 0 (123) XXX - D");
	string temp;
	string num;
	map<string, pair<int, string>> templates;
	queue<string> numbers;
	getline(cin, num);
	for (int i = 0; i < stoi(num); i++) {
		getline(cin, temp);
		numbers.push(Temp_to_string(temp));
	}
	getline(cin, num);
	for (int i = 0; i < stoi(num); i++) {
		getline(cin, temp);
		auto it = Temp_to_key(temp);
		templates[it.second] = { it.first, temp };
	}
	while (!numbers.empty()) {
		string cur = numbers.front();
		numbers.pop();
		auto it = templates.upper_bound(cur);
		while (1) {
			if (it == templates.begin()) {
				it = templates.end();
			}
			it--;
			string sub_key = cur.substr(0, it->first.size());
			if (sub_key != it->first) {
				continue;
			}
			string sub_val = cur.substr(it->first.size(), cur.size() - it->first.size());
			if (sub_val.size() != it->second.first) {
				continue;
			}
			string result = it->second.second;
			auto of = it->second.second.find('X');
			for (int i = 0; i < sub_val.size(); i++) {
				result[of + i] = sub_val[i];
			}
			cout << result << endl;
			break;
		}
	}
	return 0;
}