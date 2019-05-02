#include <iostream>
#include <cmath>
#include <vector>
#include<algorithm>
using namespace std;
const double PI = 3.1415926535897932384626433832795;
const double ERR = 100;
inline double size(pair <double, double> a, pair<double, double> b) {
	return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}
inline vector<pair<double, double>> findIntersections(double x0, double y0, double R) {
	double tmp;
	vector<pair<double, double>> forReturn;
	if ((tmp = pow(R, 2) - pow(x0, 2)) > 0) { //left
		forReturn.push_back(make_pair(0, -sqrt(tmp) + y0));
		forReturn.push_back(make_pair(0, sqrt(tmp) + y0));
	}
	else {
		forReturn.push_back(make_pair(ERR, ERR));
		forReturn.push_back(make_pair(ERR, ERR));
	}
	if ((tmp = pow(R, 2) - pow((1 - y0), 2)) > 0) { //up
		forReturn.push_back(make_pair(-sqrt(tmp) + x0, 1));
		forReturn.push_back(make_pair(sqrt(tmp) + x0, 1));
	}
	else {
		forReturn.push_back(make_pair(ERR, ERR));
		forReturn.push_back(make_pair(ERR, ERR));
	}
	if ((tmp = pow(R, 2) - pow((1 - x0), 2)) > 0) { //right
		forReturn.push_back(make_pair(1, sqrt(tmp) + y0));
		forReturn.push_back(make_pair(1, -sqrt(tmp) + y0));
	}
	else {
		forReturn.push_back(make_pair(ERR, ERR));
		forReturn.push_back(make_pair(ERR, ERR));
	}
	if ((tmp = pow(R, 2) - pow(y0, 2)) > 0) { //down 
		forReturn.push_back(make_pair(sqrt(tmp) + x0, 0));
		forReturn.push_back(make_pair(-sqrt(tmp) + x0, 0));
	}
	else {
		forReturn.push_back(make_pair(ERR, ERR));
		forReturn.push_back(make_pair(ERR, ERR));
	}
	return forReturn;
}
inline double segment(double R, double h) {
	return (acos(h / R) * pow(R, 2) - h * (R * sin(acos(h / R))) );
}
int main(){
	int n;
	double R;
	double sum = 0;
	cin >> n >> R;
	double x, y;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		double s = PI * pow(R, 2);
		double s0 = s;
		pair<double, double> dl(0, 0), ul(0, 1), ur(1, 1), dr(1, 0);
		vector <pair<double, double>> intersections = findIntersections(x, y, R);
		pair<double, double> err(ERR, ERR);
		if (intersections[0] != err) {
			s -= segment(R, x);
		}
		if (intersections[2] != err) {
			s -= segment(R, 1 - y);
		}
		if (intersections[4] != err) {
			s -= segment(R, 1 - x);
		}
		if (intersections[6] != err) {
			s -= segment(R, y);
		}
		if (intersections[0].second < 0 && intersections[7].first < 0 && intersections[0] != err && intersections[7] != err) {
			double h = R * cos(asin(size(intersections[0], intersections[7]) / 2 / R));
			s += segment(R, h) + size(dl, intersections[0]) * size(dl, intersections[7]) / 2;
		}
		if (intersections[1].second > 1 && intersections[2].first < 0 && intersections[1] != err && intersections[2] != err) {
			double h = R * cos(asin(size(intersections[1], intersections[2]) / 2 / R));
			s += segment(R, h) + size(ul, intersections[1]) * size(ul, intersections[2]) / 2;
		}
		if (intersections[3].first > 1 && intersections[4].second > 1 && intersections[3] != err && intersections[4] != err) {
			double h = R * cos(asin(size(intersections[3], intersections[4]) / 2 / R));
			s += segment(R, h) + size(ur, intersections[3]) * size(ur, intersections[4]) / 2;
		}
		if (intersections[5].second < 0 && intersections[6].first > 1 && intersections[5] != err && intersections[6] != err) {
			double h = R * cos(asin(size(intersections[5], intersections[6]) / 2 / R));
			s += segment(R, h) + size(dr, intersections[5]) * size(dr, intersections[6]) / 2;
		}
		sum += s;
	}
	std::cout.setf(std::ios::fixed);
	std::cout.precision(9);
	cout << sum << endl;
	system("pause");
}


