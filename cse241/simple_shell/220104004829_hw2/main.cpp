#include "file.h"
#include "softLinked.h"
#include "regularFile.h"
#include "directory.h"
#include <stdexcept>

using namespace std;

void saveToFile(const Directory* currentDir, ofstream& outputFile);
void saveDisk(const Directory& currentDir);
size_t Directory::diskSize =0;

int main(){

string d;
string command, argument1, argument2, input;
bool found=false;
vector<string> pathNames;

Directory root("Root", "/", nullptr); //generate root
Directory *currentDir= &root;
Directory::diskSize = currentDir->getDiskSize();
loadDisk(currentDir); //load disk


string cp=currentDir->getPath();
cout<<  "MYSHELL"<<endl;
cout << "Commands are ls, ls -R, rmdir, rm, mkdir, cat, cp, link, cd, exit"<<endl;
cout<< cp<<">";

while(getline(cin, input) && input!="exit"){ //get input commands
    try{
        command="";
        argument1="";
        argument2="";
        d="";
        for(int i=0; i<input.length(); i++){
            if(input[i]!=' '){
                d= d+input[i];
                if(i==(input.length()-1)){
                    pathNames.push_back(d);
                    d = "";
                }
            }
            else{
                if(i!=0){
                    pathNames.push_back(d);
                    d="";
                }
            }
        }
        if(command=="exit" && argument1=="" && argument2=="")break;

        if(pathNames.size()>3){
            throw invalid_argument("Error: Invalid command");
        }
        else{
            if(pathNames.size()!=0)command=pathNames[0];
            if(pathNames.size()>1)argument1= pathNames[1];
            if(pathNames.size()>2)argument2= pathNames[2];

            if(command=="ls"){
                if(argument1=="-R" && argument2==""){
                    currentDir->ls("R");
                    cout << endl;
                }else if(argument1=="" && argument2==""){
                    currentDir->ls("");
                }
                else{
                    throw invalid_argument("Error: Invalid command");
                }
            }
            else if(command=="rmdir"){
                if(argument1!="" && argument2=="") currentDir->rmdir(argument1);
                else throw invalid_argument("Error: Invalid command");
            }
            else if(command=="rm"){
                if(argument1!="" && argument2=="")currentDir->rm(argument1);
                else throw invalid_argument("Error: Invalid command");
            }
            else if(command=="mkdir"){
                if(argument1!="" && argument2=="") currentDir->mkdir(argument1);
                else throw invalid_argument("Error: Invalid command");
            }
            else if(command=="cat"){
                if(argument1!="" && argument2=="") currentDir->catFile(argument1);
                else throw invalid_argument("Error: Invalid command");
            }
            else if(command=="cp"){
                if(argument1!="" && (argument2=="." || argument2=="")) currentDir->cp(argument1);
                else throw invalid_argument("Error: Invalid command");
            }
            else if(command=="link"){
                if(argument1!="" && argument2!="") currentDir->link(argument1,argument2);
                else throw invalid_argument("Error: Invalid command");
            }
            else if(command=="cd"){
                if(argument1!="" && argument2==""){
                    currentDir= currentDir->cd(argument1, found);
                    if(found==false) throw invalid_argument("Error: Directory '" + argument1 + "' not found.");
                }
                else if(argument1=="" && argument2==""){
                    currentDir= currentDir->cd(" ", found);
                    if(found==false)throw invalid_argument("Error: Directory cannot be found.");
                }
                else{
                    throw invalid_argument("Error: Invalid command");
                }
            }
            else if(command==""){
                //pass
            }
            else{
                throw invalid_argument("Error: Invalid command");
            }

            saveDisk(root);
        }   


    }
    catch(exception &e){ //exception handling
        cout<< e.what()<<endl;
    }
    
    cp=currentDir->getPath();
    if(cp!="/" && cp.back()== '/'){
        cp.pop_back();
    }
    cout<< cp<<">";
    
    pathNames.clear();

}


}


void saveToFile(const Directory* currentDir, std::ofstream& outputFile) {
    
    if (currentDir == nullptr) {
        return;
    }

    outputFile << "D " << currentDir->getName() << " " << currentDir->getPath()<< " " << currentDir->getDate() << endl;

    for (const auto& file : currentDir->getFiles()) {
        Directory* subDir = dynamic_cast<Directory*>(file);
        RegularFile* regFile = dynamic_cast<RegularFile*>(file);
        SoftLinkedFile* softFile = dynamic_cast<SoftLinkedFile*>(file);
        if (subDir) {
            saveToFile(subDir, outputFile);
        } else if (regFile) {
            outputFile << "R " << regFile->getName() << " " << regFile->getPath() << " "<< regFile->getDate()<< " " << regFile->getSize()<<endl;
            outputFile << regFile->getData() << endl;
        } else if (softFile) {
            outputFile << "S " << softFile->getName() << " " << softFile->getPath() << " "<< softFile->getDate()<< " "  << softFile->getRegPath() << endl;
        }
    }
}

void saveDisk(const Directory& currentDir) {
    ofstream outputFile("disk.txt");
    if (!outputFile.is_open()) {
        cerr << "Error: disk.txt cannot generated." << endl;
        return;
    }

    // Root dizini için kaydetmeye başla
    saveToFile(&currentDir, outputFile);

    outputFile.close();
}




