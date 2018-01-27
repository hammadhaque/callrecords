#include "call_class.h"

/**************************************************************
Name: Syed Haque    
FAUID: Shaque2015
Znumber: Z23352249
Desription:  In this program we will be overloading << which is a part of the output stream and the - operator and we will also be adding the copy constructor to this program.
*****************************************************************/
//driver to test the functionality of your class.
int main()
{
	call_class My_Class;
	cout << My_Class;
	string key;
	cout << endl;
	cout << endl;
	cout << "Add information to the call record " << endl;
	My_Class.add();
	cout << My_Class << endl;
	cout << endl;
	cout << endl;
	cout << "enter the number you want to search:";
	cin >> key;
	if ((My_Class.search(key) + 1) != 0)
	{
		cout << "the number " << key << " you are looking for is in the position " << My_Class.search(key) + 1 << endl;
	}
	else
	{
		cout << "-------------Phone number is not present!!!---------------"<<endl;
	}
	cout << "Enter a phone number that you want to remove from the list:";
	cin >> key;
	My_Class - (key);
	cout << My_Class << endl;
	cout << "The phone number has now been removed\n";
	return 0;

}



