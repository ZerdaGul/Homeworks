#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 3
#define COLS 3

typedef struct{
    int board[3][3]; //puzzle table
    int score; 
    int total_move;
    int empty_x; //x coordinate of space
    int empty_y; //y coordinate of space
    int best_score; //best_score
    int array[4];
}puzzle_t;

void play_game_user(puzzle_t *puzzle); 
int move(puzzle_t *puzzle,char num_c, char dir);
int check(puzzle_t *puzzle);
int isSolvable(puzzle_t *puzzle);
void finish_pc(puzzle_t *puzzle);
int auto_finish(puzzle_t *puzzle,int *last_move);
void show_best_score();

int main(){

    FILE *best_score_f; //file pointer for best_score.txt
    char c; //option that selected by user from menu 
    int flag=0; //if user select exit in menu,  flag will equal 1
    int k, l, hold; //use in loops
    puzzle_t puzzle; 

    best_score_f = fopen("best_score.txt", "r"); 
    if(best_score_f == NULL){ //if at the beginning there is no best_score.txt, assign best_score 0
        printf("best_score.txt can not be opened.\n");
        puzzle.best_score=0;
    }
    else{ //if there is  a best_score.txt, assign best_score the integer value in best_score.txt.
        fscanf(best_score_f, "%d", &puzzle.best_score);
        fclose(best_score_f);
    }

    while(flag==0){ //flag checks whether user selects exit in menu or not.
        flag=0; //reassign until while continues
        do{ //print menu and get option from user until user enter valid input
        printf("Welcome to the 8-Puzzle Game!\nPlease select an option:\n");
        printf("1. Play game as a user\n2. Finish the game with PC\n3. Show the best score\n4.Exit\n> ");
        scanf(" %c", &c);
        }
        while(c<49 || c>52);
        //create a table as 012,345,678
        for(int i=0; i<ROWS; i++){
            for(int j=0; j<COLS; j++){
                puzzle.board[i][j]=(i*3)+j;
            }
        }

        srand(time(NULL));//feed rand function

        do{ //shuffle until creating a solvable table
            for (int i = ROWS - 1; i > 0; i--) {
                for (int j = COLS - 1; j > 0; j--) {
                    k = rand() % (i + 1);
                    l = rand() % (j + 1);
                    hold = puzzle.board[i][j];
                    puzzle.board[i][j] = puzzle.board[k][l];
                    puzzle.board[k][l] = hold;
                }
            }
        }
        while(isSolvable(&puzzle)==0); //checks if the table is solvable

        //find the x and y coordinates of space in the table
        for(int i=0; i<ROWS; i++){
            for(int j=0; j<COLS; j++){
                if(puzzle.board[i][j]==0){
                    puzzle.empty_x=i;
                    puzzle.empty_y=j;
                }
            }
        }
        //at the beginning of the game, score and total_move is 0
        puzzle.score=0; 
        puzzle.total_move=0;
        switch(c){
            case '1':
                play_game_user(&puzzle); //user plays
                break;
            case '2':
                finish_pc(&puzzle); //pc plays
                break;
            case '3':
                show_best_score(); //shows the best score in the best_score.txt
                break;
            case '4':
                flag=1; //when flag=1, while loop ends
                break;
        }
    }
    printf("\nProgram terminated...\n");
}

int move(puzzle_t *puzzle,char num_c, char dir){ //check whether the move user enter is valid and if it is valid make the move.

    int num_i; //integer version of character input
    int flag=0; //if flag=0, move is valid , if flag=1, move is unvalid

    num_i=num_c-'0'; 
    switch(dir){ //make move according to the user's input
        case 'R':
            if(puzzle->empty_y!=0 && puzzle->board[puzzle->empty_x][puzzle->empty_y-1]==num_i){
                puzzle->board[puzzle->empty_x][puzzle->empty_y]=num_i;
                puzzle->board[puzzle->empty_x][puzzle->empty_y-1]=0;
                puzzle->empty_y--;
                puzzle->total_move++;
            }
            else{
                flag=1;
            }
            break;
        case 'L':
            if(puzzle->empty_y!=2 && puzzle->board[puzzle->empty_x][puzzle->empty_y+1]==num_i){
                puzzle->board[puzzle->empty_x][puzzle->empty_y]=num_i;
                puzzle->board[puzzle->empty_x][puzzle->empty_y+1]=0;
                puzzle->empty_y++;
                puzzle->total_move++;
            }
            else{
                flag=1;
            }
            break;
        case 'U':
            
            if(puzzle->empty_x!=2 && puzzle->board[puzzle->empty_x+1][puzzle->empty_y]==num_i){
                puzzle->board[puzzle->empty_x][puzzle->empty_y]=num_i;
                puzzle->board[puzzle->empty_x+1][puzzle->empty_y]=0;
                puzzle->empty_x++;
                puzzle->total_move++;
            }
            else{
                flag=1;
            }
            break;
        case 'D':
            if(puzzle->empty_x!=0 && puzzle->board[puzzle->empty_x-1][puzzle->empty_y]==num_i){
                puzzle->board[puzzle->empty_x][puzzle->empty_y]=num_i;
                puzzle->board[puzzle->empty_x-1][puzzle->empty_y]=0;
                puzzle->empty_x--;
                puzzle->total_move++;
            }
            else{
                flag=1;
            }
            break;
    }
    return flag; //if flag=0, move is valid , if flag=1, move is unvalid
}

