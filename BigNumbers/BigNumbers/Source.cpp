#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <cstdio>
#include "bignumbers.h"

using namespace std;

void unecho_cin(bool choice) {
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	if (choice) {
		mode &= ~ENABLE_ECHO_INPUT;
	}
	else {
		mode |= ENABLE_ECHO_INPUT;
	}
	SetConsoleMode(hStdin, mode);
}

int main() {
	
	string nr, nr2;
	int option;

	while (true) {
		unecho_cin(true);
		cout << "-----------------Big Numbers calculator with integers---------------------\n";
		cout << "1.Print a given number\n";
		cout << "2.Addition\n";
		cout << "3.Types of constructors\n";
		cout << "4.Scientific vs normal\n";
		cout << "5.Comparison operators/relational operators\n";
		cout << "6.Exit\n";
		cin >> option;
		switch (option) {
		case 1: {
			cout << "\t1.1.Normal number\n";
			cout << "\t1.2.Scientific number\n";
			cin >> option;
			switch (option) {
			case 1: {
				cout << "\t\tInsert a normal number\n\t";
				cin >> nr;
				BigNumber n1(nr);
				cout << "\t\t";
				n1.print_normal();
			}
					break;
			case 2: {
				cout << "\t\tInput a scientific number\n\t\t";
				cin >> nr;
				BigNumber n1(nr);
				cout << "\t\t";
				n1.print_scientific();
			}
					break;
			default: break;
			}
		}
		break;
		case 2: {
			cout << "\t2.1.Addition using a function\n";
			cout << "\t2.2.Addition using the operator +\n";
			cin >> option;
			switch (option) {
			case 1: {
				cout << "\t\tLet's read first number\n";
				cin >> nr;
				cout << "\t\tLet's read second number\n";
				cin >> nr2;
				BigNumber n1(nr);
				BigNumber n2(nr2);
				BigNumber n3;
				n3.addition(n1, n2);
				cout << "\t\t";
				n3.print_normal();
			}
					break;
			case 2: {
				cout << "\t\tLet's read first number\n";
				cin >> nr;
				BigNumber n1(nr);
				cout << "\t\t";
				n1.print_normal();
				cout << "\t\tLet's read second number\n";
				cin >> nr2;
				BigNumber n2(nr2);
				cout << "\t\t";
				n2.print_normal();
				BigNumber n3;
				n3 = n1 + n2;
				cout << "\t\tSum : ";
				n3.print_normal();
			}
					break;
			default: break;
			}
		}
		break;
		case 3: {
			cout << "\t3.1.General constructor\n";
			cout << "\t3.2.Type conversion constructor int->BigNumber (Ex: int 15 is gonna be 15 in BigNumber)\n";
			cout << "\t3.3.Type conversion constructor char->BigNumber (Ex: char 'a' is gonna be 97(ASCII))\n";
			cout << "\t3.4.Copy constructor\n";
			cin >> option;
			switch (option) {
			case 1: {
				cout << "\t\tInsert a number\n";
				cin >> nr;
				BigNumber n1(nr);
				cout << "\t\tNumber generated with general constructor: ";
				n1.print_normal();
			}
					break;
			case 2: {
				cout << "\t\tInsert and integer\n";
				int n;
				cin >> n;
				BigNumber n1(n);
				cout << "\t\tNumber generated from int\n";
				n1.print_normal();
			}
					break;
			case 3: {
				cout << "\t\tInsert a char\n";
				char n;
				cin >> n;
				BigNumber n1(n);
				cout << "\t";
				n1.print_normal();
			}
					break;
			case 4: {
				cout << "\tInsert a number\n";
				cin >> nr;
				BigNumber n1(nr);
				BigNumber n2(n1);
				cout << "\t\tThe number you created is:\n";
				n1.print_normal();
				cout << "\t\tThe number copied by our copy constructor is:\n";
				n2.print_normal();
			}
					break;
			default: break;
			}
		}
		break;
		case 4: {
			cout << "\t4.1.Number with general constructor to normal and scientific\n";
			cout << "\t4.2.Number with conversion int->BigNumber constructor to normal and scientific\n";
			cout << "\t4.3.Number with conversion char->BigNumber constructor and scientific\n";
			cin >> option;
			switch (option) {
			case 1: {
				cout << "\t\tInsert a number\n\n";
				cin >> nr;
				BigNumber n1(nr);
				cout << "\t\tWith general constructor : \n";
				cout << "\t\tNormal number :\n\t\t";
				n1.print_normal();
				cout << "\t\tScientific number :\n\t\t";
				n1.print_scientific();
			}
					break;
			case 2: {
				cout << "\t\tInsert a number\n\n";
				int n;
				cin >> n;
				BigNumber n1(n);
				cout << "\t\tWith conversion int->BigNumber constructor : \n";
				cout << "\t\tNormal number :\n\t\t";
				n1.print_normal();
				cout << "\t\tScientific number :\n\t\t";
				n1.print_scientific();
			}
					break;
			case 3: {
				cout << "\t\tInsert a character\n\n";
				char ch;
				cin >> ch;
				BigNumber n1(ch);
				cout << "\t\tWith conversion char->BigNumber constructor : \n";
				cout << "\t\tNormal number :\n\t\t";
				n1.print_normal();
				cout << "\t\tScientific number :\n\t\t";
				n1.print_scientific();
			}
					break;
			default: break;
			}
		}
		break;
		case 5: {
			cout << "\t5.1.Less then ( a < b )\n";
			cout << "\t5.2.Greater then ( a > b )\n";
			cout << "\t5.3.Equal ( a == b)\n";
			cout << "\t5.4.Less then ( a != b )\n";
			cout << "\t5.5.Less then ( a <= b )\n";
			cout << "\t5.6.Less then ( a >= b )\n";
			cin >> option;
			switch (option) {
			case 1: {
				cout << "\n\t\tInsert a number\n";
				cin >> nr;
				BigNumber n1(nr);
				cout << "\t\tNumber : " << n1 << "\n";
				cout << "\t\tInsert a second number\n";
				cin >> nr;
				BigNumber n2(nr);
				cout << "\t\tNumber : " << n2 << "\n";
				if (n1 < n2) {
					cout << "\t\tFirst number is smaller\n";
				}
				else {
					cout << "\t\tFirst number is not smaller\n";
				}

			}
			break;
			case 2: {
				cout << "\n\t\tInsert a number\n";
				cin >> nr;
				BigNumber n1(nr);
				cout << "\t\tNumber : " << n1 << "\n";
				cout << "\t\tInsert a second number\n";
				cin >> nr;
				BigNumber n2(nr);
				cout << "\t\tNumber : " << n2 << "\n";
				if (n1 > n2) {
					cout << "\t\tFirst number is bigger\n";
				}
				else {
					cout << "\t\tFirst number is not bigger\n";
				}

			}
			break;
			case 3: {
				cout << "\n\t\tInsert a number\n";
				cin >> nr;
				BigNumber n1(nr);
				cout << "\t\tNumber : " << n1 << "\n";
				cout << "\t\tInsert a second number\n";
				cin >> nr;
				BigNumber n2(nr);
				cout << "\t\tNumber : " << n2 << "\n";
				if (n1 == n2) {
					cout << "\t\tThe numbers are equal\n";
				}
				else {
					cout << "\t\tThe numbers are not equal\n";
				}


			}
			break;
			case 4: {
				cout << "\n\t\tInsert a number\n";
				cin >> nr;
				BigNumber n1(nr);
				cout << "\t\tNumber : " << n1 << "\n";
				cout << "\t\tInsert a second number\n";
				cin >> nr;
				BigNumber n2(nr);
				cout << "\t\tNumber : " << n2 << "\n";
				if (n1 != n2) {
					cout << "\t\tThe numbers are not equal\n";
				}
				else {
					cout << "\t\tThe numbers are equal\n";
				}

			}
			break;
			case 5: {
				cout << "\n\t\tInsert a number\n";
				cin >> nr;
				BigNumber n1(nr);
				cout << "\t\tNumber : " << n1 << "\n";
				cout << "\t\tInsert a second number\n";
				cin >> nr;
				BigNumber n2(nr);
				cout << "\t\tNumber : " << n2 << "\n";
				if (n1 <= n2) {
					cout << "\t\tFirst number is smaller or equal\n";
				}
				else {
					cout << "\t\tSecond number is smaller\n";
				}
			}
			break;
			case 6: {
				cout << "\n\t\tInsert a number\n";
				cin >> nr;
				BigNumber n1(nr);
				cout << "\t\tNumber : " << n1 << "\n";
				cout << "\t\tInsert a second number\n";
				cin >> nr;
				BigNumber n2(nr);
				cout << "\t\tNumber : " << n2 << "\n";
				if (n1 >= n2) {
					cout << "\t\tFirst number is greater or equal\n";
				}
				else {
					cout << "\t\tSecond number is smaller\n";
				}
			}
			break;
			default: break;
			}
		break;
		}
		break;
		case 6: {
			return 0;
		}
		break;
		default: break;
		}
		
		cout << "\n\n";
		cin.get();
		system("CLS");
	}
	
	
	/*
	
	cout << "8.Now let's try all the compare operators\n\t";
	cout << "Number 1 : \n\t";
	cin >> nr;
	cout << "\tNumber 2 : \n\t";
	cin >> nr2;
	{
		BigNumber n1(nr);
		BigNumber n2(nr2);
		cout << "\t8.1.Less then ( < )\n\t";
		if (n1 < n2) {
			cout << "\tFirst number is smaller";
		}
		else {
			cout << "\tFirst number it's not smaller";
		}

		cout << "\n\n\t8.2.Greater then ( > )\n\t";
		if (n1 > n2) {
			cout << "\tFirst number is bigger";
		}
		else {
			cout << "\tFirst number it's not bigger";
		}

		cout << "\n\n\t8.3.Less then ( == )\n\t";
		if (n1 == n2) {
			cout << "\tNumbers are equal";
		}
		else {
			cout << "\tNumbers are not equal";
		}

		cout << "\n\n\t8.4.Less or equal then ( <= )\n\t";
		if (n1 <= n2) {
			cout << "\tFirst number is lower or equal ";
		}
		else {
			cout << "\tFirst number is not lower or equal ";
		}

		cout << "\n\n\t8.5.Less or equal then ( >= )\n\t";
		if (n1 >= n2) {
			cout << "\tFirst number is greater or equal ";
		}
		else {
			cout << "\tFirst number is not lower or equal ";
		}
	}
	 */

	//cout << endl;
	//n3.print_scientific();
}