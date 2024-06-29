
#include "functions.h"
#include <chrono>
#include <thread>
//============================= FUNCTIONS DEFINITION ===========================================


int wait = 5;
int status = -1;
int soz = 0;




// mf
void clearScreen() 
{
	system("clear");	
}

char _getch()
{
    char ch = 'a';
	std::cin >> ch;
    return ch;
}

void mainMenu() {
	char choice;

	clearScreen();

	std::cout << "Main Screen" << std::endl; L();
	std::cout << "1- Login" << std::endl;
	delay(400);
	std::cout << "2- Signup" << std::endl;
	delay(400);
	std::cout << "3- Exit\n";
	delay(400);
	L();

	std::cout << "Your choice: ";
	std::cin >> choice;
	std::cin.ignore(1000, '\n');

	//Input validation

	if (choice == '3') {
		clearScreen();
		std::cout << "Thanks for yousing our program" << std::endl;
		delay(1500);

		return;
	}
	switch (choice) {
	case '1': {
		if (wait < 4) {
			std::cout << "You have attempted too many logins, please wait for a while" << std::endl;

			wait++;
			delay(1000);
			mainMenu();
		}
		login();
		break;
	}

	case '2':  signUp(); break;
	}
}

void login(std::vector<std::string>& s, std::vector<std::string>& d, int trials, std::string message) {

	clearScreen();
	std::cout << "Login" << std::endl; L();

	std::cout << message;

	unbufInput((status == 3 || status == 1 || status == -2));


	if (trials == 0) {
		std::cout << "Too many login attempts, try again later!";

		wait = 0;
		delay(1000);
		mainMenu();

		return;
	}

	std::string username;
	std::string password;
	std::cout << "username: ";

	getline(std::cin, username);
	std::cout << "\npassword: ";

	getline(std::cin, password);

	// this variable will be 1 if user not found in students
	// if it's also not found in doctors, it will be 3
	// so only if it equals 2, we say user not found
	// if user found in students with correct password then status =0;
	// if user found in students with incorrect password, then status =-2
	// if user found in doctors not students, and correct password = 2
	// if user found in doctors with incorrect passwords , =1;

	std::vector<std::string>::const_iterator st = find(s.begin(), s.end(), username);
	if (st != s.end()) {
		if (*++st == password) status = 0;
		else status = -2;
	}
	else status = 1;


	if (status == 1) {
		std::vector<std::string>::const_iterator dr = find(d.begin(), d.end(), username);
		if (dr != d.end()) {
			if (*++dr == password) status = 2;
			else status = 1;
		}
		else status = 3;
	}


	switch (status) {
	case -2:
	case 1: login(s, d, trials - 1, "Wrong Password, press any key to try again or presss b to go back: "); break;
	case 2: {
		L();
		std::string welcome = "Welcome Dr. ";

		for (auto& x : DOCTORS) {
			if (username == x->username) {
				for (auto v : welcome) {
					std::cout << v; delay(100);
				}
				for (int b = 0; b < x->name.size(); b++) {
					std::cout << x->name[b];
					delay(0);
				}
				std::cout << "!";
				delay(2000);
				doctorMenu(x);
				break;
			}
		}
		break;
	}
	case 0: {
		L();
		std::string welcome = "Welcome ";
		for (auto& x : STUDENTS) {
			if (username == x->username) {
				for (auto v : welcome) {
					std::cout << v; delay(100);
				}
				for (int b = 0; b < x->name.size(); b++) {
					std::cout << x->name[b];
					delay(100);
				}
				std::cout << "!";
				delay(2000);
				studentMenu(x);
			}
		}
		break;
	}
	case 3: login(s, d, trials - 1, "User not found, press any key to try again or presss b to go back: \n");  break;
	}
}

