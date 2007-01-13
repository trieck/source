#include <iostream>
#include <sstream>
#include <string>

using namespace std;


/////////////////////////////////////////////////////////////////////////////
class X {
public:
	static int s(int n) {
		int x, r = n % 4;
		if (r == 0) {
			x = n /2;
		} else if (r == 1 || r == 2) {
			x = n / 2 + 1;
		} else {
			x = (n + 1) / 2;		
		}
		return x;
	}
};

/////////////////////////////////////////////////////////////////////////////
class U {
public:
	static int s(int n) {
		int u, r = n % 4;
		if (r == 0 || r == 1) {
			u = n / 2 + 1;
		} else if (r == 2) {
			u = n / 2;
		} else {
			u = (n + 1) / 2;
		}
		return u;
	}
};

/////////////////////////////////////////////////////////////////////////////
class Xp {
public:
	static int s(int n) {
		int x, r = n % 4;
		if (r == 0 || r == 1) {
			x = n * (n + 3) / 4;
		} else {	// r = 2 or 3
			x = (n + 1) * (n + 2) / 4;
		}

		return x;
	}
};

/////////////////////////////////////////////////////////////////////////////
class Up {
public:
	static int s(int n) {
		int u, r = n % 4;
		if (r == 0 || r == 1) {
			u = n * (n + 3) / 4 + 1;
		} else {	// r = 2 or 3
			u = (n + 1) * (n + 2) / 4;
		}
		return u;
	}
};

/////////////////////////////////////////////////////////////////////////////
class G {
public:
	static string g(int n) {		
		int u = U::s(n);
		int x = X::s(n);

		ostringstream os;
		os << x <<"x + " << u;
		return os.str();
	}	
};

/////////////////////////////////////////////////////////////////////////////
class F {
public:
	static string f(int n) {
		int u = Up::s(n);
		int x = Xp::s(n);

		ostringstream os;
		os << x <<"x + " << u;
		return os.str();
	}
};

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	for (int n = 0; n < 1000; n++)
		cout << n << '\t' << F::f(n) << endl;

	return 0;
}