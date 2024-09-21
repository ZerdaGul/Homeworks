#include <stdio.h>
#include <string.h> //for strcmp function
#include <math.h> //for sqrt function

#define MAX_WORD_COUNT 101
#define MAX_WORD_SIZE 13
#define MAX_IGNORE_COUNT 1000
#define THRESHOLD 6

int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE]);
int  read_text(const char  * text_file, const char  * ignore_file, char words[][MAX_WORD_SIZE]);
double dissimilarity(char * w1, char * w2, char dict[][MAX_WORD_SIZE], float threshold);
int repeat(char *searched_word, char words[][MAX_WORD_SIZE]); //find number of repetition in words array
int histogram(const char words[][MAX_WORD_SIZE*2+2], const int occurrences[],char  hist[][(MAX_WORD_SIZE*2)+2+5+20]);

int main(int argc, char * argv[]){

char line[250];
char selected_words[MAX_WORD_COUNT][MAX_WORD_SIZE]; // the words that user enter
char dict[2000][MAX_WORD_SIZE];
char words[300001][MAX_WORD_SIZE];
char hist_words[MAX_WORD_COUNT][(MAX_WORD_SIZE*2)+2]; //the words that histogram function uses
int occurrences[MAX_WORD_COUNT];
char searched_word[MAX_WORD_SIZE]; //the words user enter or the closest words to them. use it for dissimilarity
double min_dissim=THRESHOLD; //minimum value dissimilarity value betweem the searched word and every word in dictionary 
int i=0, a=0, b=0, r=0, m=0, p=0; //use it in loops
int num_words=0; //number of words that user enter
char file_name_dict[]= "dictionary.txt";
char file_name_text[]= "input.txt";
char file_name_ignore[]= "ignore.txt";
double dissim=0; //dissimilarity value which return by dissimilarity function
int flag1=0; //check whether the word in dictionary or not
int repeat_num; //number of repetition times for a word in words array 
int num_dict_words=0; //number of words in dict array
int num_text_words=0; //number of words in text
char hist[MAX_WORD_COUNT][(MAX_WORD_SIZE*2)+2+5+20]; //histogram array

for(int i=0; i<MAX_WORD_COUNT; i++){
    selected_words[i][0]='-'; //make all the elements sentinal valaue at first
}

printf("Enter word(s): ");
scanf("%[^\n]", line); //get the words from user

while(line[i]!='\0'){

    if( (line[i]>64 && line[i]<91) || (line[i]>96 && line[i]<123) || (line[i]>47 && line[i]<58)){
        selected_words[a][b]=line[i]; //get the letters and number in sentence 
        b++;
    }
    else if(line[i]==' ' || line[i]=='-'){ //seperate the sentence into words
        a++; 
        b=0;
    }
    i++;
}
//find the number of words in the array according to sentinal value
for(int i=0; i<MAX_WORD_SIZE; i++){
    if(selected_words[i][0]=='-'){
        break;
    }
    else{
        num_words=i+1;
    }
}

num_dict_words = read_dict(file_name_dict, dict); //read the words in dict array , returns number of words in dict array
num_text_words = read_text(file_name_text, file_name_ignore, words); // read the words in input file while ignore the words in ignore file, returns number of words in words array.

if(num_words==1){

        repeat_num = repeat(selected_words[0], words); //find number of repetition in input text
        if(repeat_num==0){ //if exact word doesn't appear in words
            for(int i=0; dict[i][0]!='-'; i++){ //check if the word is in dictionary
                if(strcmp(selected_words[0], dict[i])==0){
                    flag1=1;
                    break;
                }
            }
            if(flag1==1){ //if word is in dictionary 
                for(int k=0; dict[k][0]!='-'; k++){
                    if(strcmp(selected_words[0],dict[k])==0){
                        continue;
                    }
                    dissim= dissimilarity(selected_words[0], dict[k], dict, THRESHOLD);
                    if(min_dissim>dissim){
                        min_dissim=dissim;
                        for(int t=0; t<MAX_WORD_SIZE; t++){
                            searched_word[t]= dict[k][t]; //find the closest word and hold it in searched_word
                        }
                    }
                }
                if(min_dissim!=THRESHOLD){ //if dissimilarity isn't equal to threshold then find repetition times of closest word
                    repeat_num = repeat(searched_word, words);
                    if(repeat_num!=0){
                        printf("“%s” doesn’t appear in “%s” but “%s” appears %d times.\n", selected_words[0], file_name_text, searched_word, repeat_num);
                    }
                    else{
                        printf("“%s” doesn’t appear in “%s”.\n", selected_words[0], file_name_text); //if exact word and closest both doesn't appear print this message
                    }  
                }                
                else{ //if dissimilarity equal to threshold then there is no matches
                    printf("“%s” doesn’t appear in “%s”.\n", selected_words[0], file_name_text);
                }
            }
            else{ //if word doesn't appear in input text and dictionary then print this message
                printf("“%s” doesn’t appear in “%s”.\n", selected_words[0], file_name_text);
            }
        }
        else{ //print repetition times of word in input text
            printf("“%s” appears in “%s” %d times.\n", selected_words[0], file_name_text, repeat_num);
        }
}
else{

    for(m=0; m<num_words; m++){ //for each word calculate number of appears
        flag1=0;
        min_dissim=THRESHOLD;
        searched_word[0]='-';
        repeat_num = repeat(selected_words[m], words); //find number of repetition in input text
        if(repeat_num==0){ //if exact word doesn't appear in words
            for(int i=0; dict[i][0]!='-'; i++){//check if the word is in dictionary
                if(strcmp(selected_words[m], dict[i])==0){
                    flag1=1;
                    break;
                }
            }
            
            if(flag1==1){  //if word is in dictionary 
                for(int k=0; dict[k][0]!='-'; k++){
                    if(strcmp(selected_words[m],dict[k])==0){
                        continue;
                    }
                    dissim= dissimilarity(selected_words[m], dict[k], dict, THRESHOLD);
                    if(min_dissim>dissim){
                        min_dissim=dissim;
                        for(int t=0; t<MAX_WORD_SIZE; t++){
                            searched_word[t]= dict[k][t]; //find the closest word and hold it in searched_word
                        }
                    }
                }
                if(min_dissim!=THRESHOLD && searched_word[0]!='-'){ //if dissimilarity isn't equal to threshold then find repetition times of closest word
                    repeat_num = repeat(searched_word, words);
                    if(repeat_num!=0){  //take the selected_words, '->' and closest word to hist_words
                        r=0;
                        for(r=0; selected_words[m][r]!='\0' ; r++){
                            hist_words[m][r]= selected_words[m][r];
                        }
                        hist_words[m][r]='-';
                        r++;
                        hist_words[m][r]='>';
                        r++;
                        p=0;
                        for(r; r<MAX_WORD_SIZE*2+2; r++){
                            hist_words[m][r]= searched_word[p]; 
                            p++;
                            if(p==MAX_WORD_SIZE-1){
                                break;
                            }
                        }
                        occurrences[m]= repeat_num; //take the number of occurences
                    }
                    else{
                        for(int i=0; i<MAX_WORD_SIZE; i++){
                            hist_words[m][i]= selected_words[m][i]; //take the word into hist_words array
                        }
                        occurrences[m]= repeat_num; //take the number of occurences
                    }  
                }                
                else{ //take the word and its occurences
                    for(int i=0; i<MAX_WORD_SIZE; i++){
                        hist_words[m][i]= selected_words[m][i];
                    }
                    occurrences[m]= repeat_num;
                }
            }
            else{ //take the word and its occurences
                for(int i=0; i<MAX_WORD_SIZE; i++){
                    hist_words[m][i]= selected_words[m][i];
                }
                occurrences[m]= repeat_num;
            }
        }
        else{ //take the word and its occurences
            for(int i=0; i<MAX_WORD_SIZE; i++){
                hist_words[m][i]= selected_words[m][i];
            }
            occurrences[m]= repeat_num;
        }
    }
    hist_words[m][0]='-'; //sentinal value
    histogram(hist_words, occurrences, hist); //print the histogram
}
}

