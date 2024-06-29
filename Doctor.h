#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Course.h"
#include <algorithm>

struct Student;

// extern deque <shared_ptr<Course> > COURSES;

struct Doctor {
	// Members
	//=======================================================================================
	std::string name;
	std::string username;
	std::deque <std::shared_ptr<Course> > courses; // a vector to store the courses the doctor is teaching
	//=======================================================================================

	// Constructor and deconstructor
	//=======================================================================================

	Doctor(std::string n, std::string u);
	~Doctor() { }
	//=======================================================================================

	//Methods
	//=======================================================================================
	//---------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------
	void removeCourse(std::string name) {
		auto pred = [name](std::shared_ptr <Course> course) {
			return course->name == name;
		};
		auto it = std::find_if(courses.begin(), courses.end(), pred);
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

