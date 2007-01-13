
#include <iostream>
#include "fstring.h"

using namespace std;

int main(int argc, char *argv[])
{
	String s = "Hello World!";
	String t = s;

	cout << (const char*)t << endl;

	t += "|This is some stuff!!!";
	cout << (const char*)t << endl;

	t += "|Wow";
	cout << (const char*)t << endl;

	t += String("|Crazy!") + "Wow";
	cout << (const char*)t << endl;

	return 0;
}