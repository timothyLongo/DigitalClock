//Timothy Longo


#include <iostream> // to get input and output
#include <iomanip> // for text alignment and formatting
#include <Windows.h> // for sleep function


using namespace std;


void Get_Time_24(int &c_h, int &c_m, int &c_s) {
	//setting up the time
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	//using hours var to manipulate the time based on user input
	int hours = newtime.tm_hour + c_h; // if user_in is 1 this is updated
	int mins = newtime.tm_min + c_m; // if user_in is 2 this is updated
	int secs = newtime.tm_sec + c_s; // if user_in is 3 this is updated
	// since the increment logic is defined in get_time_12 then passed here

	while (secs > 59) {
		secs = secs - 60;
		mins += 1;
		if (mins > 59) {
			mins = mins - 60;
			hours += 1;
		}
		continue;
	}
	while (mins > 59) {
		mins = mins - 60;
		hours += 1;
		continue;
	}
	while (hours > 23) {
		hours = hours - 24;
		continue;
	}
	// this section corrects 2:3:4 to 02:03:04
	// setfill and right alignment carry over
	cout << setfill('0') << right << setw(2) << hours << ":";
	cout << setw(2) << mins;
	cout << ":";
	cout << setw(2) << secs;
}


void Get_Time_12(int user_in, int & c_h, int &c_m, int &c_s) {
	// setting up the time
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	// using int variable to manipulate the hour to 12 hour based time
	int hours = newtime.tm_hour + c_h; // ensures each time function is called changes are saved
	// using vars to manipulate all 
	int mins = newtime.tm_min + c_m;
	int secs = newtime.tm_sec + c_s;
	int ampmCycleCount = 2;
	int hoursForCycle = newtime.tm_hour + c_h;
	string ampm = " AM";
	
	if (user_in == 1) {
		hours = hours + 1;
		hoursForCycle += 1;
		c_h += 1; // should be the ONLY increment. then passed to the 24 hour clock which is called AFTER
	}
	if (user_in == 2) {
		mins = mins + 1;
		c_m += 1; // only increment
	}
	if (user_in == 3) {
		secs = secs + 1;
		c_s += 1; // only increment
	}
	while (mins > 59) {
		mins = mins - 60;
		hours += 1;
		hoursForCycle += 1;
		continue;
	}
	while (secs > 59) {
		secs = secs - 60;
		mins += 1;
		if (mins > 59) {
			mins = mins - 60;
			hours += 1;
			hoursForCycle += 1;
		}
		continue;
	}
	// am / pm cycle logic
	while (hoursForCycle > 11) {
		hoursForCycle = hoursForCycle - 12;
		ampmCycleCount += 1;
		continue;
	}
	if (ampmCycleCount % 2 == 1) {
		ampm = " PM";
	}
	while (hours > 12) {
		hours = hours - 12;
		continue;
	}
	cout << setfill('0') << right << setw(2) << hours << ":";
	cout << setw(2) << mins;
	cout << ":";
	cout << setw(2) << secs;
	cout << ampm;
}


void Let_There_Be_Clocks(int user_in, int &c_h, int &c_m, int &c_s) {
	// clocks must be in proper format NEXT TO EACH OTHER
	cout << setfill('*') << setw(18) << "";
	cout << setfill(' ') << setw(3) << "";
	cout << setfill('*') << setw(18) << "" << endl;
	cout << setfill(' ') << left << "* ";
	cout << setw(14) << "12-Hour Clock" << right << setw(2) << "*";
	cout << setw(3) << "";
	cout << left << setw(2) << "* ";
	cout << setw(14) << "24-Hour Clock" << right << setw(2) << "*" << endl;
	cout << left << setw(2) << "*";
	Get_Time_12(user_in, c_h, c_m, c_s); // calls 12-hour clock
	cout << setfill(' ') << setw(5) << "*" << setw(5) << "* ";
	Get_Time_24(c_h, c_m, c_s); // calls 24-hour clock
	cout << setfill(' ') << setw(8) << "*" << endl;
	cout << setfill('*') << setw(18) << "";
	cout << setfill(' ') << setw(3) << "";
	cout << setfill('*') << setw(18) << "" << endl;
}


void DisplayMenu(int &c_h, int &c_m, int &c_s) {
	cout << endl;
	// displays menu using appropriate syntax for text alignment formatting
	cout << setfill('*') << setw(23) << "" << endl;
	cout << setfill(' ');
	cout << "* " << left << setw(20) << "[1] Add One Hour" << "*" << endl;
	cout << "* " << left << setw(20) << "[2] Add One Minute" << "*" << endl;
	cout << "* " << left << setw(20) << "[3] Add One Second" << "*" << endl;
	cout << "* " << left << setw(20) << "[4] Confirm Time" << "*" << endl;
	cout << "* " << left << setw(20) << "[5] Exit" << "*" << endl;
	cout << setfill('*') << setw(23) << "" << endl;

	bool keeploopin = true;
	while (keeploopin) {
		string user_in;
		cout << endl;
		cin >> user_in;
		if (user_in.at(0) == '1') {
			system("CLS");
			Let_There_Be_Clocks(1, c_h, c_m, c_s);
			DisplayMenu(c_h, c_m, c_s);
			break;
		}
		else if (user_in.at(0) == '2') {
			system("CLS");
			Let_There_Be_Clocks(2, c_h, c_m, c_s);
			DisplayMenu(c_h, c_m, c_s);
			break;
		}
		else if (user_in.at(0) == '3') {
			system("CLS");
			Let_There_Be_Clocks(3, c_h, c_m, c_s);
			DisplayMenu(c_h, c_m, c_s);
			break;
		}
		else if (user_in.at(0) == '4') {
			bool keepLoopin = true;
			while (keepLoopin) { // this displays the ticking clock infinitely
				system("CLS");
				Let_There_Be_Clocks(0, c_h, c_m, c_s);
				Sleep(1000);
				continue;
			}
		}
		else if (user_in.at(0) == '5') {
			system("CLS");
			cout << endl << "Good bye!" << endl;
			keeploopin = false;
			break;
		}
		else {
			system("CLS");
			cout << endl << "Invalid input -- Try again" << endl << endl;
			Let_There_Be_Clocks(0, c_h, c_m, c_s);
			DisplayMenu(c_h, c_m, c_s);
			break;
		}
	}
}


int main() {

	// to my knowledge c++ doesn't support global variables like python does, so these are passed by reference
	int c_h = 0; // to count how many requests to add an hour
	int c_m = 0; // to count how many requests to add a min
	int c_s = 0; // to count how many requests to add a sec
	// these variables are passed by reference ultimately to the get_time functions
	// because the get_time functions set the current time, every time they are called
	// so a count is necessary to save multipule changes

	Let_There_Be_Clocks(0, c_h, c_m, c_s);
	DisplayMenu(c_h, c_m, c_s); 
	// so this prompts user with the options to change the time, which is updated every time with the current time.
	// when user confirms time, the clock ticks as a wrist watch would after setting the time

	return 0;
}