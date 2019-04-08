#include "gradeutil.h"

/*gradeutil.cpp*/

//
// Name : Prachi Thakkar
// U. of Illinois, Chicago
// CS 341, Spring 2019
// Project #02: GradeUtil API
//

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include "gradeutil.h"

using namespace std;


//
// API:
//

//
// ParseCourse:
//
// Parses a CSV (comma-separated values) line into a Course
// object, which is then returned.  The given line must have
// the following format:
//
//   Dept,Number,Section,Title,A,B,C,D,F,I,NR,S,U,W,Instructor
//
// Example:
//   BIOE,101,01,Intro to Bioengineering,22,8,2,1,0,1,0,0,0,5,Eddington
//
// Note the lack of spaces, except perhaps in the title.
// If the given line does not have this format, the behavior
// of the function is undefined (it may crash, it may throw
// an exception, it may return).
//
Course ParseCourse(string csvline)
{
    string Dept, Title, Instructor, Number, Section, NumA, NumB, NumC, NumD, NumF, NumI, NumS, NumU, NumW, NumNR;

    stringstream ss(csvline);
    // parse line:
    getline(ss, Dept, ',');
    getline(ss, Number, ',');
    getline(ss, Section, ',');
    getline(ss, Title, ',');
    getline(ss, NumA, ',');
    getline(ss, NumB, ',');
    getline(ss, NumC, ',');
    getline(ss, NumD, ',');
    getline(ss, NumF, ',');
    getline(ss, NumI, ',');
    getline(ss, NumNR, ',');
    getline(ss, NumS, ',');
    getline(ss, NumU, ',');
    getline(ss, NumW, ',');
    getline(ss, Instructor);

    Course C(Dept, Title, stoi(Number), stoi(Section), Instructor, stoi(NumA), stoi(NumB), stoi(NumC), stoi(NumD), stoi(NumF), stoi(NumI), stoi(NumS), stoi(NumU), stoi(NumW), stoi(NumNR));

    return C;
}


//
// GetDFWRate:
//
// Returns the DFW rate as a percentage for a given course,
// department, or college.  For a course whose grading type
// is defined as Course::Letter, the DFW rate is defined as
//
//   # of D grades + F grades + Withdrawals
//   -------------------------------------- * 100.0
//   # of A, B, C, D, F grades + Withdrawls
//
// The numerator is returned via the reference parameter DFW;
// the denominator is returned via the reference parameter N.
// If the course grading type is not Course::Letter, the DFW
// rate is 0.0, and parameters DFW and N are set to 0.
//
// When computed for a dept or college, all courses of type
// Course::Letter are considered in computing an overall DFW
// rate for the dept or college.  The reference parameters
// DFW and N are also computed across the dept or college.
//
double GetDFWRate(const Course& c, int& DFW, int& N)
{
	if (c.getGradingType() == 0) {
		DFW = c.NumD + c.NumF + c.NumW;
		N = c.NumA + c.NumB + c.NumC + c.NumD + c.NumF + c.NumW;

		return ((double)DFW / N) * 100;
	}

	DFW = 0;
	N = 0;
	return 0.0;
}

double GetDFWRate(const Dept& dept, int& DFW, int& N)
{
	double overAllDFW = 0, averages = 0;
	int counter = 0;
	bool isCourseTypeLetter = false;

	for(Course c: dept.Courses) {
		if(c.getGradingType() == 0) {
			DFW = c.NumD + c.NumF + c.NumW;
			N = c.NumA + c.NumB + c.NumC + c.NumD + c.NumF + c.NumW;

			overAllDFW += ((double)DFW / N);
			counter++;
			isCourseTypeLetter = true;
		}
	}

	if (isCourseTypeLetter) {
		return ((double)overAllDFW / counter) * 100;
	}

	else {
		DFW = 0;
		N = 0;

		return 0.0;
	}
}

double GetDFWRate(const College& college, int& DFW, int& N)
{
	double overAllDFW = 0;
	int counter = 0;
	bool isCourseTypeLetter = false;

	for (Dept d: college.Depts) {
		for(Course c: d.Courses) {
			if(c.getGradingType() == 0) {
				DFW = c.NumD + c.NumF + c.NumW;
				N = c.NumA + c.NumB + c.NumC + c.NumD + c.NumF + c.NumW;

				overAllDFW += ((double)DFW / N);
				counter++;
				isCourseTypeLetter = true;
			}
		}
	}

	if (isCourseTypeLetter) {
		return ((double)overAllDFW / counter) * 100;
	}

	else {
		DFW = 0;
		N = 0;

		return 0.0;
	}
}


