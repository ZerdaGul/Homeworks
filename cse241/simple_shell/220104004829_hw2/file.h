#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream> 
using namespace std;

class File{
    private:
        string type;
        string name;
        string path;
        string dateTime;
        
    public:
        File(){
            type="";
            name="";
            path="";
            dateTime=getCurrentDateTime();
        }
        File(string t, string n, string p){
            type=t;
            name=n;
            path=p;
            dateTime=getCurrentDateTime();
        }
        File(const File &cf){
            type=cf.type;
            name= cf.name;
            path=cf.path;
            dateTime=cf.dateTime;
        }
        
        File& operator=(const File &r){
            if(this!=&r){
                type=r.type;
                name=r.name;
                path=r.path;
                dateTime=r.dateTime;
            }
            return *this;
        }
        

        ~File(){
            
        }

        string getName()const{return name;}
        string getPath()const{return path;}        
        string getType()const{return type;}
        string getDate()const{return dateTime;}

        void setType(string t){type=t;}
        void setName(string n){name=n;}
        void setPath(string p){path=p;}
        void setDate(string d){dateTime=d;}
        
        virtual void cat()const=0;


        string getCurrentDateTime() const {
            auto now = chrono::system_clock::now();
            time_t nowTimeT = chrono::system_clock::to_time_t(now);

            stringstream ss;
            ss << put_time(std::localtime(&nowTimeT), "%Y-%m-%d--%X");
            return ss.str();
        }
        
};

#endif