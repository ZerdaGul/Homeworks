#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "file.h"
#include "regularFile.h"
#include "softLinked.h"
#include <fstream>
#include <vector>
using namespace std;


class Directory : public File{
    private:
        vector<File *> files; //keep files
        Directory *parent; //parent Directory

    public:
        Directory();
        Directory(string n, string p, Directory *par);
        Directory(const Directory &d);
        
        
        Directory& operator=(const Directory &r){
            if(this!=&r){
                File::operator=(r);
                files.reserve(r.files.size());
                for(int i=0; i<files.size();i++){
                    files[i]=r.files[i];
                }
            }
            return *this;
        }
        

        ~Directory();

        void cat()const{
            throw invalid_argument("Error: This is a directory!"); //cat should not work for directories.
        };
 
        void ls(string parameter);
        void mkdir(string dirName);
        void rm(string itemName);
        void cp(string sourceFileName);
        void link(string filePath, string linkName);
        Directory* cd(string p, bool &found);
        void rmdir(string itemName);
        void catFile(string fileName); //cat functions used in this catFile function

        void copyDirectory(Directory *targetDir); //copy directory for cp command
        vector<File *> getFiles()const{ //get files in directory
            return files;
        }

        size_t getDiskSize()const{ //get diskSize
            int diskSize=0;
            ifstream diskFile("disk.txt");
            if (!diskFile.is_open()) {
                diskSize=0;
            }
            char c;
            while(diskFile.get(c)){
                diskSize++;
            }
            diskFile.close();
            return diskSize;
        }

        static size_t diskSize;


        void friend loadFromFile(Directory* currentDir, ifstream& inputFile); //used in loadDisk function
        void friend loadDisk(Directory* rootDir); //load disk at the beginning of the code
        int getFilesSize()const{return files.size();} 
        void arrangeSoftLinkedFiles(); //find the regular files for the sosftlinkedfiles

        class Iterator{ //iterator for directory class
            public: 
                Iterator(const Directory& d, size_t pos):dir(d),position(pos){}
                
                File * operator*()const{
                    return dir.files[position];
                }
                Iterator& operator++(){
                    position++;
                    return *this;
                }
                bool operator!=(const Iterator& o){
                    return position!=o.position;
                }


            private:
                const Directory &dir;
                size_t position;
        };

        Iterator begin()const{
            return Iterator(*this, 0);
        }
        Iterator end()const{
            return Iterator(*this, files.size());
        }
};

#endif