int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE]){

    FILE *dictf;
    char pass[4000]; //passes the text which is not used in this function
    int num_word;
    int vector_size;
    int i=0;

    dictf= fopen(file_name, "r");
    if(dictf==NULL){
        printf("Files can not be opened.\n");
        return -1; //return when an error happens
    }
    //takes the number of words in dictionary and vector size
    fscanf(dictf, "%[^=]=%d, %[^=]=%d\n", pass, &num_word, pass, &vector_size);

    while(fscanf(dictf, "%[^ ] %[^\n]\n", dict[i], pass)==2){
        i++; //number of words in dictionary
    }
    dict[i][0]='-'; //sentinal value
    fclose(dictf);
    return i; //return number of words in dictionary
}

int read_text(const char  * text_file, const char  * ignore_file, char words[][MAX_WORD_SIZE]){

    FILE *text;
    FILE *ignore;
    char c;
    int a=0, b=0;
    char ignore_words[MAX_IGNORE_COUNT][MAX_WORD_SIZE];
    int x=0;

    text= fopen(text_file, "r");
    if(text==NULL){
        printf("Files can not be opened.\n");
        return -1; //return when an error happen
    }
    ignore=fopen(ignore_file, "r");
    if(ignore==NULL){
        printf("Files can not be opened.\n");
        return -1; //return when an error happen
    }

    while((c=fgetc(ignore))!=EOF){
        //takes the letters and digits in ignore file
        if( (c>64 && c<91) || (c>96 && c<123) || (c>47 && c<58)){
            ignore_words[a][b]=c;
            b++;
        }
        else if(c==' ' || c=='\n'){ //seperate the words
            ignore_words[a][b]='\0';
            a++;
            b=0;
        }
    }
    x=a;//number of words in ignore.txt

    a=0;
    b=0;
    while((c=fgetc(text))!=EOF){
        //take the letters and digits in text(input) file
        if( (c>64 && c<91) || (c>96 && c<123) || (c>47 && c<58)){
            words[a][b]=c;
            b++;
        }
        else if(c==' ' || c=='-' || c=='\n'){ //seperate as words
            for(int j=0; j<x; j++){
                if(strcmp(words[a],ignore_words[j])==0){ //if word is in ignore file than delete it
                    for(int k=0; k<MAX_WORD_SIZE; k++){
                        words[a][k]='\0';             
                    }
                    a--;
                    break;
                }
            }
            a++;
            b=0;
        }
    }
    fclose(text);
    fclose(ignore);
    return a;
}

