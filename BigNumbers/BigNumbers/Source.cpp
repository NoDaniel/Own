#include <iostream>
#include <string>
#include <vector>
#include "bignumbers.h"

using namespace std;

int main() {

	string nr, nr2;
	int option;

	do {
		cout << "Input your number\n";
		cin >> nr;
		cout << "Input another number\n";
		cin >> nr2;

		BigNumber n1(nr);
		BigNumber n2(nr2);
		BigNumber n3;

		n3.addition(n1, n2);

		cout << "Print output in : \n\n1.Normal type\n2.Scientific type\n\n";
		cin >> option;
		switch (option) {
		case 1:
			n3.print_normal();
			break;
		case 2:
			n3.print_scientific();
		}

		system("PAUSE");
		system("CLS");
	} while(1);



	//cout << endl;
	//n3.print_scientific();
}