#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int row;
    int col;
}point;

typedef struct {
    char type;
    int value;
}block;

block *** init_board();
void draw_board(block ***board, point *snake, int length); 
void play(block ***board);
char move(point *snake, int length);
int check_status(block ***board, point *snake, int length);
void update(block ***board, point **snake, char direction, int move_number, int *length);

int main(){
    
    block ***board;
    board=init_board();
    play(board);
    free(board);
}

block *** init_board(){

    int ox,oy; //x and y coordinates of first random obstacle
    int bx, by; //x and y coordinates of first random bait

    srand(time(NULL)); //seed the rand function

    //create the board as empty
    block ***board = (block * * *)malloc(10 * sizeof(block * *));

    for(int i=0; i<10; i++){

        board[i] = (block **)malloc(10 * sizeof (block *));
        
        for (int j = 0; j < 10; j++) {

            board[i][j] = (block *)malloc(1 * sizeof (block));
            board[i][j][0].type = 'e';
            board[i][j][0].value =0;
        
        }
    }
    //generate random obstacle and bait before playing
    do{
    ox= rand()%10;
    oy= rand()%10;
    bx= rand()%10;
    by= rand()%10;
    }
    while((ox==bx && oy==by) || (ox==0 && oy==0) || (bx==0 && by==0));

    board[ox][oy][0].type= 'o';
    board[ox][oy][0].value= 1;
    board[bx][by][0].type='b';

return board;
}

void play(block ***board){

char direction; //get direction from user
point *snake = (point *)calloc(1,sizeof(point));
int move_number=0; //number of moves
int check=0; //check whether game is over or not
int length=1; //length of snake

//snake starts from top-left of the board
snake[0].row=0; 
snake[0].col=0;

do{
    draw_board(board, snake, length); //dram the board
    direction = move(snake, length); //make moves, return the direction user enter
    move_number++; //increase number of moves user made
    check=check_status(board, snake, length); // check whether game is over or not
    if(check==0){ //if game is not over update the board and snake
        update(board, &snake, direction, move_number, &length);
    }
}
while(check==0); //continue to play until game is over
free(snake);

}


void draw_board(block ***board, point *snake, int length){

    int not_snake=1;
    printf("----------------------\n");
    for(int i=0; i<10; i++){
        printf("|");
        for(int j=0; j<10; j++){
            not_snake=1;
            //if there is snake's part in the i-j coordinate and make not_snake=0
            if(snake[0].row== i && snake[0].col==j){
                printf("O ");
                not_snake=0;
            }
            else{
                for(int k=1; k<length; k++){
                    if(snake[k].row== i && snake[k].col==j){
                        printf("X ");
                        not_snake=0;
                    }
                }
            }
            //if there is not snake part in i-j coordinate print space, obstacle or bait
            if(not_snake==1){
                switch(board[i][j][0].type){
                    case 'e': //empty
                        printf("  ");
                        break;
                    case 'b': //bait
                        printf(". ");
                        break; 
                    case 'o': //obstacle
                        if(board[i][j][0].value>9){
                            printf("%d", board[i][j][0].value);
                        }
                        else{
                            printf("%d ", board[i][j][0].value);
                        }
                        break;
                }
            }

        }
        printf("|\n");
    }
    printf("----------------------\n");

}
char move(point *snake, int length){

char direction;
int valid_move=1;
do{
    valid_move=1;
    printf("Enter the move (w,a,s,d): ");
    scanf(" %c", &direction); //get direction from user
    switch(direction){ //avoid direction that snakes goes through its own body and other than w,a,s,d buttons
        case 'w':
            if(length>1 && snake[0].row == (snake[1].row+1) && snake[0].col == snake[1].col){
                valid_move=0;
            }
            else{
                snake[0].row--;
                valid_move=1;
            }
            break;
        case 'a':
            if(length>1 && snake[0].col == (snake[1].col+1) && snake[0].row == snake[1].row){
                valid_move=0;
            }
            else{
                snake[0].col--;
                valid_move=1;
            }
            break;
        case 's':
            if(length>1 && snake[0].row == (snake[1].row-1) && snake[0].col == snake[1].col){
                valid_move=0;
            }
            else{
                snake[0].row++;
                valid_move=1;
            }
            break;
        case 'd':
            if(length>1 && snake[0].col == (snake[1].col-1) && snake[0].row == snake[1].row){
                valid_move=0;
            }
            else{
                snake[0].col++;
                valid_move=1;
            }
            break;
        default:
            valid_move=0;
            break;
    }
}
while(valid_move==0);
return direction;
}