double dissimilarity(char * w1, char * w2, char dict[][MAX_WORD_SIZE], float threshold){

    FILE *dictf;
    char pass[4000];
    int vector_size;
    int a=0;
    int i=0;
    double vector[2][400];
    double dissim=0; 

    dictf= fopen("dictionary.txt", "r");
    fscanf(dictf, "%[^ ] %[^=]=%d",pass, pass, &vector_size);
    //get the index of w1 in dict array
    for(i=0; dict[i][0]!='-'; i++){
        if(strcmp(w1, dict[i])==0){
            break; 
        }
    }
    while(fscanf(dictf, "\n%[^ ]", pass)==1){
        if(a==i){ //get the vectors
            for(int j=0; j<vector_size; j++){
                fscanf(dictf, " %lf", &vector[0][j]);
            }
            break;
        }
        else{
            fscanf(dictf, "%[^\n]", pass);
        }
        a++;
    }
    //get the index of w2 in dict array
    for(i=0; dict[i][0]!='-'; i++){
        if(strcmp(w2, dict[i])==0){
            break;
        }
    }
    rewind(dictf);
    fscanf(dictf, "%[^ ] %[^=]=%d",pass, pass, &vector_size);
    a=0;
    while(fscanf(dictf, "\n%[^ ]", pass)==1){
        if(a==i){ //get the vectors
            for(int j=0; j<vector_size; j++){
                fscanf(dictf, " %lf", &vector[1][j]);
            }
            break;
        }
        else{
            fscanf(dictf, "%[^\n]", pass);
        }
        a++;
    }
    fclose(dictf);
    //calculate the dissimilarity
    for(int i=0; i<vector_size; i++){
        dissim += (vector[0][i]-vector[1][i])* (vector[0][i]-vector[1][i]);
    }
    dissim= sqrt(dissim);
    if(dissim<threshold){
        return dissim; //return dissimilarity value
    }
    else{
        return threshold; //return threshold if can not find any close number then threshold
    }
}

