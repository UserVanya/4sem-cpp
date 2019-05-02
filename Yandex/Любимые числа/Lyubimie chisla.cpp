#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
	long double prob, weight_else_last = 0, weight_last = 1, znam;
	bool flag3 = false, first = true;
	int num5, num2 = num5 = 0, size, per, last;
	long long int num;
	cin >> num >> per;
	flag3 = !(num % 3);
	size = (int)log10(num) + 1;
	znam = (size * (size - 1)) / 2;
	for (int i = 0; i < per; i++) {
		weight_else_last = (1 + weight_else_last * (znam - size)) / znam;
	}
	weight_last = 1 - weight_else_last * (size - 1);
	while (num > 0) {
		if (first) {
			first = false;
			last = num % 10;
			num /= 10;
		}
		else {
			int c = num % 10;
			num /= 10;
			num5 += !(c % 5);
			num2 += !(c % 2);
		}
	}
	prob = (long double) ((num5 + num2 * flag3) * weight_else_last + ((!(last % 5) || !(last % 2) * flag3) * weight_last));
	cout << fixed << setprecision(15) << prob;
		return 0;
}