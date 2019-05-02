#include <map>
#include <iostream>
#include <utility>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

long long int func(long long int a, long long int b) {
	return (b - a == 1) ? 1 : (long long int)log10(b - a) + 2;
};

int main() {
	long long int currle = 1, now;
	long long int cur = 1;
	map<long long int, long long int> position;
	string s;
	cin >> s;
	istringstream input(s);
	while(input.peek() != -1) {
		if (isdigit(input.peek())) {
			input >> now;
			cur += now;
			currle += (int)log10(now) + 2;
		}
		else {
			cur++;
			currle++;
		}
		position[cur] = currle;
		input.ignore(1);
	}
	long long int number, first, last;
	cin >> number;
	for (long long int i = 0; i < number; i++) {
		cur = 0;
		cin >> first >> last;
		auto it_f = position.upper_bound(first);
		auto it_l = position.upper_bound(last);
		last++;
		if (it_f == it_l) {
			cout << func(first, last) << '\n';
		}
		else if (it_f == prev(it_l)){
			cout << func(first, it_f->first) + func(it_f->first, last) << '\n';
		}
		else {
			it_l--;
			cout << func(first, it_f->first) + func(it_l->first, last) + (it_l->second - it_f->second) << '\n';
		}
	}
	return 0;
}