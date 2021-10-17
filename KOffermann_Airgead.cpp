/*
CS210: Project Two - Airgead Banking App
Name: Kerrian Offermann
Date: October 1, 2021
File: KOffermann_Airgead.cpp
*/

#include <iostream>
#include <iomanip>
#include "KOffermann_Airgead.h"
using namespace std;

BankingApp::BankingApp() {
	m_initialInvestment = 0.0; // Initialize initial investment
	m_monthlyDeposit = 0.0; // Initialize monthly deposit
	m_annualInterest = 0; // Initialize annual interest
	m_numYears = 0; // Initialize number of years
	m_numMonths = 0; // Initialize number of months
}

// Set our investment information to initialInvestment variable
void BankingApp::SetInvestment(string doubleInput) {
	m_initialInvestment = BankingApp::StrToDouble(doubleInput, '$');
}

// Set our deposit information to monthlyDeposit
void BankingApp::SetDeposit(string doubleInput) {
	m_monthlyDeposit = BankingApp::StrToDouble(doubleInput, '$');
}

// Set our interest information to annualInterest variable
void BankingApp::SetInterest(string doubleInput) {
	m_annualInterest = BankingApp::StrToDouble(doubleInput, '%');
}

// Set our years to numYears variable
void BankingApp::SetYears(int intInput) {
	m_numYears = intInput;
}

double BankingApp::StrToDouble(string str, char ch) {
	str.erase(remove(str.begin(), str.end(), ch), str.end());
	return atof(str.c_str());
}

/* This function is responsible for printing the headers of our report. 
The widths are set and then we full them with dashes as needed. */

void BankingApp::PrintHeader(string contentWithOut) {
	cout << setw(65) << setfill('-') << "" << endl;
	cout << right << setw(60) << setfill(' ') << contentWithOut << endl;
	cout << setw(65) << setfill('-') << "" << endl;
	cout << setw(65) << setfill('-') << "" << endl;
	cout << setw(6) << setfill(' ') << "Year";
	cout << setw(24) << "Year End Balance";
	cout << setw(35) << "Year End Earned Interest";
	cout << endl;
}

/* This function will calculated the accumulated interests*/
void BankingApp::PrintValues(vector<Balances> currVect, int i) {
	double tempInterestSum = 0;
	for (int j = i; j > (i - 12); --j) {
		tempInterestSum = currVect.at(j).interest + tempInterestSum;
	}

	// This will print our interest information for each year
	cout << setw(6) << setfill(' ') << (currVect.at(i).months / 12);
	cout << setw(12) << "$";
	cout << setw(12) << fixed << setprecision(2) << currVect.at(i).closingAmount;
	cout << setw(25) << "$";
	cout << setw(10) << fixed << setprecision(2) << tempInterestSum;
	cout << endl;
}

/* This function will take variables from the user to generate our report.
This specific function makes up our main banking app screen*/
void BankingApp::SetInterestVariables() {
	string doubleInput;
	int intInput;

	/* The header for our banking app menu */
	cout << endl;
	cout << endl;
	cout << setw(65) << setfill('-') << "" << endl;
	cout << setw(27) << setfill('-') << "";
	cout << " Data Input ";
	cout << setw(26) << setfill('-') << "" << endl;
	cout << endl;
	cout << endl;

	/* Request initial investment amount */
	cout << "Initial Investment:" << endl;
	cin >> doubleInput;
	BankingApp::SetInvestment(doubleInput);

	/* Request monthly deposit amount */
	cout << "Monthly Deposit:" << endl;
	cin >> doubleInput;
	BankingApp::SetDeposit(doubleInput);

	/* Request annual interest amount */
	cout << "Annual Interest:" << endl;
	cin >> doubleInput;
	BankingApp::SetInterest(doubleInput);

	/* Request number of years to calculate */
	cout << "Number of Years:" << endl;
	cin >> intInput;
	BankingApp::SetYears(intInput);
}

/* This function will create our report for users who do not add monthly deposits*/

void BankingApp::LoadBalances() {
	vector<Balances> withoutDeposit; // Vector containing the monthly balances without deposits
	try {
		m_numMonths = m_numYears * 12;
		withoutDeposit.resize(m_numMonths); // Add values for 'numMonths' to our vector

		// Generate our header
		BankingApp::PrintHeader("Balance and Interest Without Additional Monthly Deposits");
		
		/* Our loop for the report without deposits */
		for (int i = 0; i < m_numMonths; i++) {

			Balances balance;
			if (i == 0) {
				balance.openingAmount = m_initialInvestment; // Print the initial amount on the first loop
			}

			else { // Print the most recent amount at each loop after the first 
				balance.openingAmount = withoutDeposit.at(i-1).closingAmount;
			}

			/* Take variable, perform necessary calculations, and then print the "without depost" report*/
			balance.months = i + 1;
			balance.totalAmount = balance.openingAmount;
			balance.interest = (balance.totalAmount * ((m_annualInterest / 100.0) / 12.0));
			balance.closingAmount = balance.openingAmount + balance.interest;
			withoutDeposit.at(i) = balance;
			if (balance.months % 12 == 0) {
				BankingApp::PrintValues(withoutDeposit, i);
			}
		}
		cout << endl;
		cout << endl;
	}
	catch (invalid_argument& except) {
		cout << "Error. Please try again." << endl; // Print error message if an incorrect input is entered

		if (m_numYears < 0.01 || m_annualInterest < 0.01 || m_numMonths < 0.01 || m_initialInvestment < 0.01
			|| m_monthlyDeposit < 0.01) { // If inputs are less than 0.01 or not numbers then print error message
			throw invalid_argument("Numbers less than .01 are not allowed. Please try again");
		}
	}
	
/* This function will create our report for users who add monthly deposits*/

	vector<Balances> includingDeposit;
	
	try {
		includingDeposit.resize(m_numMonths); // // Add values for 'numMonths' to our vector

		// Generate our header for report with monthly deposits 
		BankingApp::PrintHeader("Balance and Interest Include Additional Monthly Deposits");

		/* Our loop for the report with monthly deposits calculated */

		for (int i = 0; i < m_numMonths; i++) {
			Balances balance;
			if (i == 0) {
				balance.openingAmount = m_initialInvestment; // Share initial investment for first loop only
			}
			else {
				balance.openingAmount = includingDeposit.at(i-1).closingAmount; // Share investments after calculations
			}

			/* Take variable, perform necessary calculations, and then print the "with depost" report*/
			balance.months = i + 1;
			balance.totalAmount = balance.openingAmount + m_monthlyDeposit;
			balance.interest = balance.totalAmount * ((m_annualInterest / 100.0) / 12.0);
			balance.closingAmount = balance.totalAmount + balance.interest;
			includingDeposit.at(i) = balance;
			if (balance.months % 12 == 0) {
				BankingApp::PrintValues(includingDeposit, i);
			}
		}
	}
	catch (...) {
		cout << "Error. Please try again." << endl; // Print error message if an incorrect input is entered
	}
}