#pragma once

#include "Database.hpp"
#include "Student.h"
#include "Doctor.h"

//============================= FUNCTIONS PROTOTYPES =========================================
//Flags for the login proccess

//mp
//Main Menu function
void mainMenu();
//Login function
void login(std::vector<std::string>& s = students, std::vector<std::string>& d = doctors, int trials = 2, std::string message = "");
//Signup function
void signUp();
//Function to take unbuffered input
void unbufInput(bool condition = true, char choice = 'b');
//Time delay function
void delay(int s);
//Function to display line of dashes
void L(int t = 0);
//sp
//Function to display Student's menu
void studentMenu(std::shared_ptr<Student>& s);
//Function to display the list of courses of a student
void coursesList(std::shared_ptr<Student>& S);
//Function to register a course for the student (tmep_
void registerCourse(std::shared_ptr<Student>& s);

//Function to display info for a course for student
void stViewCourse(std::shared_ptr<Course>& c, std::shared_ptr<Student>& S);
//Function to auto add courses by semester
void autoAdd(std::shared_ptr<Course>& C);
//dp
//Function to display Doctor's menu
void courseGrades(std::shared_ptr<Course>& c);
void doctorMenu(std::shared_ptr<Doctor>& d);
//Function to dispaly the list of courses of a doctor
void coursesList(std::shared_ptr<Doctor>& D);
//Function to create a course by doctor
void addToDr(std::shared_ptr<Doctor>& d);
void notAutoAdd(std::shared_ptr<Course>& C);
void edit_pre(std::shared_ptr<Course>& cc);


void create(std::shared_ptr<Doctor>& d);

void addAssignmentToCourse(std::shared_ptr<Doctor>& d, std::shared_ptr<Course>& c);
void listAss(std::shared_ptr<Doctor>& d, std::shared_ptr<Course>& c);
void listAss(std::shared_ptr<Student>& s, std::shared_ptr<Course>& c);
//Function to display info for a course for doctor
void drViewCourse(std::shared_ptr<Course>& c, std::shared_ptr<Doctor>& D);
void bye();
void makeSubmission(std::shared_ptr<Student>& s, std::shared_ptr<Assignment>& as);
void viewAss(std::shared_ptr<Assignment>& as, std::shared_ptr<Doctor>& d);
void viewComments(std::shared_ptr <Submission>& sub);
void viewSub(std::shared_ptr <std::pair<std::shared_ptr <Student> const, std::shared_ptr<Submission> > > temp, std::shared_ptr<Assignment>& as, std::shared_ptr<Doctor>& d);
void subList(std::shared_ptr<Assignment>& as, std::shared_ptr<Doctor>& d);

void viewSub(std::shared_ptr<Submission>& sub, std::shared_ptr<Student>& s, std::shared_ptr<Course>& c);

void viewAss(std::shared_ptr<Assignment>& as, std::shared_ptr<Doctor>& d);

void viewAss(std::shared_ptr<Assignment>& as, std::shared_ptr <Student>& s, std::shared_ptr<Course>& c);

void loadC(std::shared_ptr<Student>& x);
void gradeList(std::shared_ptr<Student>& s);

char _getch();

char _getch();