//
// GetGradeDistribution
//
// Returns an object containing the grade distribution for a given
// course, dept or college.  For a course whose grading type is
// defined as Course::Letter, the grade distribution is defined by
// the following values:
//
//   N: the # of A, B, C, D, F grades
//   NumA, NumB, NumC, NumD, NumF: # of A, B, C, D, F grades
//   PercentA, PercentB, PercentC, PercentD, PercentF: % of A, B,
//     C, D, F grades.  Example: PercentA = NumA / N * 100.0
//
// If the course grading type is not Course::Letter, all values
// are 0.  When computed for a dept or college, all courses of
// type Course::Letter are considered in computing an overall
// grade distribution for the dept or college.
//
GradeStats GetGradeDistribution(const Course& c)
{
	if (c.getGradingType() == 0) {
		GradeStats GS;

		GS.N = c.NumA + c.NumB + c.NumC + c.NumD + c.NumF;
		GS.NumA = c.NumA;
		GS.NumB = c.NumB;
		GS.NumC = c.NumC;
		GS.NumD = c.NumD;
		GS.NumF = c.NumF;
		GS.PercentA = ((double)GS.NumA / GS.N) * 100.0;
		GS.PercentB = ((double)GS.NumB / GS.N) * 100.0;
		GS.PercentC = ((double)GS.NumC / GS.N) * 100.0;
		GS.PercentD = ((double)GS.NumD / GS.N) * 100.0;
		GS.PercentF = ((double)GS.NumF / GS.N) * 100.0;

		return GS;
	}

	return GradeStats();
}

GradeStats GetGradeDistribution(const Dept& dept)
{
	int counter = 0;
	bool isCourseTypeLetter = false;
	GradeStats GS = GradeStats();

	for(Course c : dept.Courses) {
		if (c.getGradingType() == 0) {
			GS.N += c.NumA + c.NumB + c.NumC + c.NumD + c.NumF;
			GS.NumA += c.NumA;
			GS.NumB += c.NumB;
			GS.NumC += c.NumC;
			GS.NumD += c.NumD;
			GS.NumF += c.NumF;
			GS.PercentA += ((double)GS.NumA / GS.N);
			GS.PercentB += ((double)GS.NumB / GS.N);
			GS.PercentC += ((double)GS.NumC / GS.N);
			GS.PercentD += ((double)GS.NumD / GS.N);
			GS.PercentF += ((double)GS.NumF / GS.N);

			isCourseTypeLetter = true;
			counter++;
		}
	}

	if (isCourseTypeLetter) {
		GS.N = (double)GS.N / counter;
		GS.NumA = (double)GS.NumA / counter;
		GS.NumB = (double)GS.NumB / counter;
		GS.NumC = (double)GS.NumC / counter;
		GS.NumD = (double)GS.NumD / counter;
		GS.NumF = (double)GS.NumF / counter;
		GS.PercentA = (double)GS.PercentA / counter * 100.0;
		GS.PercentB = (double)GS.PercentB / counter * 100.0;
		GS.PercentC = (double)GS.PercentC / counter * 100.0;
		GS.PercentD = (double)GS.PercentD / counter * 100.0;
		GS.PercentF = (double)GS.PercentF / counter * 100.0;

		return GS;
	}

	else {
		return GradeStats();
	}
}

GradeStats GetGradeDistribution(const College& college)
{
	int counter = 0;
	bool isCourseTypeLetter = false;
	GradeStats GS = GradeStats();

	for(Dept d : college.Depts) {
		for(Course c : d.Courses) {
			if (c.getGradingType() == 0) {
				GS.N += c.NumA + c.NumB + c.NumC + c.NumD + c.NumF;
				GS.NumA += c.NumA;
				GS.NumB += c.NumB;
				GS.NumC += c.NumC;
				GS.NumD += c.NumD;
				GS.NumF += c.NumF;
				GS.PercentA += ((double)GS.NumA / GS.N);
				GS.PercentB += ((double)GS.NumB / GS.N);
				GS.PercentC += ((double)GS.NumC / GS.N);
				GS.PercentD += ((double)GS.NumD / GS.N);
				GS.PercentF += ((double)GS.NumF / GS.N);

				isCourseTypeLetter = true;
				counter++;
			}
		}
	}

	if (isCourseTypeLetter) {
		GS.N = (double)GS.N / counter;
		GS.NumA = (double)GS.NumA / counter;
		GS.NumB = (double)GS.NumB / counter;
		GS.NumC = (double)GS.NumC / counter;
		GS.NumD = (double)GS.NumD / counter;
		GS.NumF = (double)GS.NumF / counter;
		GS.PercentA = (double)GS.PercentA / counter * 100.0;
		GS.PercentB = (double)GS.PercentB / counter * 100.0;
		GS.PercentC = (double)GS.PercentC / counter * 100.0;
		GS.PercentD = (double)GS.PercentD / counter * 100.0;
		GS.PercentF = (double)GS.PercentF / counter * 100.0;

		return GS;
	}

	else {
		return GradeStats();
	}
}