int check(puzzle_t *puzzle){

int flag=0; //if flag=0 table is correct, done. if flag=1 table is

for(int i=0; i<ROWS; i++){
    for(int j=0; j<COLS; j++){
        if(i==2 && j==2){
            if(puzzle->board[i][j]!=0){
                flag=1;
                break;
            }
        }
        else{
            if(puzzle->board[i][j]!=(i*3)+j+1){
                flag=1;
            }
        }
    }
}
return flag;
}

int isSolvable(puzzle_t *puzzle){ //check whether table is solvable or not
    
    int numbers[9];
    int i,j,k;
    int a=0;
    int counter = 0;

    for(i=0;i<ROWS;i++){
        for(j=0;j<COLS;j++){
            numbers[a]=puzzle->board[i][j];
            a++;
        }
    }
    for(k=0;k<9;k++){
        for(i=k+1;i<9;i++){
            if(numbers[i] && numbers[k] && numbers[k] > numbers[i]){
                counter++;
            }
        }
    }
    if(counter % 2 == 0){
        return 1;
    }
    else{
        return 0;
    }
    
}

void play_game_user(puzzle_t *puzzle){

FILE *bf; //file pointer for text file which includes boards 
FILE *best_score_f; 
int continue_flag=1;
char num_c, dir;
int move_flag;

bf= fopen("board.txt", "w+"); 
if(bf==NULL){
    printf("Files can not be opened.\n");
    return ;
}

//print the first state to terminal and text file
for(int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
        if(puzzle->board[i][j]==0){
            printf(" _ ");   
            fprintf(bf, " _ "); 
        }
        else{
            printf("%2d ", puzzle->board[i][j]);
            fprintf(bf, "%2d ", puzzle->board[i][j]);
        }        
    }
    printf("\n");
    fprintf(bf, "\n");
}
fprintf(bf, "\n");
fclose(bf);

while(continue_flag==1){ //continue to move until puzzle is solved
    do{//get move number and direction from user until it is valid
        printf("\nEnter your move (number-direction, e.g., 2-R): ");
        scanf(" %c-%c", &num_c, &dir);
    }
    while(num_c<49 || num_c>56|| (dir!='R' && dir!='L' && dir!='U' && dir!='D'));

    move_flag = move(puzzle, num_c, dir); //move if movement is valid. return a value according to input's validity
    
    bf= fopen("board.txt", "a+"); 
    if(bf==NULL){
        printf("Files can not be opened.\n");
        return ;
    }
    if(move_flag==1){
        printf("\n%c-%c is an illegal move!!!\n\n", num_c, dir);
    }
    else{ //if movement is valid print the current state of board to text file


        printf("\n");
        for (int i = 0; i < ROWS; i++) { //print
            for (int j = 0; j < COLS; j++) {
                if(puzzle->board[i][j]==0){
                    fprintf(bf, " _ ");  
                }
                else{
                    fprintf(bf, "%2d ", puzzle->board[i][j]);
                }        
            }
            fprintf(bf, "\n");
        }
        fprintf(bf, "\n");
    }
    //print the current state to terminal whether movement is valid or not
    for (int i = 0; i < ROWS; i++) { //print
        for (int j = 0; j < COLS; j++) {
            if(puzzle->board[i][j]==0){
                printf(" _ "); 
            }
            else{
                printf("%2d ", puzzle->board[i][j]);
            }        
        }
        printf("\n");
    }
    continue_flag=check(puzzle); //check the state of the board

    if(continue_flag==0){ //if puzzle is solved, print the messages below
        printf("\nCongratulations! You finished the game.\n");
        printf("Total number of move: %d\n", puzzle->total_move);
        puzzle->score= 1000-(10*puzzle->total_move);
        printf("Your score: %d\n\n", puzzle->score);
        if(puzzle->score > puzzle->best_score){
            puzzle->best_score = puzzle->score;
        }
        best_score_f = fopen("best_score.txt", "w+"); 
        if(best_score_f == NULL){
            printf("Files can not be opened.\n");
        }
        fprintf(best_score_f, "%d", puzzle->best_score);
        fclose(best_score_f);
    }
    fclose(bf);
}

}

void show_best_score(){ //get the best score from best_score.txt and print it

    FILE *best_score_f;
    int best_score;

   best_score_f = fopen("best_score.txt", "r"); 
    if(best_score_f == NULL){
        printf("Files can not be opened.\n");
        return ;
    }
    fscanf(best_score_f, "%d", &best_score);
    printf("\nYour best score is %d...\n\n", best_score);
}


