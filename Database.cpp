#include "Database.hpp"

DataBase::DataBase()
: 
courses_(
	{
		make_shared<Course>(Course("Programming Technique 2", "SECOP1234", "Nor Bahia", 2)),
		make_shared<Course>(Course("Programming Technique 1", "SECR1013", "lizawati bint Yusof", 1)),
		make_shared<Course>(Course("Digital Logic", "SECF1050", "Zuriahati", 1)),
		make_shared<Course>(Course("Discrete Structure", "SECI1010", "Nor Haizan", 1)),
		make_shared<Course>(Course("Computational Mathematics", "SEC2019", "Nor Haizan", 2)),
		make_shared<Course>(Course("Mobile Apps", "SEC2019", "Mohamed Alganzory", 1))
	}
		), 

students_(
	{
			make_shared<Student>(Student("Mohamedo Alganzoro", "A19EC4015", "Mido", 1)),
			make_shared<Student>(Student("Ahmedo Yousif", "A19EC4003", "Ahmedo", 2))
	}
		),
		
 doctors_(
	{
		make_shared<Doctor>(Doctor("Mohamed Alganzory", "Mohamed")),
		make_shared<Doctor>(Doctor("Ahmed Yousif", "Ahmed"))
	}
		)

{
}