void signUp() {
	clearScreen();

	std::cout << "Signup" << std::endl; L();


	std::cout << "Choose the account type or press b to go back: " << std::endl << std::endl;
	std::cout << std::left << std::setw(35) << "1- Doctor Account"
		<< "2- Student Account" << std::endl;
	L();
	std::cout << "Your choice: ";
	char stroke = _getch();
	if (stroke == 'b' or stroke == 'B') mainMenu();

	if (stroke == '1') {
		clearScreen();
		std::cout << "Sign up for a doctor account" << std::endl;
		L();
		std::string name, username, password;
		std::cout << "Name: "; getline(std::cin, name);
		std::cout << "\nUsername: "; getline(std::cin, username);
		std::cout << "\nPassword: "; getline(std::cin, password);

		auto us = find(doctors.begin(), doctors.end(), username);
		while (us != doctors.end()) {
			L();
			std::cout << "An account with this username already exists!" << std::endl
				<< "Press 'l' to login instead or press 'b' to go back: ";
			char stroke2 = _getch();
			if (stroke2 == 'b' or stroke2 == 'B') mainMenu();
			else if (stroke2 == 'l' or stroke2 == 'L') login();
		}

		doctors.push_back(username);
		doctors.push_back(password);

		DOCTORS.emplace_back(std::make_shared<Doctor> (Doctor(name, username)));
		L();
		std::cout << "Account successfully created!" << std::endl;
		delay(2000);
		mainMenu();

	}

	else if (stroke == '2') {
		clearScreen();
		std::cout << "Sign up for a student account" << std::endl;
		L();

		std::string name, ID, username, password;
		int semester;

		std::cout << "Name: "; getline(std::cin, name);
		std::cout << "Student ID: "; getline(std::cin, ID);
		std::cout << "\nOngoing semester: "; std::cin >> semester; std::cin.ignore();

		std::cout << "\nUsername: "; getline(std::cin, username);
		std::cout << "\nPassword: "; getline(std::cin, password);

		auto us = find(students.begin(), students.end(), username);
		while (us != students.end() and (std::abs(us - students.begin()) % 2 == 0)) {
			L();
			std::cout << "An account with this username already exists!" << std::endl
				<< "Press 'l' to login instead or press 'b' to go back: ";
			char stroke2 = _getch();
			if (stroke2 == 'b' or stroke2 == 'B') mainMenu();
			else if (stroke2 == 'l' or stroke2 == 'L') login();
		}

		auto id = find(studentsID.begin(), studentsID.end(), ID);
		while (id != studentsID.end()) {
			L();
			std::cout << "An account with this ID already exists!" << std::endl
				<< "Press 'l' to login instead or press 'b' to go back: ";
			char stroke2 = _getch();
			if (stroke2 == 'b' or stroke2 == 'B') mainMenu();
			else if (stroke2 == 'l' or stroke2 == 'L') login();
		}

		students.push_back(username);
		students.push_back(password);
		studentsID.push_back(ID);

		STUDENTS.emplace_back(std::make_shared<Student> (Student(name, ID, username, semester)));
		loadC(STUDENTS.back());
		L();
		std::cout << "Account successfully created!" << std::endl;
		delay(2000);
		mainMenu();

	}
}

void delay(int s) {
	//sleep_until(system_clock::now() + seconds(s));
	std::this_thread::sleep_for(std::chrono::milliseconds(s));
}

void unbufInput(bool condition, char choice) {
	char stroke;
	if (condition) {
		stroke = _getch();
		if (stroke == choice) mainMenu();
	}
}

void L(int t) {



	for (int i = 110; i != 0; i--) {
		std::cout << "-"; delay(t);
	}
	std::cout << std::endl;



}

//sf

void studentMenu(std::shared_ptr<Student>&s) {
	clearScreen();

	std::cout << "Press a key corresponding to your choice: " << std::endl;
	L();

	std::cout << "1- Courses list" << std::endl;
	delay(400);
	std::cout << "2- Register a course" << std::endl;
	delay(400);
	std::cout << "3- Grade list" << std::endl;
	delay(400);
	std::cout << "4- Log out" << std::endl;
	delay(400);

	L();
	std::cout << "Your choice: ";

	char stroke = _getch();
	switch (stroke) {
	case '1': coursesList(s);				break;
	case '2': registerCourse(s);		    break;
	case '3':  gradeList(s); studentMenu(s);break;
	case '4': std::cin.ignore(); mainMenu();	    break;
	}
}

