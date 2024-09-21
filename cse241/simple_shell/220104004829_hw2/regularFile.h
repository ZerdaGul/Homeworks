#ifndef REGULAR_H
#define REGULAR_H

#include <string>
#include "file.h"
#include "directory.h"
using namespace std;

class RegularFile:public File{
    private:
        size_t size;
        string data;
    public:
        RegularFile():File(),size(0),data(""){}
        RegularFile(string n, string p, string content):File("R",n,p){
            size=content.length();
            data=content;
        }

        RegularFile(const RegularFile& cf):File(cf){
            size=cf.size;
            data= cf.data;
        }
        ~RegularFile(){
        }

        RegularFile& operator=(const RegularFile &rs){
            if(this!=&rs){
                File::operator=(rs);
                size=rs.size;
                data= rs.data;
            }
            return *this;
        }

        void setData(string content){
            data=content;
            size=content.length();
        }
        string getData()const{return data;}

        void setSize(size_t s){size=s;}
        size_t getSize()const{return size;}

        virtual void cat()const{ //used regular file iterator
            
            for(auto c: *this){
                cout << c;
            }
            cout<<endl;
        }

        void addContent(string content){
            data+=content;
            size+=content.length();
        }
        
        class Iterator{
            public: 
                Iterator(const RegularFile& r, size_t pos):reg(r),position(pos){}
                
                char operator*()const{
                    return reg.data[position];
                }
                Iterator& operator++(){
                    position++;
                    return *this;
                }
                bool operator!=(const Iterator& o){
                    return position!=o.position;
                }


            private:
                const RegularFile &reg;
                size_t position;
        };

        Iterator begin()const{
            return Iterator(*this, 0);
        }
        Iterator end()const{
            return Iterator(*this, data.length());
        }


};

#endif