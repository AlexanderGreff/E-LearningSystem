#pragma once
#include <vector>
#include <string>
#include "Course.h"
#include "Assignment.h"



extern std::deque <std::shared_ptr<Course> > COURSES;

struct Student {
	// Members
	//=======================================================================================
	std::string name;
	std::string ID;
	std::string username;
	int semester;
	std::deque < std::shared_ptr<Course> > courses;             // a vector to store the courses a student is taking
	std::deque <std::shared_ptr <Assignment> > submitted;

	//=======================================================================================

	// Constructor and deconstructor
	//=======================================================================================

	Student(std::string n, std::string I, std::string u, int sem) {

		name = n; ID = I; username = u; semester = sem;

	
	}

	~Student() {};
	//=======================================================================================

	//Methods
	//=======================================================================================

	void dropCourse(std::string name) {
		auto pred = [name](std::shared_ptr<Course> course) {
			return course->name == name;
		};
		auto it = std::ranges::find_if(courses.begin(), courses.end(), pred);
		courses.erase(it);
	}
	//---------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------


	//Overloaded operators
	//=======================================================================================
	bool operator == (const Student& b) const {
		return username == b.username;
	}                                                //to recognise same student by username

	bool operator()(std::shared_ptr<Student>& a, std::shared_ptr <Student>& b) const {
		if (a->semester == b->semester) return a->name < b->name;
		else return a->semester < b->semester;
	}

};

static bool operator < (const Student& a, const Student& b) {
	if (a.semester == b.semester) return a.name < b.name;
	else return a.semester < b.semester;
}

