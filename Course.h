#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <deque>
#include <set>

struct Student;
struct Assignment;

struct Course {
	//Members
	//===========================================================================================
	std::string name;
	std::string code;
	std::string Dr;
	int semester;                    // to allow automatic addition of students in this semester
	int status;
	std::deque <std::shared_ptr <Assignment> > assignments;
	std::vector< std::string > desc;
	bool described = false;
	std::deque <std::shared_ptr<Course> > pre;
	std::set < std::shared_ptr <Student> > studentCnt;
	
	Course(std::string n, std::string c, std::string D, int sem) {
		name = n; code = c; Dr = D; semester = sem;

	}
	Course(std::string n, std::string c, std::string D, int sem, std::deque <std::shared_ptr<Course> >& temp) {
		name = n; code = c; Dr = D; semester = sem; pre = temp;

	}



	~Course() {}

	//Methods
	//===========================================================================================

	//-------------------------------------------------------------------------------------------


	void drSummary() {

		std::cout << "Course Description: ";
		if (described) {
			std::cout << std::endl;

			for (auto& s : desc) {
				std::cout << s << std::endl;
			}
			std::cout << std::endl;
		}
		else std::cout << "\nNo course Description, press 'd' to add a new one" << std::endl << std::endl;

		std::cout << "Course Name: " << name << std::endl
			<< "Course Code: " << code << std::endl
			<< "Number of students: " << studentCnt.size() << std::endl
			<< "Number of assignments: " << assignments.size() << std::endl;
	}

	void stSummary() {
		std::cout << "Course Description: ";
		if (described) {
			std::cout << std::endl;
			for (auto& s : desc) {
				std::cout << s << std::endl;
			}
		}
		else std::cout << "\nNo course Description" << std::endl;
		std::cout << std::endl;
		std::cout << "Course Name: " << name << std::endl
			<< "Course Code: " << code << std::endl
			<< "Dr: " << Dr << std::endl;

	}

	void setDesc() {
		std::string temp;
		std::cout << "Press  enter twice to go back" << std::endl;


		while (std::getline(std::cin, temp) and temp != "") {
			desc.push_back(temp);
		}
		described = true;
	}





	//-------------------------------------------------------------------------------------------
	//void removeAssignment(string name) {
	//	auto pred = [name](const Assignment& assignment) {
	//		return assignment.name == name;
	//	};
	//	auto it = std::find_if(assignments.begin(), assignments.end(), pred);
	//	assignments.erase(it);
	//}

	//Overloaded operators
	//===========================================================================================
	bool operator == (std::shared_ptr <Course>  b) {
		return code == b->code;
	}                                                      // to recognise same course by code

};



static bool operator< (const Course& a, const Course& b)
{
	if (a.semester == b.semester) return a.name < b.name;
	else return a.semester < b.semester;
}


