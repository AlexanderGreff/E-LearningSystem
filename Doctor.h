#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Course.h"
#include <algorithm>
using namespace std;

struct Student;


// extern deque <shared_ptr<Course> > COURSES;

struct Doctor {
	// Members
	//=======================================================================================
	string name;
	string username;
	deque <shared_ptr<Course> > courses; // a vector to store the courses the doctor is teaching
	//=======================================================================================

	// Constructor and deconstructor
	//=======================================================================================

	Doctor(string n, string u);
	~Doctor() { }
	//=======================================================================================

	//Methods
	//=======================================================================================
	//---------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------
	void removeCourse(string name) {
		auto pred = [name](shared_ptr <Course> course) {
			return course->name == name;
		};
		auto it = find_if(courses.begin(), courses.end(), pred);
		courses.erase(it);
	}
	//---------------------------------------------------------------------------------------


	//Overloaded operators
	//=======================================================================================
	bool operator == (const Doctor& b)  const {
		return username == b.username;
	}                                                  //to recognise same doctor by username

	bool operator < (const Doctor& b) const {
		if (name != name) return name < b.name;
		else return username < b.username;
	}
};
