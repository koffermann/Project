/* 
CS210: Project Two - Airgead Banking App
Name: Kerrian Offermann
Date: October 1, 2021
File: KOffermann_Airgead.h
*/

#ifndef CSProjects_Project_KOffermann_Airgead_H
#define CSProjects_Project_KOffermann_Airgead_H

#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

using namespace std;


struct Balances { 
	// This structure stores balance information
	/* Identifiers that we need to build reports with and without deposits */
	int months; // Amount of months
	double openingAmount; // Initial amount
	double depositedAmount; // Amount deposited
	double totalAmount; // Total amount
	double interest; // Interest rate
	double closingAmount; // Closing amount
};

class BankingApp {
public:

	BankingApp();
	void SetInterestVariables(); // For setting the function that will take variables from the user
	void LoadBalances(); // For setting the function that will show reports with and without deposits

private:
	double m_initialInvestment; // Variable for initial investment
	double m_monthlyDeposit; // Variable for monthly deposit
	double m_annualInterest; // Variable for annual interest
	int m_numYears; // Variable for number of years
	int m_numMonths; // Variable for nuber of months
	double StrToDouble(string str, char ch); // Setting up the function that will convert strings to double
	void SetInvestment(string t_doubleInput); // Setting up information we need for the initial investment
	void SetDeposit(string t_doubleInput); // Setting up information we need for the monthly deposit
	void SetInterest(string t_intInput); // Setting up information we need for the annual interest
	void SetYears(int t_numYears); // Setting up information we need for the number of years
	void PrintHeader(string t_contentWithOut); // Header specifically for report without deposits
	void PrintValues(vector<Balances> t_currVect, int i); // For printing the accumulated sums of our interests payments
};

#endif // CSProjects_Project_KOffermann_Airgead_H