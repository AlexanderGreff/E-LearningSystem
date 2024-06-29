#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <deque>
using namespace std;
#include "Assignment.h"

struct Submission {
	string name;
	shared_ptr <Assignment> asi;
	shared_ptr <Student> std;
	string graded;
	double mark;
	deque <string > ans;
	deque <deque <string > > comments;


	Submission(string n, shared_ptr<Assignment> a, deque <string > ba) {
		name = n; asi = a;   ans = ba;
		graded = "Not graded";
	}

	~Submission() {}

	void markSubmission(double m) {
		mark = m;
	}

	void addComment(deque < string >& c) {
		comments.push_back(c);
	}
};




