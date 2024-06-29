#pragma once

#include <deque>
#include <memory>
#include "Student.h"
#include "Course.h"
#include "Doctor.h"

class DataBase
{
    private:
        DataBase(); 
        // = default;
        

    public:
        std::deque <std::shared_ptr<Course> > courses_;
        std::deque <std::shared_ptr<Student> > students_;
        std::deque <std::shared_ptr<Doctor> > doctors_;
        std::vector <std::string> doctorList_;
        std::vector <std::string> studentList_;
        std::vector <std::string> studentIDList_;
        
    
    public:
        DataBase(const DataBase&) = delete;

//pointer style singleton generator
        static DataBase* instance()
        {
            static DataBase* instance = new DataBase;
            return instance;
        }

//reference style singleton generator
        // static DataBase& instance()
        // {
        //     static DataBase instance;
        //     return instance;
        // }
};

#define DOCTORS DataBase::instance()->doctors_ 
#define STUDENTS DataBase::instance()->students_ 
#define COURSES DataBase::instance()->courses_ 
#define students DataBase::instance()->studentList_
#define doctors DataBase::instance()->doctorList_
#define studentsID DataBase::instance()->studentIDList_
