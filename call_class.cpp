#include "call_class.h"
/************************************************************************************************************************************/
//Name: default constructor
//Decription: Reads the data file of call information (cell number, relays and call length) into the dynamic array of call record, 
//call_DB. If the count because equal to the size the function double_size is called and the memory allocated to call_DB is doubled.
/************************************************************************************************************************************/
call_class::call_class()
{
	cout << "Copy Constructor Called\n";
	ifstream in;
	in.open("callstats_data.txt");
	size = 1;
	count = 0;
	Call_DB = new call_record[size];
	while (!in.eof())
	{
		if (count == size)
		{
			double_size();
		}

		in >> Call_DB[count].firstname >> Call_DB[count].lastname >> Call_DB[count].cell_number >> Call_DB[count].relays >> Call_DB[count].call_length;
		count++; //count is incremented
	}
	process();
	in.close();

}

/************************************************************************************************************************************/
//Name: copy constructor
//Decription: performs a deep copy.
/************************************************************************************************************************************/
call_class::call_class(const call_class &avg)
{
	count = avg.count;
	size = avg.size;
	Call_DB = new call_record[size];
	for (int i = 0; i < count; i++)
	{
		Call_DB[i] = avg.Call_DB[i];
	}
	cout << "Copy Constructor has been called\n";


}
/***********************************************************************************************************************************/
//Name: is_empty
//Precondition: count == 0 has not been returned 
//Postcondition:  count == 0 has been returned
//Decription: returns true if call_DB is empty
/**********************************************************************************************************************************/
bool call_class::is_empty()
{
	return count == 0;
}

/**********************************************************************************************************************************/
//Name: is_full 
//Precondition: count == size has not been returned
//Postcondition: count == size has been returned
//Decription: returns true if call_DB is full
/*********************************************************************************************************************************/
bool call_class::is_full()
{
	return count == size;
}

/**********************************************************************************************************************************/
//Name: search
//Precondition: Call_DB has not been searched for the key
////Postconditions: Location of key in Call_DB is returned if it is there; otherwise -l is returned.
//Decription: locates key in call_DB if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int call_class::search(const string key)
{
	int k = 0;
	for (k = 0;k < count;k++)
	{
		if (Call_DB[k].cell_number == key)
			return k;                             //the int location of the key is returned if it's in the dynamic array
	}
	return -1;
}

/*********************************************************************************************************************************/
//Name: add
//Precondition:  Add a call record to call_DB if it is not full.  Is it is full, Double_size is called and the the record is added
////Postconditions: Call records have been added to Call_DB
//Decription: adds the information for a call to call_DB; if call_DB is full, double_size is called to increase the size of call_DB.
/********************************************************************************************************************************/
void call_class::add()
{
	if (count == size)
		double_size();
	cout << "Enter First Name: ";
	cin >> Call_DB[count].firstname;
	cout << "Enter Last Name: ";
	cin >> Call_DB[count].lastname;
	cout << "Enter Cell Phone Number: ";
	cin >> Call_DB[count].cell_number;
	cout << "Enter Call length:  ";
	cin >> Call_DB[count].call_length;
	cout << "Enter number of Relays: ";
	cin >> Call_DB[count].relays;
	count++; //count is incremented in order for process to be properly called
	process();
}

/********************************************************************************************************************************/
//Name: operator-
//Precondition: Call_DB, and key have been initialized
//Postcondition: The call record the matches key has been removed by using - via a member function
//Decription: remove key from call_DB if it is there.
/*******************************************************************************************************************************/
call_class & call_class::operator-(const string key)
{
	int loc = search(key);
	if (loc != -1)
	{
		for (int j = loc; j < count - 1; j++)
		{
			Call_DB[j] = Call_DB[j + 1];
		}
		count--;
	}
	return *this;
}

