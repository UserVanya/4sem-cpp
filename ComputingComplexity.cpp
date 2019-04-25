#include <iostream>
#include <chrono>
#include <vector>
using namespace std;
class Point {
public:
	double x;
	double y;
	Point(){};
	Point(double x, double y) {
		this->x = x;
		this->y = y;
	}
	double norm(Point rhs, Point lhs) { return pow(rhs.x - lhs.x, 2) + pow(rhs.y - lhs.y, 2); }
};
ostream& operator<< (ostream& out, Point rhs) {
	out << "(" << rhs.x << ", " << rhs.y << ");";
	return out;
}
void getRoots(double a, double b, double c, int &n, double &x1, double &x2) {
	double d = b * b - 4 * a*c;
	n = (d > 0 ? 2 : (d < 0 ? 0 : 1));
	if (n = 0) return;
	x1 = (-sqrt(d) - b) / (2 * a);
	x2 = (d > 0 ? (sqrt(d) - b) / (2 * a) : x1);
}
void ComputeTest1(Point curr, int step, double radius, double& sum, int depth) {
	if (step >= depth) return;
	Point center(radius, radius);
	double b = curr.y - curr.x ;
	double x1, x2;
	int n;
	getRoots(2, -2 * (2 * radius - b), pow(radius - b, 2), n, x1, x2);
	Point edge;
	edge.x = x1;
	edge.y = edge.x + b;
	sum += abs(edge.x - curr.x) * abs(edge.y - curr.y);
	step++;
	ComputeTest1(Point(curr.x, edge.y), step, radius, sum, depth);
	ComputeTest1(Point(edge.x, curr.y), step, radius, sum, depth);
}

int main(){
	const double PI = 3.1415926535;
	double radius = 5;
	int depth;
	cin >> depth;
	double realSurface = PI * pow(radius, 2);
	double sum = 0;
	double k = 32.15856667;
	for (int i = 6; i < depth; i++) {
		auto begin = std::chrono::steady_clock::now();
		ComputeTest1(Point(0, 0), 0, radius, sum, i);
		auto end = std::chrono::steady_clock::now();
		auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
		cout << "i = " << i << ": " <<  elapsed_ns.count() / k << endl;
	}
	cout << (4 * (pow(radius, 2) - sum)) / realSurface;
	system("pause");
}




