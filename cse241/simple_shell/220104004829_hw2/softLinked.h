#ifndef LINKED_H
#define LINKED_H

#include "regularFile.h"
#include "directory.h"
#define MB 1024*1024

using namespace std;

class SoftLinkedFile : public File{

    private:
        string regPath;
        RegularFile *regFile;                   
    public:
        SoftLinkedFile():File(),regPath(""), regFile(nullptr){}
        SoftLinkedFile(string n, string p ,RegularFile *rf):File("S",n, p){
            regFile= rf;
            regPath= rf->getPath();
        }
        SoftLinkedFile(string n, string p, string regFilePath):File("S",n, p){
            regFile= nullptr;
            regPath= regFilePath;
        }
        SoftLinkedFile(const SoftLinkedFile &sf):File(sf){
            regFile= sf.regFile;
            regPath= sf.getPath();
        }

        SoftLinkedFile& operator=(const SoftLinkedFile &r){
            if(this!=&r){
                File::operator=(r);
                regFile=r.regFile;
                regPath= r.getPath();
            }
            return *this;
        }

        size_t getRegSize()const{
            if(regFile !=nullptr){
                return regFile->getSize();
            }
            return 0;
        }

        ~SoftLinkedFile(){
        }

        void setRegFile(RegularFile *rf){
            regFile = rf;
            regPath= rf->getPath();

        }
        virtual void setData(const string data){
            if(regFile!=nullptr){
                regFile->setData(data);
            }
        }
        virtual void getData()const{
            if(regFile!=nullptr){
                regFile->getData();
            }
        }
        RegularFile* getRegFile()const{
            return regFile;
        }

        string getRegPath()const{
            return regPath;
        }

        void setRegPath(string newPath){
            if(regFile!=nullptr){
                regFile->setPath(newPath);
            }
            regPath= newPath;
        }

        virtual void cat()const{
            if(regFile!=nullptr){
                regFile->cat();
            }
        }
};

#endif
