#ifndef DATE_H
#define DATE_H
#include <string>
#include <iostream>
using namespace std;

string Month[] = { "", "January", "Febraury", "March", "April", "May", "June", "July",
"August", "September", "October", "November", "December" };

int daysInMonth[2][13] = { { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } };
string DOW[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturady" };
class Date{

private:
	int *month;
	int *day;
	int *year;

public:

	// constructors

	Date(int month, int day, int year) : month(new int(month)), day(new int(day)), year(new int(year)) {};
	Date() : month(new int(1)), day(new int(1)), year(new int(1900)) {};     // default constructor

	Date(Date &other){
		month = new int;
		day = new int;
		year = new int;
		*month = *other.month;
		*day = *other.day;
		*year = *other.year;
	};  // copy constructor
	Date(string mmddyyyy){
		month = new int;
		*month = mmddyyyy[0] + mmddyyyy[1];
		day = new int;
		*day = mmddyyyy[2] + mmddyyyy[3];
		year = new int;
		*year = mmddyyyy[4] + mmddyyyy[5] + mmddyyyy[6] + mmddyyyy[7];
	};  // constructor that takes a string as parameter e.g "10/31/2012"

	~Date() {
		delete month; delete day; delete year;
	};

	// overlaod assignment operator 

	Date & operator = (Date & rhs){
		if (*this != rhs){
			delete month;
			delete day;
			delete year;
			month = new int;
			*month = *(rhs.month);
			day = new int;
			*day = *(rhs.day);
			year = new int;
			*year = *(rhs.year);
		}
		return *this;
	};
	
	Date & operator++(){
		int L = (isLeap(*year)) ? 1 : 0;
		if (*month == 12 && *day == 31){
			*day = 1;
			*month = 1;
			*year += 1;
		}
		else if (*day == daysInMonth[L][*month]){
			*day = 1;
			*month += 1;
		}
		else
			*day += 1;
		return *this;
	};
	Date operator++(int){
		Date temp(*this);
		++*this;
		return temp;
	};
	Date & operator--(){
		int L = (isLeap(*year)) ? 1 : 0;
		if (*month == 1 && *day == 1){
			*day = 31;
			*month = 12;
			*year -= 1;
		}
		else if (*day == 1){
			*day = daysInMonth[L][*month - 1];
			*month -= 1;
		}
		else
			*day -= 1;
		return *this;
	};

	Date operator--(int){
		Date temp(*this);
		--*this;
		return temp;
	};
	bool operator ==(Date & rhs){
		return (*month == *rhs.month && *day == *rhs.day && *year == *rhs.year);
	};
	bool operator != (Date & rhs){
		return (*month != *rhs.month && *day != *rhs.day && *year != *rhs.year);
	};
	bool operator > (Date & rhs){
		if (*year > *rhs.year)
			return true;
		else if ((*year == *rhs.year) && (*month > *rhs.month))
			return true;
		else if ((*year == *rhs.year) && (*month == *rhs.month) && (*day > *rhs.day))
			return true;
		else
			return false;
	};

	bool operator < (Date & rhs){
		return !((*this > rhs) && !(*this == rhs));
	};

	int operator-(Date & rhs){
		int L = (isLeap(*year)) ? 1 : 0;
		int rhsL = (isLeap(*rhs.year)) ? 1 : 0;
		int sum = 0;
		int sumY1 = 0;
		int sumY2 = 0;
		if (*this == rhs) return 0;
		if ((*year == *rhs.year) && (*month == *rhs.month))
			return abs(*day - *rhs.day);
		else if ((*year == *rhs.year) && ((*month - *rhs.month) == 1))
			return ((daysInMonth[L][*rhs.month] - *rhs.day) + *day);
		else if ((*year == *rhs.year) && ((*month - *rhs.month) == -1))
			return ((daysInMonth[L][*month] - *day) + *rhs.day);
		else if ((*year == *rhs.year) && ((*month - *rhs.month) > 1)){
			for (int i = (*rhs.month + 1); i < *month; i++)
				sum += daysInMonth[L][i];
			return (sum + ((daysInMonth[L][*rhs.month] - *rhs.day) + *day));
			}
		else if ((*year == *rhs.year) && ((*month - *rhs.month) < 1)){
			for (int i = (*month + 1); i < *rhs.month; i++)
				sum = daysInMonth[L][i];
			return (sum + ((daysInMonth[L][*month] - *day) + *rhs.day));
			}
		else if (*year - *rhs.year == 1){
			for (int i = 1; i < *month; i++)
				sumY1 += daysInMonth[L][i];
			for (int j = (*rhs.month + 1); j < 13; j++)
				sumY2 += daysInMonth[rhsL][j];
			return (sumY1 + sumY2 + *day + (daysInMonth[rhsL][*rhs.month] - *rhs.day));
		}
		else if (*year - *rhs.year == -1){
			for (int i = 1; i < *rhs.month; i++)
				sumY1 += daysInMonth[rhsL][i];
			for (int j = (*month + 1); j < 13; j++)
				sumY2 += daysInMonth[L][j];
			return (sumY1 + sumY2 + *rhs.day + (daysInMonth[L][*month] - *day));
		}
		else if (*year - *rhs.year > 1){
			if (*year - *rhs.year >= 4)
				sum = 365*(*year - (*rhs.year + 1)) + ((*year - *rhs.year) / 4);
			else
				sum = 365*(*year - (*rhs.year + 1));
			for (int i = 1; i < *month; i++)
				sumY1 += daysInMonth[L][i];
			for (int j = (*rhs.month + 1); j < 13; j++)
				sumY2 += daysInMonth[rhsL][j];
			return (sum + sumY1 + sumY2 + *day + (daysInMonth[rhsL][*rhs.month] - *rhs.day));
		}
		else if (*year - *rhs.year < 1){
			if (*rhs.year - *year >= 4)
				sum = 365 * (*rhs.year - (*year + 1)) + ((*rhs.year - *year) / 4);
			else
				sum = 365 * (*rhs.year - (*year + 1));
			for (int i = 1; i < *rhs.month; i++)
				sumY1 += daysInMonth[rhsL][i];
			for (int j = (*month + 1); j < 13; j++)
				sumY2 += daysInMonth[L][j];
			return (sum + sumY1 + sumY2 + *rhs.day + (daysInMonth[L][*month] - *day));
		}
	};

	Date & operator+(int n){
		Date temp(*this);
		for (int i = 0; i < n; i++)
			++*this;
		return *this;
	};

	// accessors

	int getDay() { return *day; }
	int getMonth(){ return *month; }
	int getYear(){ return *year; }

	bool valid(int m, int d, int y){
		int L = (isLeap(y)) ? 1 : 0;
		return !((m < 1 || m > 12) || (d < 1 || d > daysInMonth[L][m]) || (y < 1));
	};   // validate the triple is indeed a valid date
	
	string toAscii(int n){
		string s = to_string(n);
		return s;
	};		//  string representation of the integer

	static Date toDate(int doy, int yr){
		Date temp(1,1,yr);
		for (int i = 0; i < (doy - 1); i++)
			temp++;
		temp.display();
		return temp;
	};  // 

	void display(){
		cout << *month << "/" << *day << "/" << *year << endl;
	};   // display date in the format of   mm/day/year e.g. 10/31/2012


	string toString(){
		int dcode = get_day_code(*year, *month, *day);
		string today;
		today = DOW[dcode] + " " + Month[*month] + " " + toAscii(*day) + ", " + toAscii(*year) + "\n";
		return today;
	}; // returns the string format of dayOfWeek Month Day, Year  e.g. Wednesday October 31, 2012

	static int isLeap(int year) {
		return ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0));
	} // returns true if the given year is a leap year and false otherwise

	static int get_day_code(int year) {
		return (year + (year - 1) / 4 - (year - 1) / 100
			+ (year - 1) / 400) % 7;
	} // returns the day code the the new year day of the given year
	
	static int get_day_code(int year, int month, int day){
		int L = (isLeap(year)) ? 1 : 0; 
		int code = (year + (year - 1) / 4 - (year - 1) / 100
			+ (year - 1) / 400) % 7;
		for (int i = 0; i < month; i++)
			code = (code + daysInMonth[L][i]) % 7;
			if (day > 1)
				code = ((code + day - 1) % 7);
		return code;
	}; // overloading get_day_code that returns the day code of the specific day

	int dayOfWeek(){
		return get_day_code(*year, *month, *day);
	};		// return the day code of this day ;
	
	int dayOfYear(){
		int L = (isLeap(*year)) ? 1 : 0;
		int total = 0;
		if (*month == 1)
			total = *day;
		else{
			for (int i = 0; i < *month; i++){
				total += daysInMonth[L][i];
			}
			total += *day;
		}
		return total;
	}; 		// returns the day of the year, eg,  the day of year for Feb 28 is 59.
	
};

#endif