void coursesList(std::shared_ptr<Student>&S) {
	clearScreen();
	char stroke;




	std::cout << "List of courses: " << std::endl; L(0);


	std::cout << std::left
		<< std::setw(35)
		<< "Course Name"
		<< std::setw(15) << "Course Code"
		<< std::setw(25) << "Course Doctor"
		<< std::setw(10) << "Number of Assignments";
	std::cout << std::endl << std::endl;

	int j = 0;


	for (auto& x : S->courses) {
		std::cout << std::left
			<< ++j << "- " << std::setw(32) <<
			x->name << std::setw(15) << x->code << std::setw(25)
			<< x->Dr << "\t\t" << std::setw(10) << x->assignments.size() << std::endl;
	}

	L();
	std::cout << "Select the number of the course you want to view or press 'b' to go back: ";
	stroke = _getch();



	if (stroke == 'b' || stroke == 'B') {

		studentMenu(S);
	}
	else {

		stViewCourse(S->courses[stroke - 49], S);
	}
}

void registerCourse(std::shared_ptr<Student>&s) {

	std::deque <std::shared_ptr <Course> > difference;
	bool flag = true;

	for (auto& x : COURSES) {

		for (auto& y : s->courses) {
			if (x->name != y->name) flag = true;
			else { flag = false; break; }

		}


		if (flag) difference.emplace_back(x);
	}

	clearScreen();

	if (difference.size() == 0) {
		std::cout << "There are no courses for you to register in at the moment." << std::endl;
		delay(3000);
		studentMenu(s);
	}


	std::cout << "Lists of courses you are not registered in: " << std::endl;
	L();
	std::cout << std::left
		<< std::setw(35)
		<< "Course Name"
		<< std::setw(15) << "Course Code"
		<< std::setw(20) << "Course Doctor"
		<< std::setw(20) << "Default Semester"
		<< "Prerequisites";
	std::cout << std::endl << std::endl;
	for (int i = 0; i < difference.size(); i++) {


		std::cout << std::left
			<< i + 1 << "- " << std::setw(32)
			<< difference[i]->name
			<< std::setw(15) << difference[i]->code
			<< std::setw(20) << difference[i]->Dr
			<< std::setw(20) << difference[i]->semester;
		if (difference[i]->pre.size() == 0) std::cout << "No prerequisites." << std::endl;
		else {
			for (auto& x : difference[i]->pre) {
				std::cout << x->name << ", ";
			}
			std::cout << std::endl;
		}
	}

	std::cout << "\nChoose a course or press 'b' to go back: ";

	char choice;
	std::cin >> choice;

	if (choice == 'b' or choice == 'B') { std::cin.ignore(); studentMenu(s); }

	choice = choice - 49;
	std::cin.ignore();

	//=========================================================================================================================
	bool felog2 = true;
	for (auto& x : difference[choice]->pre) {
		bool felog = false;
		for (auto& y : s->courses) {
			if (x->name == y->name) { felog = true; break; }
		}
		if (!felog) { felog2 = false; break; }
	}

	if (felog2) {
		
		difference[choice]->studentCnt.insert((s));
		s->courses.emplace_back(difference[choice]);


		std::cout << "Added!";
		delay(2000);
		studentMenu(s);

	}
	else std::cout << "You do not have all the prerequisites for this course!" << std::endl;
	delay(2000);
	registerCourse(s);


	//=========================================================================================================================




}

void stViewCourse(std::shared_ptr<Course>& c, std::shared_ptr<Student>&S) {

	clearScreen();
	std::cout << "Course Info" << std::endl;
	L();

	c->stSummary();
	L();
	listAss(S, c);

	if (c->assignments.size() != 0) std::cout << "Select an assignment to view or ";
	std::cout << "press 'b' to go back: ";

	char stroke;
	stroke = _getch();

	if (stroke == 'b') coursesList(S);
	else {

		clearScreen();


		viewAss(c->assignments[static_cast <int> (stroke) - 49], S, c);

	}
}

void autoAdd(std::shared_ptr<Course>& C) {
	for (auto& x : STUDENTS) {
		if (x->semester == C->semester) {
			x->courses.emplace_back(C);
			C->studentCnt.insert(x);
		}
	}
}