int repeat(char *searched_word, char words[][MAX_WORD_SIZE]){
    //find the number of apperings in the words array
    int repeat_num=0;
    for(int i=0; words[i][0]!='-'; i++){
        if(strcmp(searched_word, words[i])==0){
            repeat_num++;
        }
    }
    return repeat_num;
}

int histogram(const char words[][(MAX_WORD_SIZE*2)+2], const int occurrences[], char hist[][(MAX_WORD_SIZE*2)+2+5+20]){

    int scale=1;
    int num_words=0;
    int max;
    max= occurrences[0];
    int flag=1;
    int i=0, j=0;
    int similar_word=0;

    for(i=0; words[i][0]!='-'; i++){
        num_words++;
    }

    for(i=0; i<num_words; i++){
        if(max<occurrences[i]){
            max = occurrences[i]; //find the maximum occurences
        }
    }
    //calculate the scale
    if(max%20!=0){
        scale=(max/20)+1;
    }
    else{
        scale= max/20;
    }

    if(scale!=1){
    printf("Scale: %d\n",scale); //if scale is not equal to 1, print it
    }

    for(i=0; i<num_words; i++){
        similar_word=0;
        hist[i][0]='"'; //add " to the beginning
        for(j=1; j<MAX_WORD_SIZE*2+1; j++){
            if(words[i][j-1]=='\0'){
                hist[i][j]='"'; //add " to the end
                break;
            }
            hist[i][j]= words[i][j-1];
        }
        for(int a=j+1; a<MAX_WORD_SIZE*2+3; a++){
            hist[i][a]=' '; 
        }
        if(occurrences[i]!=0){
            for(int k=0; k<MAX_WORD_SIZE*2; k++){
                if(words[i][k]=='-'){
                    similar_word=1; //if there is '-' then it is closest word because of "->"
                }
            }
            if(similar_word==1){ //if there is closest match print +
                for(j=MAX_WORD_SIZE*2+3; j<((occurrences[i]/scale)+MAX_WORD_SIZE*2+3); j++){
                    hist[i][j]='+';
                }
            }
            else{ //if exact word is used then print *
                for(j=MAX_WORD_SIZE*2+3; j<((occurrences[i]/scale)+MAX_WORD_SIZE*2+3); j++){
                    hist[i][j]='*';
                }
            }
        }
        else{ //when word doesn't appear then there is no matches
            hist[i][MAX_WORD_SIZE*2+3]='N';
            hist[i][MAX_WORD_SIZE*2+4]='O';
            hist[i][MAX_WORD_SIZE*2+5]=' ';
            hist[i][MAX_WORD_SIZE*2+6]='M';
            hist[i][MAX_WORD_SIZE*2+7]='A';
            hist[i][MAX_WORD_SIZE*2+8]='T';
            hist[i][MAX_WORD_SIZE*2+9]='C';
            hist[i][MAX_WORD_SIZE*2+10]='H';
            hist[i][MAX_WORD_SIZE*2+11]='E';
            hist[i][MAX_WORD_SIZE*2+12]='S';
        }
    }
    hist[i][0]='-'; //sentinal value

    for(int i=0; hist[i][0]!='-'; i++){
        printf("%s\n", hist[i]); //print the histogram
    }
    return scale; //return scale
}