/******************************************************************************************************************************/
//Name: double_size
//Precondition: There is no free memory in Call_DB.  count == size ---_Call_DB is full
//Postcondition: The capacity of memory of Call_DB has been doubled
//Decription: doubles the size (capacity) of call_DB
/******************************************************************************************************************************/
void call_class::double_size()
{
	size *= 2;
	call_record *temp = new call_record[size];

	for (int i = 0; i<count; i++)
	{
		temp[i] = Call_DB[i];
	}

	delete[] Call_DB;
	Call_DB = temp;
}


/******************************************************************************************************************************/
//Name: process
//Precondition: The call record variables such as net cost, tax rate, call tax and total cost have not been initialized yet
//Postcondition: Net cost, tax rate, call tax and total cost have all been processed and calculated
//Decription: calculate the net cost, tax rate, call tax and total cost for every call record in call_DB.
/*****************************************************************************************************************************/
void call_class::process()
{
	for (int i = 0; i < count; i++)
	{
		//Step 2: put your if-else statement here to determine the tax rate.
		//condition 1 if relays <= 1  && relays <= 5 then  tax_rate is .01 and call_tax = net_cost * tax_rate
		//condition  2 if relays >=6 && relays <=1 then tax_rate is .03 and call_tax = net_cost * tax and so forth

		Call_DB[i].net_cost = Call_DB[i].relays / 50.0 * .40 * Call_DB[i].call_length;

		if (Call_DB[i].relays >= 0 && Call_DB[i].relays <= 5) // if else statement to get the correct tax rate
		{
			Call_DB[i].tax_rate = .01;
		}
		else if (Call_DB[i].relays >= 6 && Call_DB[i].relays <= 11)
		{
			Call_DB[i].tax_rate = .03;
		}
		else if (Call_DB[i].relays >= 12 && Call_DB[i].relays <= 20)
		{
			Call_DB[i].tax_rate = .05;
		}
		else if (Call_DB[i].relays >= 21 && Call_DB[i].relays <= 50)
		{
			Call_DB[i].tax_rate = .08;
		}
		else
		{
			Call_DB[i].tax_rate = .12;
		}

		//Step 3:put your code here to determine the total_cost using the formula: total_cost = net_cost + call_tax;
		//Note store all values in your call record
		//calculates the total cost of the call by using both the net_cost and call_tax

		Call_DB[i].call_tax = Call_DB[i].net_cost * Call_DB[i].tax_rate;

		Call_DB[i].total_cost = Call_DB[i].net_cost + Call_DB[i].call_tax;
	}
}


/****************************************************************************************************************************/
//Name: operator<<
//Precondition: Call_DB, size and count have been initialized
//Postcondition: Records in Call_DB printed to screen
//Decription: Overloading operator<< as a friend function. Prints every field of every call_record in call_DB 
//                   formatted to the screen and a file called "stats7_output.txt".
/***************************************************************************************************************************/
ostream & operator<<(ostream & out, call_class & Org)
{
	out.setf(ios::fixed);
	out.setf(ios::showpoint);
	out.precision(2);

	for (int i = 0; i<Org.count; i++)
	{
		out << Org.Call_DB[i].firstname << "\t"
			<< Org.Call_DB[i].lastname << "\t"
			<< Org.Call_DB[i].cell_number << "\t"
			<< Org.Call_DB[i].relays << "\t"
			<< Org.Call_DB[i].call_length << "\t"
			<< Org.Call_DB[i].net_cost << "\t"
			<< Org.Call_DB[i].tax_rate << "\t"
			<< Org.Call_DB[i].call_tax << "\t"
			<< Org.Call_DB[i].total_cost << endl;
	}
	return out;

	//Put code to OPEN and CLOSE an ofstream and print to the file "stats7_output.txt".
}

/****************************************************************************************************************************/
//Name: destructor
//Precondition: Memory has not been de-allocated for the call class
//Postcondition: All memory allocated to call_DB has been de-allocated
//Decription: de-allocates all memory allocated to call_DB.  This should be the last function to be called before the program
//            is exited.
/***************************************************************************************************************************/
call_class::~call_class()
{
	cout << "Destructor has been called\n";
	delete[] Call_DB;
}
