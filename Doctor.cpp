#include "Doctor.h"
#include "Database.hpp"
    
    
    Doctor::Doctor(string n, string u) 
    {
		name = n; 
        username = u;
		for (int i = 0; i < COURSES.size(); i++) 
        {
			if (COURSES[i]->Dr == name) courses.emplace_back(COURSES[i]);
		}

	}
