/************************************************************************************************/
/*   CSC309/404  Homework Assignment #6                                                         */
/*   Name :  Joshua Iverson																		*/
/*   Due Date :   June 1, 2014                                                                  */
/*   Compiler : Miscrosoft Visual Studio 2013 C++												*/
/*                                                                                              */
/************************************************************************************************/


#include <iostream>
#include <string>
#include <iomanip>
#include "Date.h"
#include <fstream>

using namespace std;

void app1();
void app2();
void print_calendar(int year);
char *major[] = { "New Year Day", "MLK Birthday", "Valentine's Day", "President Day", "St.Patrick's Day", "April Fools", "Tax Day", "May Day", "Mother's Day",
"Memorial Day", "Father's Day", "Independence Day", "Labor Day", "Grandparent's Day",
"Columbus Day", "Halloween", "Election Day", "Veterans Day", "Thanksgiving Day", "Christmas" };
char * dayofweek[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

void print_calendar(int year, ostream &out);

//The menu function simply presents the options of the program to the user. 
void menu() {
	cout << "\n\t\tType 1 for major holidays ";
	cout << "\n\t\tType 2 for Calendar  ";
	cout << "\n\t\tType 3 to quit.";
	cout << "\n\n\t\tPlease enter your choice :";;

}

Date dayLightSaving(int yr, Date& end);

//The main function calls the functions as dictated by the user and outputs a calendar to a file if requested by the user.
int main() {	
	Date partIII;
	dayLightSaving(2014, partIII);
	
	/*int choice;
	cout << endl << endl << "\tWelcome to CSC404  Holidays/  Calendar System: \n\n";
	while (true) {
		menu();
		cin >> choice;

		switch (choice) {
		case 1: app1(); break;
		case 2: app2(); break;
		case 3: break;
		default:  cout << "\n\n\t\tInvalid choice \n"; break;
		}
		if (choice == 3) break;

	}

	cout << "\n\n\tThank you for using U.S. Major Holidays Calendar System! \n";
	cout << "\n\n\t\tBye! \n\n";*/
	return 0;
}

///////////////////////////////
Date NewYear(int yr) {
	Date tmp(1, 1, yr);
	return tmp;
}
// MLK day third monday of January
Date MLKDay(int yr) {
	Date temp(1, 16, yr);
	while (temp.dayOfWeek() != 1)
		++temp;
	return temp;
}

Date Valentine(int yr) {
	return Date(2, 14, yr);
}

Date PresidentDay(int yr) {  // 3rd monday of Febraury
	Date temp(2, 16, yr);
	while (temp.dayOfWeek() != 1)
		++temp;
	return temp;
}

Date StPatrick(int yr) {  //mar 17
	Date temp(3, 17, yr);
	return temp;
}

Date AprilFool(int yr){
	return Date(4, 1, yr);
}

Date MayDay(int yr) {  // May ist
	Date tmp(5, 1, yr);
	return tmp;
}
Date MotherDay(int yr) {  // 2nd sunday in may
	Date temp(5, 8, yr);
	while (temp.dayOfWeek() != 0)
		++temp;
	return temp;
}
Date MemorialDay(int yr) {
	Date temp(5, 25, yr);
	while (temp.dayOfWeek() != 1)
		++temp;
	return temp;
}

Date FatherDay(int yr) {  // 3rd sunday in June
	Date temp(6, 15, yr);
	while (temp.dayOfWeek() != 0)
		++temp;
	return temp;
}

Date IndependenceDay(int yr) {  // July 4
	Date tmp(7, 4, yr);
	return tmp;
}


Date Labor(int yr) {
	Date temp(9, 1, yr);
	while (temp.dayOfWeek() != 1)
		++temp;
	return temp;
}

Date Columbus(int yr) {  // second monday of october
	Date temp(10, 8, yr);
	while (temp.dayOfWeek() != 1)
		++temp;
	return temp;
}

Date Halloween(int yr) {
	Date tmp(11, 1, yr);    // november 1st, a day after Halloween
	return --tmp;
}
Date ElectionDay(int yr) {  // 1st tuesday after 1st monday in november
	Date temp(11, 1, yr);
	if (temp.dayOfWeek() == 0)
		temp + 2;
	else if (temp.dayOfWeek() == 1)
		temp + 1;
	else
		temp + 3;
	while (temp.dayOfWeek() != 2)
		++temp;
	return temp;
}

Date VeteransDay(int yr) {    // Nov 11
	Date temp(11, 11, yr);
	return temp;
}

//April 15th, unless on a weekend.
Date TaxDay(int yr) {
	Date temp(4, 15, yr);
	if (temp.dayOfWeek() != 0 || temp.dayOfWeek() != 6)
		return temp;
	else if (temp.dayOfWeek() == 0)
		return ++temp;
	else if (temp.dayOfWeek() == 6)
		return temp + 2;
}

//First Sunday after Labor Day.
Date Grandparent(int yr) {
	Date temp = Labor(yr) + 6;
	return temp;
}
Date thanksgiving(int yr) { //  the fourth thursday of Novemeber
	Date temp(11, 22, yr);
	while (temp.dayOfWeek() != 4)
		++temp;
	return temp;
}

Date xmas(int yr) {
	return Date(12, 25, yr);
}

Date dayLightSaving(int yr, Date& end){
	Date start(3, 8, yr);
	Date temp(11, 1, yr);
	while (temp.dayOfWeek() != 0)
		++temp;
	end = temp;
		
	while (start.dayOfWeek() != 0)
		++start;
	return start;
}

// an array of  function pointers
Date(*fp[20])(int) = { NewYear, MLKDay, Valentine, PresidentDay, StPatrick, AprilFool, TaxDay, MayDay, MotherDay, MemorialDay,
FatherDay, IndependenceDay, Labor, Grandparent, Columbus, Halloween, ElectionDay, VeteransDay, thanksgiving, xmas };

//Output for the function that calls the array of function pointers, which is the name of the holiday and the day of the week, followed by the date. 
void process(Date(*fun)(int), int yr, int index){
	Date d = fun(yr);
	string holiday;
	holiday = d.toString();
	cout << setw(25) << right << major[index] << " | " << holiday << endl;
}

//This function accepts a year from the user and calls the process function with that year. 
void app1() {


	int yr;

	while (true) {

		cout << "\tPlease enter the year (4 digits) or -1  to quit: ";
		cin >> yr;
		if (yr < 0) break;
		cout << "\n\n\t\tMajor holidays for year " << yr << endl << endl;


		for (int i = 0; i < 18; i++) process(fp[i], yr, i);

		cout << endl << endl;
	}

}

//This function outputs a calendar to the console for a year given by the user or writes the calendar to a file
//with a file name given by the user. 
void app2() {


	int yr;
	char resp[10];
	string filename;
	ofstream out;

	cout << "\n\tDo your want to write to a file?";
	cin >> resp;

	if (resp[0] == 'y' || resp[0] == 'Y'){
		cout << "\n\tPlease enter the file name: ";
		cin >> filename;
		filename += ".txt";
		out.open(filename, ios::app);
	}

	while (true) {

		cout << "\tPlease enter the year (4 digits) or -1  to quit: ";
		cin >> yr;
		if (yr < 0) break;
		cout << "\n\n\t\tCalendar for year " << yr << endl << endl;
		out << "\n\n\t\tCalendar for year " << yr << endl << endl;

		if (resp[0] == 'y' || resp[0] == 'Y'){
			cout << "\t\tloaded to " << filename << "." << endl << endl;
			print_calendar(yr, out);
		}
		else print_calendar(yr, cout);

		cout << endl << endl;
	}
	if (resp[0] == 'y' || resp[0] == 'Y'){
		out.close();
	}
}

//This function loops through twelve months and the applicable number of days in the year,
//plus the number of days the month needs to be offset, which is the first day of the month.
void print_calendar(int year, ostream &out) {
	int m = 1;
	Date cal(m, 1, year);
	int L = cal.isLeap(year) ? 1 : 0;
	static int tots = daysInMonth[L][m] + cal.get_day_code(year, m, 1);
	for (m = 1; m < 13; m++){
		out << "\n\n\t" << Month[cal.getMonth()] << " " << cal.getYear() << "\n" << endl;
		out << setw(5) << left << "Sun" << setw(5) << left << "Mon" <<
			setw(5) << left << "Tue" << setw(5) << left << "Wed" <<
			setw(5) << left << "Thu" << setw(5) << left << "Fri" <<
			setw(5) << left << "Sat" << endl;
		for (int k = 0; k < tots; k++){
			if (k < cal.get_day_code(cal.getYear(), cal.getMonth(), 1)){
				out << setw(5) << left << " ";
			}
			else if (cal.dayOfWeek() == 6){
				out << setw(5) << left << cal.getDay() << "\n";
				++cal;
			}
			else{
				out << setw(5) << left << cal.getDay();
				++cal;
			}
			tots = daysInMonth[L][m] + cal.get_day_code(year, m, 1);
		}
	}
	out.flush();
}

