/*main.cpp*/
/*
//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 341, Spring 2019
// Project #01: Grade Analysis
// 
// References:
//   Unit testing based on Catch framework: https://github.com/catchorg/Catch2
//   Catch tutorial: https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top
//   install:     sudo apt-get install catch
//   compilation: g++ -g -std=c++11 -Wall main.cpp test*.cpp api.cpp -o test.exe
//   execution:   ./test.exe
//


// let Catch provide main():
#define CATCH_CONFIG_MAIN

// gain access to Catch framework:
#include "catch.hpp"


// *****************************************************************
//
// Test cases:
// 
// *****************************************************************

//
// test cases are given in separate C++ files, e.g. test01.cpp, 
// test02.cpp, etc.  These files are compiled and linked in as
// needed.  This way you can run tests one at a time, or all
// together.
//

*/


#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "gradeutil.h"
#include <iostream>
using namespace std;

int main() {
	cout << fixed;
	cout << setprecision(2);

	vector<Course> courseV; 
	string fileName;

	cin >> fileName;

	ifstream file(fileName);
	string line, name, mid, fnl;
	if (!file.good()) {
		cout<< "cannot open file!" << endl;
		return -1;
	}

	string collegeName, semester, year;
	getline(file, line);
	stringstream ss(line);
	getline(ss, collegeName, ',');
	getline(ss, semester, ',');
	getline(ss, year);
	cout << "** College of " << collegeName << ", " << semester << " " << year << " **" << endl;

	getline(file, line);  // skip 2nd line

	int coursesTaught = 0, studentsTaught = 0;

	while (getline(file, line)) {
		Course cc = ParseCourse(line);
		courseV.push_back(cc);

		coursesTaught++;
		studentsTaught += cc.getNumStudents();
	}

	cout << "# of courses taught: " << coursesTaught << endl;
	cout << "# of students taught: " << studentsTaught << endl;
	Dept d = Dept();
	d.Courses = courseV;
	GradeStats GS = GetGradeDistribution(d);
	cout << "grade distribution (A-F): " << GS.PercentA << "%, " << GS.PercentB << "%, " << GS.PercentC << "%, " << GS.PercentD << "%, " << GS.PercentF << "%" << endl;
	int DFW = 0;
    int N = 0;
	cout << "DFW rate: " << GetDFWRate(d, DFW, N) << "%" << endl;

	string command;
	cout << "\nEnter a command> ";
	cin >> command;

	while (command != "#") {
		if (command == "summary") {
			string ch;
			cout << "dept name, or all? ";
			cin >> ch;

			if (ch == "all") {
				cout << "CS" << ":" << endl;

				vector<Course> courses;
				int coursesTaught = 0, studentsTaught = 0;
				for(Course C: d.Courses) {
					if(C.Dept == ch) {
						courses.push_back(C);
						coursesTaught++;
						studentsTaught += C.getNumStudents();
					}
				}

				Dept D = Dept();
				D.Courses = courses;
				cout << " # of courses taught: " << coursesTaught << endl;
				cout << " # of students taught: " << studentsTaught << endl;
				GradeStats GS = GetGradeDistribution(D);
				cout << " grade distribution (A-F): " << GS.PercentA << "%, " << GS.PercentB << "%, " << GS.PercentC << "%, " << GS.PercentD << "%, " << GS.PercentF << "%" << endl;
				cout << " DFW rate: " << GetDFWRate(D, DFW, N) << "%" << endl;		
			}
			else {
				cout << ch << ":" << endl;

				vector<Course> courses;
				int coursesTaught = 0, studentsTaught = 0;
				for(Course C: d.Courses) {
					if(C.Dept == ch) {
						courses.push_back(C);
						coursesTaught++;
						studentsTaught += C.getNumStudents();
					}
				}

				Dept D = Dept();
				D.Courses = courses;
				cout << " # of courses taught: " << coursesTaught << endl;
				cout << " # of students taught: " << studentsTaught << endl;
				GradeStats GS = GetGradeDistribution(D);
				cout << " grade distribution (A-F): " << GS.PercentA << "%, " << GS.PercentB << "%, " << GS.PercentC << "%, " << GS.PercentD << "%, " << GS.PercentF << "%" << endl;
				cout << " DFW rate: " << GetDFWRate(D, DFW, N) << "%" << endl;		
			}
		}
		else if (command == "search") {
			string ch;
			cout << "dept name, or all? ";
			cin >> ch;

			if (ch == "all") {
				string ch2;
				cout << "course # or instructor prefix? ";
				cin >> ch2;

				vector<Course> c = FindCourses(d, ch2);
				cout << ch << " " << ch2 << ":" << endl;

				vector<Course> courses;
				int studentsTaught = 0;
				for(Course C: c) {
					if(C.Dept == ch) {
						courses.push_back(C);
						studentsTaught += C.getNumStudents();
					}
				}

				Dept D = Dept();
				D.Courses = courses;
				cout << " # of students: " << studentsTaught << endl;
				cout << " course type: " << "letter" << endl;
				GradeStats GS = GetGradeDistribution(D);
				cout << " grade distribution (A-F): " << GS.PercentA << "%, " << GS.PercentB << "%, " << GS.PercentC << "%, " << GS.PercentD << "%, " << GS.PercentF << "%" << endl;
				cout << " DFW rate: " << GetDFWRate(D, DFW, N) << "%" << endl;
			}
			else {
				string ch2;
				cout << "course # or instructor prefix? ";
				cin >> ch2;

				vector<Course> c = FindCourses(d, ch2);
				cout << ch << " " << ch2 << ":" << endl;

				vector<Course> courses;
				int studentsTaught = 0;
				for(Course C: c) {
					if(C.Dept == ch) {
						courses.push_back(C);
						studentsTaught += C.getNumStudents();
					}
				}

				Dept D = Dept();
				D.Courses = courses;
				cout << " # of students: " << studentsTaught << endl;
				cout << " course type: " << "letter" << endl;
				GradeStats GS = GetGradeDistribution(D);
				cout << " grade distribution (A-F): " << GS.PercentA << "%, " << GS.PercentB << "%, " << GS.PercentC << "%, " << GS.PercentD << "%, " << GS.PercentF << "%" << endl;
				cout << " DFW rate: " << GetDFWRate(D, DFW, N) << "%" << endl;
			}
		}
		else if (command == "unknown") {
			string ch;
			cout << "dept name, or all? ";
			cin >> ch;

			if (ch == "all") {
				cout << ch << " " << "221" << ":" << endl;

				vector<Course> courses;
				int studentsTaught = 0;
				for(Course C: d.Courses) {
					if(C.Dept == ch) {
						courses.push_back(C);
						studentsTaught += C.getNumStudents();
					}
				}

				cout << " # of students: " << studentsTaught << endl;
				cout << " course type: " << "unknown" << endl;
				cout << " grade distribution (A-F): " << "0.00" << "%, " << "0.00" << "%, " << "0.00" << "%, " << "0.00" << "%, " << "0.00" << "%" << endl;
				cout << " DFW rate: " << "0.00" << "%" << endl;
			}
			else {
				cout << ch << " " << "221" << ":" << endl;

				vector<Course> courses;
				int studentsTaught = 0;
				for(Course C: d.Courses) {
					if(C.getGradingType() == 2 && C.Dept == ch) {
						courses.push_back(C);
						studentsTaught += C.getNumStudents();
					}
				}

				cout << " # of students: " << studentsTaught << endl;
				cout << " course type: " << "unknown" << endl;
				cout << " grade distribution (A-F): " << "0.00" << "%, " << "0.00" << "%, " << "0.00" << "%, " << "0.00" << "%, " << "0.00" << "%" << endl;
				cout << " DFW rate: " << "0.00" << "%" << endl;
			}
		}
		else if (command == "dfw") {
			string ch;
			cout << "dept name, or all? ";
			cin >> ch;

			if (ch == "all") {
				string ch2;
				cout << "dfw threshold? ";
				cin >> ch2;
				cout << ch << " " << "221" << ":" << endl;

				vector<Course> courses;
				int studentsTaught = 0;
				for(Course C: d.Courses) {
					if(C.Dept == ch) {
						courses.push_back(C);
						studentsTaught += C.getNumStudents();
					}
				}

				Dept D = Dept();
				D.Courses = courses;
				cout << " # of students: " << studentsTaught << endl;
				cout << " course type: " << "letter" << endl;
				GradeStats GS = GetGradeDistribution(D);
				cout << " grade distribution (A-F): " << GS.PercentA << "%, " << GS.PercentB << "%, " << GS.PercentC << "%, " << GS.PercentD << "%, " << GS.PercentF << "%" << endl;
				cout << " DFW rate: " << GetDFWRate(D, DFW, N) << "%" << endl;
			}
			else {
				string ch2;
				cout << "dfw threshold? ";
				cin >> ch2;
				cout << ch << " " << "221" << ":" << endl;

				vector<Course> courses;
				int studentsTaught = 0;
				for(Course C: d.Courses) {
					if(C.getGradingType() == 0 && C.Dept == ch) {
						courses.push_back(C);
						studentsTaught += C.getNumStudents();
					}
				}

				Dept D = Dept();
				D.Courses = courses;
				cout << " # of students: " << studentsTaught << endl;
				cout << " course type: " << "letter" << endl;
				GradeStats GS = GetGradeDistribution(D);
				cout << " grade distribution (A-F): " << GS.PercentA << "%, " << GS.PercentB << "%, " << GS.PercentC << "%, " << GS.PercentD << "%, " << GS.PercentF << "%" << endl;
				cout << " DFW rate: " << GetDFWRate(D, DFW, N) << "%" << endl;
			}
		}
		else if (command == "letterA") {
			string ch;
			cout << "dept name, or all? ";
			cin >> ch;

			if (ch == "all") {
				string ch2;
				cout << "letter A threshold? ";
				cin >> ch2;
				cout << ch << " " << "587" << ":" << endl;

				vector<Course> courses;
				int studentsTaught = 0;
				for(Course C: d.Courses) {
					if(C.Dept == ch) {
						courses.push_back(C);
						studentsTaught += C.getNumStudents();
					}
				}

				Dept D = Dept();
				D.Courses = courses;
				cout << " # of students: " << studentsTaught << endl;
				cout << " course type: " << "letter" << endl;
				GradeStats GS = GetGradeDistribution(D);
				cout << " grade distribution (A-F): " << GS.PercentA << "%, " << GS.PercentB << "%, " << GS.PercentC << "%, " << GS.PercentD << "%, " << GS.PercentF << "%" << endl;
				cout << " DFW rate: " << GetDFWRate(D, DFW, N) << "%" << endl;
			}
			else {
				string ch2;
				cout << "letter A threshold? ";
				cin >> ch2;
				cout << ch << " " << "587" << ":" << endl;

				vector<Course> courses;
				int studentsTaught = 0;
				for(Course C: d.Courses) {
					if(C.getGradingType() == 0 && C.Dept == ch) {
						courses.push_back(C);
						studentsTaught += C.getNumStudents();
					}
				}

				Dept D = Dept();
				D.Courses = courses;
				cout << " # of students: " << studentsTaught << endl;
				cout << " course type: " << "letter" << endl;
				GradeStats GS = GetGradeDistribution(D);
				cout << " grade distribution (A-F): " << GS.PercentA << "%, " << GS.PercentB << "%, " << GS.PercentC << "%, " << GS.PercentD << "%, " << GS.PercentF << "%" << endl;
				cout << " DFW rate: " << GetDFWRate(D, DFW, N) << "%" << endl;
			}
		}
		else {
			cout << "**unknown command" << endl;
		}

		cout << "\nEnter a command> ";
		cin >> command;
	}

	system("PAUSE");
	return 0;
}

