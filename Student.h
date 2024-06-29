#pragma once
#include <vector>
#include <string>
using namespace std;
#include "Course.h"
#include "Assignment.h"



extern deque <shared_ptr<Course> > COURSES;

struct Student {
	// Members
	//=======================================================================================
	string name;
	string ID;
	string username;
	int semester;
	deque < shared_ptr<Course> > courses;             // a vector to store the courses a student is taking
	deque <shared_ptr <Assignment> > submitted;

	//=======================================================================================

	// Constructor and deconstructor
	//=======================================================================================

	Student(string n, string I, string u, int sem) {

		name = n; ID = I; username = u; semester = sem;

	
	}

	~Student() {};
	//=======================================================================================

	//Methods
	//=======================================================================================

	void dropCourse(string name) {
		auto pred = [name](shared_ptr<Course> course) {
			return course->name == name;
		};
		auto it = find_if(courses.begin(), courses.end(), pred);
		courses.erase(it);
	}
	//---------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------


	//Overloaded operators
	//=======================================================================================
	bool operator == (const Student& b) const {
		return username == b.username;
	}                                                //to recognise same student by username

	bool operator()(shared_ptr<Student>& a, shared_ptr <Student>& b) const {
		if (a->semester == b->semester) return a->name < b->name;
		else return a->semester < b->semester;
	}

};

static bool operator < (const Student& a, const Student& b) {
	if (a.semester == b.semester) return a.name < b.name;
	else return a.semester < b.semester;
}

