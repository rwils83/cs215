/* Created By Ryan J. Wilson
CTU CS215
Date of last Modification: 7/7/2018
Referenced code is from Sample Code Week 1 created by Dr. Evans in winter of 2016*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
    // set the variables to use
    int records = 10;
    char test = ' ';
    string studentName[10];
    double gpa[10];
    string lastName;
    string firstName;
    cout << setiosflags(ios::fixed);
    cout << setiosflags(ios::showpoint);
    cout << setprecision(2);
    cout << "Would you like to run this as test?" << endl;
    cin >> test;
    //set ability to run quick test to save typing
    if (test== 'y'){
        for (int i=0; i<records;i++){
        studentName[i] = "test, test";
            if (i < 3){
            gpa[i] = i+.5;}
            else if (i == 3){
            gpa[i] = i;}
            else if (i < 5 & i >3){
            gpa[i] = i-1;}
            else if(i > 5 & i < 9){
            gpa[i] = i-4;}
            else{
            gpa[i]= i-5;}
        }
    }
    else{

    // Modified from Sample Code by Ryan J. Wilson
    for (int i=0; i<records; i++){
        if(i==0){
            cout << "Enter First Student Name(Last, First)" <<endl;
            cin.ignore();
            getline(cin, studentName[i]);
            cout << "Enter Student GPA" << endl;
            cin >>gpa[i];}
         else{
            cout << "Enter the Next Student's Name(Last, First)"<<endl;
            cin.ignore();
            getline(cin, studentName[i]);
            cout << "Enter GPA: " << endl;
            cin >> gpa[i];}
            }}
    cout << setfill(' ') << setw(25) << left << "Student Name" << setw(5) << right << "GPA" << endl;
    //original code by Dr. Evans
    for (int i = 0; i < records; i++){
        string::size_type commaPos = studentName[i].find(",");  //find ","
		lastName = studentName[i].substr(0, commaPos);	// select last name
		firstName = studentName[i].substr(commaPos + 1);	// select first name
		if (firstName[0] == ' ') firstName.erase(0, 1);	// remove blank space between "," and first letter of first name

		// set all letters in first name to lower case, and then set first letter to upper case
		for (int x = 0; x < firstName.length(); x++)
		{
			firstName[x] = tolower(firstName[x]);
		}
		firstName[0] = toupper(firstName[0]);

		// set all letters in last name to lower case, and then set first letter to upper case
		for (int x = 0; x < lastName.length(); x++)
		{
			lastName[x] = tolower(lastName[x]);
		}
		lastName[0] = toupper(lastName[0]);

		// set original studentName variable to proper case formatting
		studentName[i] = lastName + ", " + firstName;

		// print student record
		cout << setfill(' ') << setw(25) << left << studentName[i] << setw(5) << right << gpa[i] << endl;




}

	return 0;
        }
