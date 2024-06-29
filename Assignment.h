#pragma once
#include <iostream>
#include <string>
#include <deque>
#include <map>
#include "Student.h"
#include "Course.h"
#include "Submission.h"
struct Doctor;


extern std::deque <std::shared_ptr<Student> > STUDENTS;




struct Assignment {
	std::string name;
	double fullMark;
	std::string deadLine;

	std::shared_ptr < Course >crs;
	std::shared_ptr < Doctor > dr;
	std::deque <std::string> desc;

	std::deque < double > marks;
	std::map <std::shared_ptr <Student>, std::shared_ptr<Submission> > subs;

	Assignment(std::string n, double fM, std::string dL, std::deque <std::string>ds) {

		name = n; fullMark = fM, deadLine = dL; desc = ds;


	}

	Assignment(std::string n, double fM, std::string dL, std::shared_ptr < Course >  c, std::shared_ptr < Doctor >d, std::deque <std::string>ds) {

		name = n; fullMark = fM, deadLine = dL; crs = c; dr = d; desc = ds;

	}

	~Assignment() {	};


	bool operator < (const Assignment& b) const
	{
		return deadLine < b.deadLine;
	}
};