void notAutoAdd(std::shared_ptr<Course>& C) {
	bool flag = false, flag3 = true;
	for (auto& x : STUDENTS) {
		if (x->semester != C->semester) continue;
		for (auto& y : C->pre) {
			bool flag2 = false;
			for (auto& z : x->courses) {
				if (y->name == z->name) { flag2 = true; break; }
			}
			if (!flag2) { flag3 = false; break; }
		}
		if (flag3) {
			x->courses.emplace_back(C);
			C->studentCnt.insert(x);
		}
	}
}
//df

void doctorMenu(std::shared_ptr<Doctor>& d) {


	clearScreen();
	std::cout << "Press a key corresponding to your choice: " << std::endl;
	L();
	std::cout << "1- Courses list" << std::endl
		<< "2- Create a course" << std::endl
		<< "3- Log out" << std::endl
		<< "Your choice: ";

	char stroke = _getch();
	switch (stroke) {
	case '1': coursesList(d);			break;
	case '2': create(d);				break;
	case '3': mainMenu();				break;
	}
}

void coursesList(std::shared_ptr<Doctor>& D) {

	clearScreen();

	char stroke;

	std::cout << "List of courses: " << std::endl;
	L();

	std::cout << std::left << std::setw(24) << "Course Name" << std::setw(18) << "Course Code"
		<< std::setw(22) << "Number of students" << "Number of assignments" << std::endl << std::endl;

	for (int i = 0; i < D->courses.size(); i++) {
		std::cout << i + 1 << "- " << std::left << std::setw(21) << D->courses.at(i)->name
			<< std::setw(18) << D->courses.at(i)->code << std::setw(25)
			<< D->courses.at(i)->studentCnt.size() << D->courses.at(i)->assignments.size() << std::endl;
	}

	L();
	std::cout << "Select the number of the course you want to view or press 'b' to go back: ";
	stroke = _getch();
	if (stroke == 'b' || stroke == 'B') doctorMenu(D);
	else	drViewCourse(D->courses[(stroke)-49], D);


}




void drViewCourse(std::shared_ptr<Course>& c, std::shared_ptr<Doctor>& D) {

	clearScreen();
	std::cout << c->name << " -> Course Info" << std::endl;
	L();

	c->drSummary();

	L();
	std::cout << "Press a key corresponding to your choice or b to go back: " << std::endl << std::endl
		<< "1- Assignments list \n"
		<< "2- Create a new assignment \n"
		<< "3- View Students grades for this course \n"
		<< std::endl << "Your choice: ";


	char stroke = _getch();

	if (stroke == 'D' or stroke == 'd') {
		//clearScreen();
		std::cout << std::endl;

		clearScreen();
		std::cout << "Please enter the course description for " << c->name << ": \n";
		L();
		c->setDesc();
		drViewCourse(c, D);

	}

	if (stroke == 'b') coursesList(D);
	if (stroke == '1') {
		listAss(D, c);
		drViewCourse(c, D);
	}
	if (stroke == '2') {
		clearScreen();
		addAssignmentToCourse(D, c);
		delay(1000);
		drViewCourse(c, D);
	}
	if (stroke == '3') {
		clearScreen();
		courseGrades(c);
		drViewCourse(c, D);

	}




}

void create(std::shared_ptr<Doctor>& d) {
	clearScreen();
	std::string n, c; int sem;
	int isPre = 0;
	std::cout << "Create a course" << std::endl;
	L();
	std::cout << "Enter details: " << std::endl << std::endl;

	std::cout << "Course name: "; getline(std::cin, n);
	std::cout << "Course code: "; getline(std::cin, c);
	std::cout << "Default semester: "; std::cin >> sem; std::cin.ignore();
	int stat;

	std::cout << "\nPrerequisites?: \n"
		<< std::left << std::setw(35) << "1-No prerequisites"
		<< "2-Add prerequisites\n"
		<< "choice: "; std::cin >> stat; std::cin.ignore();

	COURSES.emplace_back(std::make_shared<Course> (Course(n, c, d->name, sem)));

	if (stat == 1) {

		addToDr(d);
		autoAdd(COURSES.back());
	}

	else if (stat == 2) {
		edit_pre(COURSES.back());
		addToDr(d);
		notAutoAdd(COURSES.back());
	}

	L();
	std::cout << "Course created successfully!" << std::endl;
	delay(2000);
	coursesList(d);

}

