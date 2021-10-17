/*  
CS210 - Project Three
Name: Kerrian Offermann
Date: 10/13/2021
*/

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <sstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char *procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("KOffermann_M7P3_PythonCode");
	PyErr_Print();	
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen: 
		You sent me: Test
Return:
	100 is returned to the C++	
*/
int callIntFunc(string proc, string param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char *paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"KOffermann_M7P3_PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"KOffermann_M7P3_PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


int main()
{
	
	

	while (true) { /* This while loop will keep the menu going until user chooses to end program*/

		try { /* Try block starts here -- will check for input errors */

			cout << endl;
			cout << "Please select from option 1, 2, 3, or 4." << endl;
			cout << endl;
			cout << "[1] Display List of All Items and Quantity Sold" << endl;
			cout << "[2] Display Quantity of a Single Item Sold " << endl;
			cout << "[3] Display Graph of All Items and Quantity Sold" << endl;
			cout << "[4] Exit Menu" << endl;

			/* User will enter an input to be stored in userInput 
			If the input is not a valid integer then they will receive an error message
			If they enter a valid integer then their input will be used for their selection*/

			int userInput = 0; 
			std::string line;
			while (std::getline(std::cin, line)) {
				std::stringstream ss(line);
				if (ss >> userInput) {
					if (ss.eof()) {   // Success
						break;
					}
				}
				std::cout << "Error. Please enter a number." << std::endl;
			}

			/* The menu will print first and then allow user to enter value 1, 2, 3, and 4 */

			if (userInput != 1 && userInput != 2 && userInput != 3 && userInput != 4) {
				throw runtime_error("Error. Please choose a valid menu option.");
			}

			/* If a value is not 1, 2, 3, and 4 then user will receive the above warning
			Our catch block below will also remind user of instructions and loop back to main menu */


			if (userInput == 1) {
				
				CallProcedure("QuantityAll");
				cout << endl;
				continue;
			}
			/* If user enters option 1, a list of each item sold and that item's quantity will print.
			The user will then be returned to the main menu to enter another choice. */

			if (userInput == 2) {
				
				CallProcedure("QuantityOne");
				continue;
			}

			/* If user enters option 2, they will be prompted by the Python function to enter the name of the item.
			A correct item entry (regardless of case) will bring back results of the item and the quantity sold.
			An incorrect item entry will print a warning and send the user back to the main menu. */

			if (userInput == 3) {

				CallProcedure("QuantityGraph");
				continue;
			}

			/*  */

			if (userInput == 4) {
				cout << endl;
				cout << "Thank you for using Chada Tech. Goodbye!" << endl;
				break;
			}

			/* If user chooses three then they will receive a farewell message and the program will close.*/

		} // Our try block ends here -- and stops detecting errors at this point

		catch (runtime_error& excpt) {
			cout << excpt.what() << endl;
			cout << "The menu choices are 1, 2, 3, or 4." << endl;
			continue;
		}

		/* When the input error is caught, this message will print.
		User will be taken back to the menu to choose another option.*/

	}

	return 0;

}