int check_status(block ***board, point *snake, int length){

if(snake[0].row==-1 || snake[0].row==10 || snake[0].col==-1 || snake[0].col==10){ 
    printf("Snake collided with the wall. Game is over!!!\n");
    return 1;
}
else if(board[snake[0].row][snake[0].col][0].type=='e'){
    for(int i=1; i<length; i++){
        if(snake[0].row== snake[i].row && snake[0].col== snake[i].col){ 
            printf("Head of the snake hit its own body. Game is over!!!\n");
            return 1;
        }
    }
    return 0;
}
else if(board[snake[0].row][snake[0].col][0].type=='o' && board[snake[0].row][snake[0].col][0].value >length){
    printf("Snake hit an obstacle bigger the itself. Game is over!!!\n"); 
    return 1;
}
return 0;
}

void update(block ***board, point **snake, char direction, int move_number, int *length){

int temp_row1, temp_col1, temp_row2, temp_col2;
int rand_x,rand_y;
int valid_random=1;
int obstacle_counter=0;
srand(time(NULL));

temp_row1= (*snake)[0].row;
temp_col1= (*snake)[0].col;
switch(direction){ //get the x-y coordinates of snake's head before move
    case 'w':
        temp_row1=((*snake)[0].row+1);
        break;
    case 'a':
        temp_col1= ((*snake)[0].col+1);
        break;
    case 's':
        temp_row1=((*snake)[0].row-1);
        break;
    case 'd':
        temp_col1= ((*snake)[0].col-1);
        break;
}
//shift the snake
for(int i=1; i<*length; i++){
    temp_row2= (*snake)[i].row;
    temp_col2= (*snake)[i].col;
    (*snake)[i].row= temp_row1;
    (*snake)[i].col= temp_col1;
    temp_row1 = temp_row2;
    temp_col1 = temp_col2;
}

switch(board[(*snake)[0].row][(*snake)[0].col][0].type){
    case 'o': //hit obstacle which is smaller then snake
        board[(*snake)[0].row][(*snake)[0].col] = (block *)realloc(board[(*snake)[0].row][(*snake)[0].col], 1);
        board[(*snake)[0].row][(*snake)[0].col][0].type='e';
        board[(*snake)[0].row][(*snake)[0].col][0].value=0;
        break;
    case 'b': //snake eat bait
        (*length)++;
        board[(*snake)[0].row][(*snake)[0].col][0].type='e';
        (*snake)=(point *)realloc((*snake), (sizeof(point)*(*length)));
        (*snake)[(*length)-1].row= temp_row1; 
        (*snake)[(*length)-1].col= temp_col1; 
        
        do{ //generate a new random bait
            valid_random=1;
            rand_x=rand()%10;
            rand_y= rand()%10;
            for(int i=0; i<*length; i++){
                if(((*snake)[i].row==rand_x && (*snake)[i].col==rand_y)){
                    valid_random=0;
                }
            }
        }
        while(valid_random==0 || board[rand_x][rand_y][0].type=='o');
        board[rand_x][rand_y][0].type='b';
        break;
}
//count number of obstacles in the board
for(int i=0; i<10; i++){
    for(int j=0; j<10; j++){
        if(board[i][j][0].type=='o'){
            obstacle_counter++;
        }
    }
}
srand(time(NULL));
//generate obstacle in every 5 moves. (max 3 obstacle in the board)
if(move_number>4 && move_number%5==0 && obstacle_counter<3){
    do{
        valid_random=1;
        rand_x=rand()%10;
        rand_y= rand()%10;
        for(int i=0; i<*length; i++){
            if(((*snake)[i].row==rand_x && (*snake)[i].col==rand_y)){
                valid_random=0;
            }
        }
    }
    while(valid_random==0 || board[rand_x][rand_y][0].type=='b');
    if(board[rand_x][rand_y][0].type=='o'){ //if there is obstacle, increase the value and realloc snake
        board[rand_x][rand_y][0].value++;
        board[rand_x][rand_y] = (block *)realloc(board[rand_x][rand_y], (board[rand_x][rand_y][0].value));
    }
    else{ //create the new obstacle
        board[rand_x][rand_y][0].type='o';
        board[rand_x][rand_y][0].value=1;
    }
}

}

