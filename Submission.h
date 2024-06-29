#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <deque>
// using namespace std;
#include "Assignment.h"

struct Submission {
	std::string name;
	std::shared_ptr <Assignment> asi;
	std::shared_ptr <Student> std;
	std::string graded;
	double mark;
	std::deque <std::string > ans;
	std::deque <std::deque <std::string > > comments;

	Submission(std::string n, std::shared_ptr<Assignment> a, std::deque <std::string > ba) {
		name = n; asi = a;   ans = ba;
		graded = "Not graded";
	}

	~Submission() {}

	void markSubmission(double m) {
		mark = m;
	}

	void addComment(std::deque < std::string >& c) {
		comments.push_back(c);
	}
};


