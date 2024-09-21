#include "directory.h"

Directory::Directory():File(){
    parent=nullptr;
}

Directory::Directory(string n, string p, Directory *par):File("D",n,p){
    parent=par;
}

Directory::Directory(const Directory &d):File(d){
    parent=d.parent;
    files.resize(d.files.size());
    for(int i=0; i<d.files.size(); i++){
        files[i]= d.files[i];
    }
}


Directory::~Directory(){

    for (auto ptr : files) {
        delete ptr;
    }
    files.clear();
}


void Directory::mkdir(string dirName) { //create new directory in current directory

    if(4096+ Directory::diskSize>10*MB){ //control of disk size
        throw invalid_argument("Error: Disk is full. Please delete some files.");
    } 

    for (size_t i = 0; i < files.size(); ++i) { //check same name
        if (files[i]->getName() == dirName) {
            throw invalid_argument("Error: Directory or file with the same name already exists.");
        }
    }
    //create new directory
    Directory* newDir = new Directory(dirName, (getPath() + dirName + "/"), this); 
    Directory::diskSize += 4096;
    files.push_back(newDir);

}
void Directory::rm(string itemName) {//rm  regular or softlinked files.
    bool found = false;
    bool foundDir=false;

    for (size_t i = 0; i < files.size(); ++i) {
        if (files[i]->getName() == itemName) {
            if (dynamic_cast<Directory*>(files[i])) foundDir=true; 
            else{
                size_t deleteSize=0;
                RegularFile *reg= dynamic_cast<RegularFile*>(files[i]);
                if(reg)deleteSize+=reg->getSize();
                Directory::diskSize -=deleteSize; //decrease disk size
                delete files[i]; //delete file
                files.erase(files.begin() + i);
                found = true;
                break;
            }

        }
    }

    if (!found) { //give error messages
        if(foundDir==true)  throw invalid_argument("Error: cannot remove '"+ itemName +"': Is a directory");
        else throw invalid_argument("Error: cannot remove '"+ itemName +"': No such file or directory");
    }
}


void Directory::rmdir(string itemName) { //delete empty directories

    bool found = false;
    bool foundFile=false;
    bool foundFullDir=false;

    if(itemName[0]=='/'){ //arrange the item name
        itemName= itemName.substr(1,itemName.length());
    }
    if(itemName[itemName.length()-1]=='/'){
        itemName= itemName.substr(0,itemName.length()-1);
    }


    for (size_t i = 0; i < files.size(); ++i) {
        if (files[i]->getName() == itemName) {
            Directory *temp=dynamic_cast<Directory*>(files[i]);
            if (temp == nullptr) foundFile=true; //file with same directory name
            if(temp!=nullptr && temp->files.size()!=0) foundFullDir=true; //directory is full
            if(temp!=nullptr && temp->files.size()==0){ 
                Directory::diskSize -=4096; //4 KB size for directory
                delete files[i]; //delete directory
                files.erase(files.begin() + i);
                found = true;
                break;
            }
        }
    }

    if (!found) { //error messages
        if(foundFullDir==true) throw invalid_argument("Error: cannot remove '"+ itemName +"': is not empty directory");
        else if(foundFile==true) throw invalid_argument("Error: cannot remove '"+itemName +"': Is a not directory");
        else throw invalid_argument("Error: Item '"+ itemName + "' not found.");
    }
}



bool is_file_exist(const string& fileName) { //check file is exist
    ifstream dosya(fileName.c_str());
    return dosya.good();
}

