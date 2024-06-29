#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <queue>
#include <stack>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <thread>
// #include <conio.h>
#include <map>
#include <cstdlib>
#include <assert.h>
using namespace std;
using namespace this_thread;
using namespace std::chrono;

#include "functions.h"
#include "Database.hpp"

int foo(int i)
{
	static int a = 20;
	a += i;
	return a;
}
//============================= MAIN FUNCTION ==================================================

int main() {
	std::cout << foo(10) << std::endl;
	std::cout << foo(20) << std::endl;
	return 0;

	//Loading up some example data for assignments for an example course

	COURSES[5]->assignments = {
		make_shared<Assignment>(Assignment("Test1", 10, "20/5/2020" ,  {"This is a cool course" , "Please study "})),
		make_shared<Assignment>(Assignment("Test2", 20, "2/5/2020" ,  {"Thie" , "Pleasudy "})),
		make_shared<Assignment>(Assignment("Test3", 30, "20/5/0" ,  {"Taaaa " , "aaaady "}))

	};
	
	// Loading up courses for all students
	for (auto& x : STUDENTS) {
		loadC(x);
	}

	mainMenu();

	system("sleep 1");

}