//
// FindCourses(dept, courseNumber)
//
// Searches the courses in the department for those that match
// the given course number.  If none are found, then the returned
// vector is empty.  If one or more courses are found, copies of
// the course objects are returned in a vector, and returned in
// ascending order by section number.
//
vector<Course> FindCourses(const Dept& dept, int courseNumber)
{
	vector<Course> courses;

	for(Course C: dept.Courses) {
		if(C.Number == courseNumber) {
			Course newCourse = C;
			courses.push_back(newCourse);
		}
	}

	sort(courses.begin(), courses.end(), [](Course c1, Course c2){
	// primary sort by section number, ascending:
	if (c1.Section < c2.Section)
		return true;
	else
		return false;
	});

	return courses;
}


//
// FindCourses(dept, instructorPrefix)
//
// Searches the courses in the department for those whose
// instructor name starts with the given instructor prefix.
// For example, the prefix "Re" would match instructors "Reed"
// and "Reynolds".
//
// If none are found, then the returned vector is empty.  If
// one or more courses are found, copies of the course objects
// are returned in a vector, with the courses appearing in
// ascending order by course number.  If two courses have the
// same course number, they are given in ascending order by
// section number.  Note that courses are NOT sorted by instructor
// name.
//
vector<Course> FindCourses(const Dept& dept, string instructorPrefix)
{
	vector<Course> courses;

	for(Course C: dept.Courses) {
		auto res = mismatch(instructorPrefix.begin(), instructorPrefix.end(), C.Instructor.begin());
		if (res.first == instructorPrefix.end()) {
			cout << "Prefix matched" << endl;
			Course newCourse = C;
			courses.push_back(newCourse);
		}
	}

  	sort(courses.begin(), courses.end(), [](Course c1, Course c2){
  	// primary sort by course number, ascending:
  	if (c1.Number < c2.Number)
  		return true;
  	else if (c1.Number > c2.Number)
  		return false;
  	else // equal, secondary sort by section number:
  		if (c1.Section < c2.Section)
  			return true;
  		else
  			return false;
  	});

  	return courses;
}


//
// FindCourses(college, courseNumber)
//
// Searches for all courses in the college for those that match
// the given course number.  If none are found, then the returned
// vector is empty.  If one or more courses are found, copies of
// the course objects are returned in a vector, with the courses
// appearing in ascending order by department, then course number,
// and then section number.
//
vector<Course> FindCourses(const College& college, int courseNumber)
{
	vector<Course> courses;

	for(Dept D: college.Depts) {
		for(Course C: D.Courses) {
			if(C.Number == courseNumber) {
				Course newCourse = C;
				courses.push_back(newCourse);
			}
		}
	}

	sort(courses.begin(), courses.end(), [](Course c1, Course c2){
	// primary sort by department, ascending:
	if (c1.Dept < c2.Dept)
		return true;
	else if (c1.Dept > c2.Dept)
		return false;
	else // equal, secondary sort by course number:
		if (c1.Number < c2.Number)
			return true;
		else if (c1.Number > c2.Number)
			return false;
		else // equal, sort by section number:
			if (c1.Section < c2.Section)
				return true;
			else
				return false;
	});

	return courses;
}


//
// FindCourses(college, instructorPrefix)
//
// Searches all the courses in the college for those whose
// instructor name starts with the given instructor prefix.
// For example, the prefix "Re" would match instructors "Reed"
// and "Reynolds".  If none are found, then the returned
// vector is empty.  If one or more courses are found, copies of
// the course objects are returned in a vector, with the courses
// appearing in ascending order by instructor, then course number,
// and then section number.
//
vector<Course> FindCourses(const College& college, string instructorPrefix)
{
	vector<Course> courses;

	for(Dept D: college.Depts) {
		for(Course C: D.Courses) {
			auto res = mismatch(instructorPrefix.begin(), instructorPrefix.end(), C.Instructor.begin());
			if (res.first == instructorPrefix.end()) {
				cout << "Prefix matched" << endl;
				Course newCourse = C;
				courses.push_back(newCourse);
			}
		}
	}

	sort(courses.begin(), courses.end(), [](Course c1, Course c2){
	// primary sort by instructor, ascending:
	if (c1.Instructor < c2.Instructor)
		return true;
	else if (c1.Instructor > c2.Instructor)
		return false;
	else // equal, secondary sort by course number:
		if (c1.Number < c2.Number)
			return true;
		else if (c1.Number > c2.Number)
			return false;
		else // equal, sort by section number:
			if (c1.Section < c2.Section)
				return true;
			else
				return false;
	});

	return courses;
}