void Directory::cp(string sourceFilePath) {

    ifstream sourceFile(sourceFilePath);
    bool found;
    vector<string> pathNames;
    string fileName;

    if (is_file_exist(sourceFilePath)) { //search for path in regular OS system(computer)
            string d2=""; //find the path name
            for(int i=0; i<sourceFilePath.length(); i++){
                if(sourceFilePath[i]!='/'){
                    d2= d2+sourceFilePath[i];
                    if(i==sourceFilePath.length()-1){
                        pathNames.push_back(d2);
                        d2 = "";
                    }
                }
                else{
                    if(i!=0){
                        pathNames.push_back(d2);
                        d2="";
                    }
                }
            }

            //create regular file
            RegularFile *newFile= new RegularFile(pathNames.back(), getPath()+pathNames.back(), "");
            string content="";
            char c; 
            while(sourceFile.get(c)){
                content+=c;
            }
            newFile->setData(content); //get content
            sourceFile.close();

            bool sameNameFlag=false;
            for(int i=0;i<files.size(); i++){
                if(newFile->getName()==(files[i])->getName()){
                    delete newFile; //give error
                    throw invalid_argument("Error: cannot copy '"+ (files[i])->getName() +"': has same name with a file in directory");
                }
            }
            if(Directory::diskSize+ newFile->getSize()>10*MB){ //give error
                throw invalid_argument("Error: Disk is full. Please delete some files.");
            }else{ // add regular file to directory
                Directory::diskSize+= newFile->getSize();
                files.push_back(newFile);
            }

    }
    else {
        //copying from my OS system
        Directory *currentDir= this;
        currentDir=currentDir->cd(sourceFilePath, found);
        if(found==0 && sourceFilePath.back()!='/'){ //rootta böyle bir klasör yoksa ve sonu / ile bitmiyorsa yani dosyaysa
            currentDir=this;
            string d=""; //arrange path name
            for(int i=0; i<sourceFilePath.length(); i++){
                if(sourceFilePath[i]!='/'){
                    d= d+sourceFilePath[i];
                    if(i==sourceFilePath.length()-1){
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
            fileName= pathNames.back(); //get filename 
            int l1= sourceFilePath.length();
            int l2= fileName.length();
            string newPath= sourceFilePath.substr(0, l1-l2); //get the directory path of file
            currentDir=this;
            currentDir= currentDir->cd(newPath, found);
            if(sourceFilePath==fileName){ //if file is in current directory
                currentDir=currentDir->cd(".", found);
            }
            if(found==1){ //if directory is found
                bool founded=false;
                for(int k=0; k<currentDir->files.size(); k++){
                    RegularFile* rf= dynamic_cast<RegularFile *>(currentDir->files[k]);
                    if(rf){ 
                        bool sameName=false;
                        if(rf->getName()==fileName){//if file for copying is found
                            founded=true;
                            for(int k=0; k<files.size(); k++){
                                if(files[k]->getName()==fileName){
                                    sameName=true; //there is another file with same name in current directory
                                }
                            }
                            if(sameName==false){
                                RegularFile *newFile2= new RegularFile(fileName, getPath()+fileName, "");
                                newFile2->setData(rf->getData());
                                if(Directory::diskSize+ newFile2->getSize()>10*MB){
                                    delete newFile2; //if disksize is not enough delete file
                                    throw invalid_argument("Error: Disk is full. Please delete some files.");
                                }else{
                                    files.push_back(newFile2); //add file into directory
                                    Directory::diskSize+=newFile2->getSize(); //increase the used diskSize
                                    return;
                                }
                            }else{ //error messages
                                throw invalid_argument("Error: cannot copy '"+fileName +"': has same name with a file in directory");
                            }
                        }
                    }
                }
                if(founded==false){ //error messages
                    throw invalid_argument("Error: cannot copy '"+fileName +"': There is not such a file in directory");
                }
            }
            else{ //error messages
                throw invalid_argument("Error: cannot copy '"+ fileName +"': There is not such a file in directory");
            }
        }
        else{
            if(Directory::diskSize+ 4096>10*MB){  //error messages
                throw invalid_argument("Error: Disk is full. Please delete some files.");
            }else{
                Directory *newDirectory= new Directory(currentDir->getName(), (getPath() + currentDir->getName() + "/"), this);
                files.push_back(newDirectory); //add directory
                Directory::diskSize+=4096; //increase the disk size
                newDirectory->copyDirectory(currentDir); //copy content of directory recursively
            }

        }
    }
}

void Directory::copyDirectory(Directory *targetDir){ //copy content of directory recursively

    for(int i=0; i<targetDir->files.size(); i++){
        RegularFile *reg= dynamic_cast<RegularFile *>(targetDir->files[i]);
        Directory *dir= dynamic_cast<Directory *>(targetDir->files[i]);
        SoftLinkedFile *soft= dynamic_cast<SoftLinkedFile *>(targetDir->files[i]);
        if (dir) {
            Directory* newdir = new Directory(dir->getName(), getPath()+ dir->getName() +"/", this);
            newdir->copyDirectory(dir); //copy content of directory recursively
            files.push_back(newdir);

        } else if (reg) { //copy content of regular file
            RegularFile* newRegFile = new RegularFile(reg->getName(), getPath()+reg->getName(), reg->getData());
            files.push_back(newRegFile);
        } else if (soft) { //copy content of soft linked file
            SoftLinkedFile* newSoftFile = new SoftLinkedFile(soft->getName(), getPath()+ soft->getName(), soft->getRegFile());
            files.push_back(newSoftFile);
        }
    }
}




void Directory::link(string filePath, string linkName) { //link files

    for(int i=0; i<files.size(); i++){
        if(files[i]->getName()==linkName){ //same name error
            throw invalid_argument("Error: cannot link '"+ linkName +"': has same name with a file in directory");
        }
    }

    vector< string > pathNames;
    string fileName;
    string d="";
    bool pushed=false;
    for(int i=0; i<filePath.length(); i++){
        if(filePath[i]!='/'){
            d= d+filePath[i]; //arrange path name
            if(i==filePath.length()-1){
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
    fileName= pathNames.back(); //file name
    int l1= filePath.length();
    int l2= fileName.length();
    string newPath= filePath.substr(0, l1-l2); //directory path
    Directory* foundDir=this;
    bool found=false;
    foundDir= foundDir->cd(newPath, found);
    if(filePath==fileName){
        foundDir= foundDir->cd(".", found); //if file is in same directory
    }
    
    

    if(found==1){ //if directory is found
        for(int i=0; i<foundDir->files.size(); i++){
            RegularFile* foundReg= dynamic_cast<RegularFile *>(foundDir->files[i]);
            if(foundDir->files[i]->getName()==fileName && foundReg!=nullptr){ //if file is found
                SoftLinkedFile* soft= new SoftLinkedFile(linkName, getPath()+ linkName, foundReg);
                files.push_back(soft); //add soft link which is created
                pushed=true;
                return;
            }
        }
    }

    if(pushed==false){ //error messages
        throw invalid_argument("Error: cannot link '"+ fileName +"': There is no such a file in directory");
    }
}




Directory* Directory::cd(string p, bool &found) {
    vector<string> pathNames;
    found=false;
    if (p == "..") { //turn back to previsious directory
        found=true;
        if (parent != nullptr) {
            return parent;
        }
        else{
            return this;
        }
    }
    else if(p=="."){ // stay in current directory
        found=true;
        return this;
    }
    else if(p==" "){ // turn back to root
        found=true;
        Directory *ptr;
        ptr= this;
        while(ptr->parent != nullptr){
            ptr = ptr->parent;
        }
        return ptr;
    }
    else{
        string d=""; //arrange path
        for(int i=0; i<p.length(); i++){
            if(p[i]!='/'){
                d= d+p[i];
                if(i==p.length()-1){
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

        Directory* currentDir = this;
        char c= p[0];
        string subP1 = p.substr(0, 3);
        string subP2 = p.substr(0, 2);
        if(subP1=="../"){ //if path is started with '..'
            if (parent != nullptr) {
                currentDir= parent;
            }
            else{
                currentDir= this;
            }
            pathNames.erase(pathNames.begin());
            if(pathNames.size()==0) found=true;
        }
        else if(subP2=="./"){ //if path is started with '.'
            currentDir = this;
            pathNames.erase(pathNames.begin());
            if(pathNames.size()==0) found=true;
        }
        else if(c=='/'){ //if path is started with '/'
            Directory *ptr;
            ptr= this;
            while(ptr->parent != nullptr){
                ptr = ptr->parent;
            }
            currentDir= ptr;
            if(pathNames.size()==0) found=true;
        }

        for (const string& dirName : pathNames) {
            found = false;

            for (File* file : currentDir->files) {
                Directory* dir = dynamic_cast<Directory*>(file);
                if (dir) {
                    if (dir->getName() == dirName) { //if directory found, go inside of it
                        currentDir = dir;
                        found = true;
                        break;
                    }
                }
            }

            if (!found) { //if directory cannot be found return current directory
                return this;
            }
        }

        return currentDir; //if directory foundes return founded directory
    }
    return this;
}


void Directory::catFile(string fileName){ //cat command

    bool found=false;
    for(int i=0; i< files.size(); i++){
        SoftLinkedFile* soft= dynamic_cast<SoftLinkedFile* >(files[i]); 
        if(files[i]->getName()== fileName && soft!=nullptr){ //if file is a soft linked file first check if regular file is still valid

            bool found2=false;
            vector<string> pathNames;
            string d="";
            for(int i=0; i<soft->getRegPath().length(); i++){
                if(soft->getRegPath()[i]!='/'){
                    d= d+soft->getRegPath()[i];
                    if(i==soft->getRegPath().length()-1){
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
            bool found3=false;
            string fileName= pathNames.back(); //file name
            int l1= soft->getRegPath().length();
            int l2= fileName.length();
            string newPath= soft->getRegPath().substr(0, l1-l2);
            Directory* currentDir= cd(newPath, found2);
            if(found2==true){
                for(int k=0; k<currentDir->files.size(); k++){
                    RegularFile *reg= dynamic_cast<RegularFile *>(currentDir->files[k]);
                    if(reg!=nullptr && reg->getName()==fileName){ // if regular file is still valid show the content
                        reg->cat();
                        found=true;
                        found3=true;
                        break;
                    }
                }

                if(found3==false){ // if regular file is removed, give error
                    throw invalid_argument("Error: cannot cat '"+ soft->getName() +"': source file not found");
                }
            }
        }else if(files[i]->getName()== fileName){
            files[i]->cat(); //cat for directory and regular file types
            found=true;
            break;
        }
    }

    if(!found){ //error messages
        throw invalid_argument("Error: cannot cat '"+ fileName +"': No such file in current directory");
    }

}




void loadFromFile(Directory* currentDir, ifstream& inputFile) { //load at the beginning of the code run
    
    vector<string> lineWords;
    string line, d, type, name, path,time, data, regPath;
    char c;
    int fileSize;
    while (getline(inputFile, line)) {
        d="";
        for(int i=0; i<line.length(); i++){
            if(line[i]!=' '){
                d= d+line[i];
                if(i==line.length()-1){
                    lineWords.push_back(d);
                    d = "";
                }
            }
            else{
                lineWords.push_back(d);
                d="";
            }
        }

        if(lineWords.size()>=4){
            type= lineWords[0];
            name= lineWords[1];
            path= lineWords[2];
            time= lineWords[3];
        }

        if (type == "D") { //if a directory
            if(path==currentDir->getPath()+ name+ "/"){ //if current directory and path name is same
                Directory *subDir= new Directory(name, path, currentDir); 
                subDir->setDate(time); //set date
                currentDir->files.push_back(subDir); //add directory
                Directory::diskSize +=4096; //increase the disk size
            }
            else{
                int l1= path.length();
                int l2= name.length()+1;
                string newPath= path.substr(0, l1-l2);
                bool found=false;
                currentDir=currentDir->cd(newPath, found);
                if(found==1){
                    Directory *subDir= new Directory(name, path, currentDir);
                    subDir->setDate(time); //set date
                    currentDir->files.push_back(subDir); //add directory
                    Directory::diskSize +=4096;  //increase disk size
                }
            }
            
        } else if (type == "R") { //generate regular file
            fileSize= stoi(lineWords[4]);
            data="";
            for(int i=0; i<fileSize; i++){
                inputFile.get(c);
                data+=c;
            }
            inputFile.get(c);

            RegularFile *newReg= new RegularFile(name, path, data);
            int l1= path.length();
            int l2= name.length();
            string newPath= path.substr(0, l1-l2);
            bool found=false;
            currentDir=currentDir->cd(newPath, found);
            if(found==1){
                newReg->setDate(time);
                currentDir->files.push_back(newReg);
                Directory::diskSize +=newReg->getSize();
            }
        } else if (type == "S") { //generate soft linked file
            regPath=lineWords[4];
            SoftLinkedFile *newSoft= new SoftLinkedFile(name, path, regPath);
            int l1= path.length();
            int l2= name.length();
            string newPath= path.substr(0, l1-l2);
            bool found=false;
            currentDir=currentDir->cd(newPath, found);
            newSoft->setRegPath(regPath);
            if(found==1){
                newSoft->setDate(time);
                currentDir->files.push_back(newSoft);
            }
        }

        lineWords.clear();
    }
}

void loadDisk(Directory* rootDir) { //load disk

    ifstream inputFile("disk.txt");
    if (!inputFile.is_open()) {
        Directory::diskSize=0;
        return;
    }
    vector<string> lineWords;
    string line, d, type, name, path, time;
    getline(inputFile, line);
    d="";
    for(int i=0; i<line.length(); i++){
        if(line[i]!=' '){
            d= d+line[i];
            if(i==line.length()-1){
                lineWords.push_back(d);
                d = "";
            }
        }
        else{
            lineWords.push_back(d);
            d="";
        }
    }

    if(lineWords.size()==4){
        type= lineWords[0];
        name= lineWords[1];
        path= lineWords[2];
        time= lineWords[3];
    }


    if(lineWords.size()==4 && type=="D" && name=="Root" && path=="/"){ //if root path is true
        rootDir->setDate(time);
        loadFromFile(rootDir, inputFile);  //load the other contents in directory
    }

    inputFile.close();

    rootDir->arrangeSoftLinkedFiles();

}

void Directory::arrangeSoftLinkedFiles(){ //find the regular files of soft linked files 

    for (size_t i = 0; i < files.size(); ++i) {
        Directory* dir=dynamic_cast<Directory*>(files[i]);
        SoftLinkedFile* soft=dynamic_cast<SoftLinkedFile*>(files[i]);
        if (dir) {
            dir->arrangeSoftLinkedFiles();
        } else if(soft){

            string d="";
            vector<string> pathNames;
            for(int i=0; i<soft->getRegPath().length(); i++){
                if((soft->getRegPath())[i]!='/'){
                    d= d+(soft->getRegPath())[i];
                    if(i==(soft->getRegPath()).length()-1){
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
            int l1= soft->getRegPath().length();
            int l2= pathNames.back().length();
            string newPath= soft->getRegPath().substr(0, l1-l2);
            bool found=false;
            Directory* currentDir= this->cd(newPath, found);
            for(int i=0; i<currentDir->files.size(); i++){
                RegularFile *rf= dynamic_cast<RegularFile*>(currentDir->files[i]);
                if(rf!=nullptr && rf->getName()==pathNames.back()){
                    soft->setRegFile(rf); //set regular file
                    break;
                }
            }
            pathNames.clear();
        }
    }
}


void Directory::ls(string parameter){

    if (parameter == "R") { //recursively
        for (auto files: *this) { //used directory iterator
            cout << endl;
            Directory* dir=dynamic_cast<Directory*>(files);
            RegularFile *reg = dynamic_cast<RegularFile *>(files);
            SoftLinkedFile *soft = dynamic_cast<SoftLinkedFile *>(files);
            if (dir) {
                cout <<files->getType()<< " "<< files->getName() << " "<< files->getDate();
                dir->ls("R");
            } else if(reg){
                cout << files->getType() << " "<< files->getName()<<" "<< reg->getSize()<< " bytes "<< files->getDate();
            }
            else if(soft){
                cout <<files->getType()<< " " <<files->getName() << " > "<< soft->getRegPath() <<" "<<  files->getDate();
            }
        }
    }else{
        for (auto files: *this) {//used directory iterator
            RegularFile *reg = dynamic_cast<RegularFile *>(files);
            SoftLinkedFile *soft = dynamic_cast<SoftLinkedFile *>(files);
            if(reg){
                cout << files->getType() << " "<< files->getName()<<" "<< reg->getSize()<< " bytes "<< files->getDate();
            }
            else if(soft){
                cout << files->getType()<< " "<< files->getName()<<" > "<< soft->getRegPath() <<" "<<files->getDate();
            }
            else{
                cout << files->getType()<< " "<< files->getName()<<" "<< files->getDate();
            }
            cout << endl;
        }
    }
}