void addAssignmentToCourse(std::shared_ptr<Doctor>& d, std::shared_ptr<Course>& c) {

	std::string nama;  double fM; std::string dL;  std::deque <std::string> ds;
	std::cout << "Enter the details for the assignment: " << std::endl << std::endl;

	std::cout << "Assignment name: ";
	getline(std::cin, nama);
	std::cout << "Assignment description: \n";
	std::string temp;
	while (getline(std::cin, temp) and temp != "") {
		ds.push_back(temp);
	}
	std::cout << "Assignment full mark: "; std::cin >> fM; std::cin.ignore();
	std::cout << "Assignment dead line: "; getline(std::cin, dL);
	std::shared_ptr <Assignment> asi = std::make_shared <Assignment>(Assignment(nama, fM, dL, c, d, ds));
	c->assignments.emplace_back(asi);

	std::cout << "Assignment added!" << std::endl;


}

void listAss(std::shared_ptr<Student>&s, std::shared_ptr<Course>& c) {

	std::cout << "List of Assignments" << std::endl;
	L();
	if (c->assignments.size() == 0) std::cout << "This course has no assignments!" << std::endl;
	else {
		std::cout << std::left << std::setw(30)
			<< "Assignment name"
			<< std::setw(25)
			<< "Assignment Deadline"

			<< std::setw(25)
			<< "Assignment fullMark"
			<< "My submissions"

			<< std::endl << std::endl;

		int j = 0;
		for (auto& x : c->assignments) {
			std::cout << std::left << ++j << "- "
				<< std::setw(27) << x->name
				<< std::setw(25) << x->deadLine
				<< std::setw(25) << x->fullMark;
			//if (s.submitted.size() == 0) { std::cout << "No Submissions" << std::endl; continue; }
			auto fo = find(s->submitted.begin(), s->submitted.end(), x);
			if (fo != s->submitted.end()) std::cout << "Submitted"; else std::cout << "No Submissions";
			std::cout << std::endl;
		}

		L();
	}

}

void listAss(std::shared_ptr<Doctor>& d, std::shared_ptr<Course>& c) {
	clearScreen();
	std::cout << "List of Assignments" << std::endl;
	L();
	if (c->assignments.size() == 0) { std::cout << "This course has no assignments!" << std::endl; delay(2000); return; }
	else {
		std::cout << std::left << std::setw(30)
			<< "Assignment name"
			<< std::setw(25)
			<< "Assignment Deadline"

			<< std::setw(25)
			<< "Assignment fullMark"
			<< "Number of submissions"

			<< std::endl << std::endl;

		int j = 0;
		for (auto& x : c->assignments) {
			std::cout << std::left << ++j << "- "
				<< std::setw(27) << x->name
				<< std::setw(25) << x->deadLine

				<< std::setw(25) << x->fullMark
				<< x->subs.size() << std::endl;
		}
	}

	L();

	std::cout << "Select an assignment to view or press 'b' to go back: ";
	char stroke = _getch();
	if (stroke == 'b') return;
	clearScreen();
	viewAss(c->assignments[(int)stroke - 49], d);


	listAss(d, c);


}
void bye() {
	std::cout << "A";
}

