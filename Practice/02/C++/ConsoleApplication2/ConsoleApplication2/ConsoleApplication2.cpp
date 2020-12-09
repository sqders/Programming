#include <iostream>
using namespace std;
int main() {
	int tri, pi;
	tri = 3;
	pi = 3.14;
//так как pi имеет тип int ,ему присвоется значение до точки
	double d_tri, d_pi;
	d_tri = 3;
	d_pi = 3.14;
	cout << tri << endl << pi << endl << d_tri<<endl << d_pi;
	return 0;
}