void finish_pc(puzzle_t *puzzle){ //try to solve the puzzle with pc by using random moves.

FILE *bf;
FILE *best_score_f;
int last_move=-1;
int continue_flag=1;
int move;

bf= fopen("board.txt", "w+"); 
if(bf==NULL){
    printf("Files can not be opened.\n");
    return ;
}

//print the first state to terminal and text file
for (int i = 0; i < ROWS; i++) { //print
    for (int j = 0; j < COLS; j++) {
        if(puzzle->board[i][j]==0){
            printf(" _ ");   
            fprintf(bf, " _ "); 
        }
        else{
            printf("%2d ", puzzle->board[i][j]);
            fprintf(bf, "%2d ", puzzle->board[i][j]);
        }        
    }
    printf("\n");
    fprintf(bf, "\n");
}
fprintf(bf, "\n");

while(continue_flag==1){ //make random moves until puzzle is solved

    for(int i=0; i<4; i++){
        puzzle->array[i]=0; //includes the number around space, if there is no number then includes 0
    }
    if(puzzle->empty_x!=0){
        puzzle->array[0]= puzzle->board[puzzle->empty_x-1][puzzle->empty_y]; //D
    }
    if(puzzle->empty_x!=2){
        puzzle->array[1]= puzzle->board[puzzle->empty_x+1][puzzle->empty_y]; //U
    }
    if(puzzle->empty_y!=0){
        puzzle->array[2]= puzzle->board[puzzle->empty_x][puzzle->empty_y-1]; //R
    }
    if(puzzle->empty_y!=2){
        puzzle->array[3]= puzzle->board[puzzle->empty_x][puzzle->empty_y+1]; //L
    }

    move = auto_finish(puzzle, &last_move); //return a number between 0-3.

    switch(move){
        case 0: //if number is 0 move to Down
            printf("Computer Move: %d-D\n\n" , puzzle->array[0]);
            fprintf(bf, "Computer Move: %d-D\n\n" , puzzle->array[0]);
            puzzle->board[puzzle->empty_x][puzzle->empty_y]= puzzle->array[0];
            puzzle->board[puzzle->empty_x-1][puzzle->empty_y]=0;
            last_move= puzzle->array[0];
            puzzle->empty_x--;
            puzzle->total_move++;
            break;
        case 1: //if number is 1 move to Up
            printf("Computer Move: %d-U\n\n" , puzzle->array[1]);
            fprintf(bf, "Computer Move: %d-U\n\n" , puzzle->array[1]);
            puzzle->board[puzzle->empty_x][puzzle->empty_y]=puzzle->array[1]; 
            puzzle->board[puzzle->empty_x+1][puzzle->empty_y]=0;
            last_move= puzzle->array[1];
            puzzle->empty_x++;
            puzzle->total_move++;
            break;
        case 2: //if number is 2 move to Right
            printf("Computer Move: %d-R\n\n" , puzzle->array[2]);
            fprintf(bf, "Computer Move: %d-R\n\n" , puzzle->array[2]);
            puzzle->board[puzzle->empty_x][puzzle->empty_y]=puzzle->array[2]; 
            puzzle->board[puzzle->empty_x][puzzle->empty_y-1]=0;
            last_move= puzzle->array[2];
            puzzle->empty_y--;
            puzzle->total_move++;
            break;
        case 3: //if number is 3 move to Left
            printf("Computer Move: %d-L\n\n" , puzzle->array[3]);
            fprintf(bf, "Computer Move: %d-L\n\n" , puzzle->array[3]);
            puzzle->board[puzzle->empty_x][puzzle->empty_y]=puzzle->array[3]; 
            puzzle->board[puzzle->empty_x][puzzle->empty_y+1]=0;
            last_move= puzzle->array[3];
            puzzle->empty_y++;
            puzzle->total_move++;
            break;
    }
    for (int i = 0; i < ROWS; i++) { //print the current state of the board to terminal and the text file
        for (int j = 0; j < COLS; j++) {
            if(puzzle->board[i][j]==0){
                fprintf(bf, " _ "); 
                printf(" _ "); 
            }
            else{
                fprintf(bf, "%2d ", puzzle->board[i][j]);
                printf("%2d ", puzzle->board[i][j]);
            }        
        }
        fprintf(bf, "\n");
        printf("\n");
    }
    fprintf(bf, "\n");
    printf("\n");

    continue_flag= check(puzzle); //check whether puzzle is solved or not
    //printf("total_move== %d\n", puzzle->total_move);


}
//print number of total move to terminal 
printf("Computer finished the game.\n");
printf("Total number of moves: %d\n\n", puzzle->total_move);
puzzle->score= 1000-(10*puzzle->total_move);

if(puzzle->score > puzzle->best_score){ //if score is higher than best score, change best score
    puzzle->best_score = puzzle->score;
    best_score_f = fopen("best_score.txt", "w+"); 
    if(best_score_f == NULL){
        printf("Files can not be opened.\n");
    }
    else{
        fprintf(best_score_f, "%d", puzzle->best_score);
        fclose(best_score_f);
    }
}

fclose(bf);
}

int auto_finish(puzzle_t *puzzle,int *last_move){
    //recursive function to pick a random move
    int move;
    move = rand()%4;
    if(puzzle->array[move]==0 || puzzle->array[move]==*last_move){
        auto_finish(puzzle, last_move); 
    }
    else{
        return move;
    }
}