void addToDr(std::shared_ptr<Doctor>& d) {

	d->courses.emplace_back(COURSES.back());

}
void edit_pre(std::shared_ptr<Course>& cc) {

	clearScreen();
	std::cout << "Add prerequisites for " << cc->name << std::endl;
	L();

	std::cout << "List of courses you can add as pre requisites: " << std::endl;
	L();

	bool flag = true;

	int cnt = 0;
	std::map <int, std::shared_ptr<Course> > m;

	std::cout << std::left
		<< std::setw(35)
		<< "Course Name"
		<< std::setw(15) << "Course Code"
		<< std::setw(20) << "Default Semester"
		<< "Prerequisites";
	std::cout << std::endl << std::endl;




	for (auto& x : COURSES) {
		bool flag = true;
		if (x->name == cc->name) continue;
		if (x->semester > cc->semester) continue;
		for (auto& y : cc->pre) { if (y->name == x->name) flag = false; }
		for (auto& z : x->pre) { if (cc->name == z->name) flag = false; }
		if (!flag) continue;
		std::cout << std::left << ++cnt << "- "
			<< std::setw(32) << x->name
			<< std::setw(15) << x->code
			<< std::setw(20) << x->semester;
		if (x->pre.size() == 0) std::cout << "No prerequisites." << std::endl;
		else {
			for (auto& g : x->pre) {
				std::cout << g->name << ", ";
			}
			std::cout << std::endl;
		}

		m.emplace(cnt, x);
	}
	static int onlyOnce = 0;				// to take the initial size of the number of prerequisites allowed

	if (!onlyOnce) soz = (int)m.size();

	onlyOnce++;
	L();
	std::cout << "Choose a course to add or press b to go back: ";
	char choice;
	std::cin >> choice;
	std::cin.ignore();
	if (choice == 'b' or choice == 'B') return;
	else cc->pre.emplace_back(m[choice - 48]);
	L();
	std::cout << "Prerequisite added successfully" << std::endl; delay(1500);

	clearScreen();

	std::cout << "list of prerequisites for " << cc->name << std::endl;
	L();

	int cnt2 = 0;
	for (auto& x : cc->pre) {
		std::cout << ++cnt2 << "- " << x->name << std::endl;
	}
	L();
	std::cout << "Press c to add another prerequisite or press b to go back: ";

	std::cin >> choice;

	std::cin.ignore();

	if (choice == 'b' or choice == 'B') return;
	else if (choice == 'c' or choice == 'C') {

		if (cc->pre.size() == soz) { L(); std::cout << "No more courses to add\n"; delay(1600); return; }

		edit_pre(cc);
	}

}
void viewSub(std::shared_ptr <std::pair<std::shared_ptr <Student> const, std::shared_ptr<Submission> > > temp, std::shared_ptr<Assignment>& as, std::shared_ptr<Doctor>& d) {
	clearScreen();
	std::cout << "View submission" << std::endl;
	L();
	std::cout << "Submission name: " << temp->second->name << std::endl
		<< "Student name: " << temp->first->name << std::endl
		<< "Student answer: " << std::endl;
	for (auto& x : temp->second->ans) {
		std::cout << x << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Submission status: " << temp->second->graded << std::endl;
	std::cout << "Marks: ";
	(temp->second->graded == "Not graded") ? std::cout << "N/A" << std::endl : std::cout << temp->second->mark << std::endl;

	L();

	std::cout << "Comments:" << std::endl;
	L();
	viewComments(temp->second);

	std::cout << "Press b to go back, c to add a coment, or g to grade assignment";
	char stroke = _getch();
	if (stroke == 'b' or stroke == 'B') viewAss(as, d);
	else if (stroke == 'g' or stroke == 'G') {
		std::cout << std::endl;
		L();
		std::cout << "Enter the grade: ";
		double mark;
		std::cin >> mark;
		temp->second->graded = "Graded";
		temp->second->mark = mark;
		std::cin.ignore();
		std::cout << "Marks for the submission has been updated" << std::endl;
		delay(1500);
		viewSub(temp, as, d);
	}
	else if (stroke == 'c' or stroke == 'C') {
		std::cout << "\nnew comment: ";
		std::string tomp = "Dr." + d->name + ": \n";
		std::deque <std::string> t;
		t.emplace_back(tomp);

		while (getline(std::cin, tomp) and tomp != "") {
			t.emplace_back(tomp);
		}
		if (t.size() > 1) {
			temp->second->addComment(t);
			std::cout << "Comment added" << std::endl;
		}

		else std::cout << "No comment added" << std::endl;
		delay(1500);
		viewSub(temp, as, d);
	}
}

void subList(std::shared_ptr<Assignment>& as, std::shared_ptr<Doctor>& d) {
	std::cout << "List of submissions" << std::endl;
	L();
	if (as->subs.size() == 0) {
		std::cout << "No submissions so far!\nPress 'b' to go back" << std::endl;
		char stroke = _getch();
		if (stroke == 'b' or stroke == 'B') return;
	}
	std::cout << std::left
		<< std::setw(30) << "Submission name"
		<< std::setw(30) << "Student name"
		<< std::setw(20) << "Status"
		<< "Mark" << std::endl << std::endl;
	int j = 0;


	std::deque < std::shared_ptr <std::pair<std::shared_ptr <Student> const, std::shared_ptr<Submission> > > > temp;

	for (auto& x : as->subs) {
		std::cout << std::left << ++j << "- "
			<< std::setw(27) << x.second->name
			<< std::setw(30) << x.first->name
			<< std::setw(20) << x.second->graded;
		(x.second->graded == "Not graded") ? std::cout << "N/A" : std::cout << x.second->mark;
		std::cout << std::endl;
		temp.emplace_back(std::make_shared < std::pair < std::shared_ptr <Student> const, std::shared_ptr<Submission > > >(x));

	}
	std::cout << std::endl;
	std::cout << "Choose a submission to view or press 'b' to go back: ";
	char stroke = _getch();
	if (stroke == 'b') return;
	else viewSub(temp[(int)stroke - 49], as, d);

}
void viewAss(std::shared_ptr<Assignment>& as, std::shared_ptr<Doctor>& d) {
	clearScreen();
	std::cout << "View Assignment" << std::endl;
	L();
	std::cout << "Assignment name: " << as->name << std::endl;
	std::cout << "Assignment Description: \n";
	for (auto& x : as->desc) {
		std::cout << x << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Assignment deadline: " << as->deadLine << std::endl;
	std::cout << "Assignment full mark: " << as->fullMark << std::endl;
	std::cout << std::endl;

	subList(as, d);

}
void makeSubmission(std::shared_ptr<Student>&s, std::shared_ptr<Assignment>& as) {

	std::string n;   std::deque <std::string > ans;

	std::cout << "Submission name: "; getline(std::cin, n);
	std::cout << "Your answer: " << std::endl;
	std::string temp = "-";
	while (getline(std::cin, temp) and temp != "") {
		ans.push_back(temp);
	}
	s->submitted.emplace_back(as);
	
	as->subs.emplace(s, std::make_shared<Submission>(Submission(n, as, ans)));

}

void viewAss(std::shared_ptr<Assignment>& as, std::shared_ptr <Student>& s, std::shared_ptr<Course>& c) {

	std::cout << "Assignment name: " << as->name << std::endl;
	std::cout << "Assignment Description: \n";
	for (auto& x : as->desc) {
		std::cout << x << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Assignment deadline: " << as->deadLine << std::endl;
	std::cout << "Assignment full mark: " << as->fullMark << std::endl;
	//std::cout << "Assignment Average: " << /*AVg*/ std::endl;
	std::cout << std::endl;
	L();
	std::cout << "Your Submission: " << std::endl << std::endl;



	auto it = find(s->submitted.begin(), s->submitted.end(), as);
	if (it == s->submitted.end()) {

		std::cout << "No submission made, Press 's' to make a submission or press 'b' to go back" << std::endl;
		char stroke;
		stroke = _getch();

		if (stroke == 'b') stViewCourse(c, s);
		else if (stroke == 's' or stroke == 'S') {
			clearScreen();

			makeSubmission(s, as);
			L();
			std::cout << "Thanks for making a submission!";
			delay(1000);
			std::cout << std::endl;
			stViewCourse(c, s);
		}

	}
	else {

		std::cout << std::left
			<< std::setw(30) << "Submission name"
			<< std::setw(25) << "Submition status"
			<< "Marks" << std::endl
			<< std::setw(30) << as->subs[s]->name
			<< std::setw(25) << as->subs[s]->graded;
		(as->subs[s]->graded == "Not graded") ? std::cout << "N/A" : std::cout << as->subs[s]->mark;
		std::cout << std::endl;
		L();

		std::cout << "Press s to view submission or b to go back: ";
		char stroke;
		stroke = _getch();

		if (stroke == 'b') stViewCourse(c, s);
		else viewSub(as->subs[s], s, c);

	}


}

void viewComments(std::shared_ptr <Submission>& sub) {
	int cnt = 1;
	for (auto& x : sub->comments) {

		for (auto& y : x) {
			for (int i = 0; i < cnt; i++) std::cout << '\t';
			std::cout << y << std::endl;
		}
		L();
		cnt++;
	}

}
void viewSub(std::shared_ptr <Submission>& sub, std::shared_ptr<Student>&s, std::shared_ptr<Course>& c) {
	clearScreen();
	std::cout << "Submission for " << sub->asi->name;
	L();
	std::cout << "Submission name: " << sub->name << std::endl
		<< "Answer: " << std::endl;
	for (auto& x : sub->ans) {
		std::cout << x << std::endl;
	}
	std::cout << std::endl << "Grade: ";
	if (sub->graded == "Not graded") std::cout << "N/A" << std::endl;
	else std::cout << sub->mark << std::endl;
	L();
	std::cout << "Comments: " << std::endl;
	L();
	viewComments(sub);
	std::cout << std::endl;
	L();
	std::cout << "Press 'b' to go back, or press 'c' to post a comment";
	char stroke = _getch();
	if (stroke == 'b' or stroke == 'B') stViewCourse(c, s);
	else if (stroke == 'c' or stroke == 'C') {
		std::cout << "\nnew comment: ";
		std::string temp = s->name + ": \n";
		std::deque <std::string> t;
		t.emplace_back(temp);

		while (getline(std::cin, temp) and temp != "") {
			t.emplace_back(temp);
		}
		if (t.size() > 1) {
			sub->addComment(t);
			std::cout << "Comment added" << std::endl;

		}


		else std::cout << "No comment added" << std::endl;
		delay(1500);
		viewSub(sub, s, c);
	}
}

void courseGrades(std::shared_ptr<Course>& c) {

	if (c->assignments.size() == 0) {
		std::cout << "This course does not have any assignments yet";
		delay(2000);
		return;
	}

	if (c->studentCnt.size() == 0) {
		std::cout << "No students are enrolled in this course";
		delay(2000);
		return;

	}
	std::cout << std::left << std::setw(25) << "Student";
	for (auto& x : c->assignments) {
		std::cout << std::setw(25) << x->name;
	}
	std::cout << std::endl;
	L();


	for (auto& x : c->studentCnt) {

		std::cout << std::setw(25) << x->name;

		for (auto& y : c->assignments) {
			if (y->subs.find(x) == y->subs.end()) {
				std::cout << std::left << std::setw(22) << "Not Submitted";
				continue;
			}
			if (y->subs[x]->graded == "Not graded") std::cout << std::left << std::setw(23) << "Not Graded";
			else std::cout << y->subs[x]->mark << "/" << std::setw(23) << y->fullMark;
		}
	
		std::cout << std::endl;
	}
	std::cout << std::endl;
	L();
	std::cout << "press b to go back";
	char stroke = _getch();
	if (stroke == 'b' or stroke == 'B') return;

}

void gradeList(std::shared_ptr<Student>&s) {
	clearScreen();
	std::cout << "Grade List" << std::endl;
	L();
	double mark;

	std::cout << std::setw(40) << "Course" << "Marks" << std::endl; L();

	for (auto& x : s->courses) {
		mark = 0;
		std::cout << std::left << std::setw(40) << x->name;
		for (auto& y : x->assignments) {
			if (y->subs.find(s) == y->subs.end()) continue;
			if (y->subs[s]->graded == "Not graded") continue;
			mark += y->subs[s]->mark;
			
		}
		
		std::cout << mark << "%";
		std::cout << std::endl;
	}

	L();

	std::cout << "Press b to go back: ";
	char stroke = _getch();
	if (stroke == 'b' or 'B') return;

}


void loadC(std::shared_ptr<Student>&x) {
	for (int i = 0; i < COURSES.size(); i++) {
		if (COURSES[i]->semester == x->semester) {

			x->courses.emplace_back(COURSES[i]);
			
			COURSES[i]->studentCnt.insert(x);

		}
	}
}