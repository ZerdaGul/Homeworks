#include "ChessBoard.h"


Pieces::Pieces(const Pieces &p){ //copy constructor
    x=p.getX();
    y=p.getY();
    type=p.getType();
    color=p.getColor();
    character=p.getCharacter();
}

Pieces::Pieces(int row, int col, PieceType t, PieceColor c) {
    x = row;
    y = col;
    type = t;
    color = c;
    switch (type) { //according to the type and color select the correct character for the piece
        case KING:
            character = 'k';
            if (color == WHITE) character -= 32;
            break;
        case QUEEN:
            character = 'q';
            if (color == WHITE) character -= 32;
            break;
        case ROOK:
            character = 'r';
            if (color == WHITE) character -= 32;
            break;
        case KNIGHT:
            character = 'n';
            if (color == WHITE) character -= 32;
            break;
        case BISHOP:
            character = 'b';
            if (color == WHITE) character -= 32;
            break;
        case PAWN:
            character = 'p';
            if (color == WHITE) character -= 32;
            break;
        default:
            break;
    }
}

Pieces& Pieces::operator=(const Pieces& p){ //assignment operator
    if(this!=&p){
        x= p.x;
        y=p.y;
        type=p.type;
        color=p.color;
        character=p.character;
    }
    return *this;
}

ChessBoard::ChessBoard(const ChessBoard& c){ //copy constructor
    white.reserve(16);
    black.reserve(16);
    board.resize(ROW, vector<char>(COL, EMPTY));

    for(int i=0; i<c.white.size();i++){
        white[i]= c.white[i];
    }
    for(int i=0; i<c.black.size();i++){
        black[i]= c.black[i];
    }

    for(int i=0; i< ROW; i++){
        for(int j=0; j<COL; j++){
            board[i][j]= c.board[i][j];
        }
    }
    whitePoint=c.whitePoint;
    blackPoint=c.blackPoint;

}

ChessBoard& ChessBoard::operator=(const ChessBoard& c){ //assignment operator

    if(this!=&c){
        white.reserve(16);
        black.reserve(16);
        board.resize(ROW, vector<char>(COL, EMPTY));

        for(int i=0; i<c.white.size();i++){
            white[i]= c.white[i];
        }
        for(int i=0; i<c.black.size();i++){
            black[i]= c.black[i];
        }

        for(int i=0; i< ROW; i++){
            for(int j=0; j<COL; j++){
                board[i][j]= c.board[i][j];
            }
        }
        whitePoint=c.whitePoint;
        blackPoint=c.blackPoint;
    }
    return *this;

}



ChessBoard::ChessBoard(){ //initialize the chess

    whitePoint=0;
    blackPoint=0;
    black.reserve(16); //take 16 Pieces place for black pieces
    white.reserve(16); //take 16 Pieces place for white pieces
    board.resize(ROW, vector<char>(COL, EMPTY)); //take ROW*COL char places for the pieces on the board
    //generate the pieces
    Pieces r1(0,0,ROOK, BLACK), r2(0,7,ROOK, BLACK), n1(0,1, KNIGHT, BLACK), n2(0,6, KNIGHT, BLACK);
    Pieces b1(0,2, BISHOP, BLACK), b2(0,5,BISHOP, BLACK), q(0,3, QUEEN, BLACK), k(0,4, KING, BLACK);
    Pieces p1(1,0, PAWN, BLACK),p2(1,1, PAWN, BLACK),p3(1,2, PAWN, BLACK),p4(1,3, PAWN, BLACK),p5(1,4, PAWN, BLACK),p6(1,5, PAWN, BLACK),p7(1,6, PAWN, BLACK),p8(1,7, PAWN, BLACK);
    black= {r1,r2,n1,n2,b1,b2,q,k,p1,p2,p3,p4,p5,p6,p7,p8};

    Pieces R1(7,0,ROOK, WHITE), R2(7,7,ROOK, WHITE), N1(7,1, KNIGHT, WHITE), N2(7,6, KNIGHT, WHITE);
    Pieces B1(7,2, BISHOP, WHITE), B2(7,5,BISHOP, WHITE), Q(7,3, QUEEN, WHITE), K(7,4, KING, WHITE);
    Pieces P1(6,0, PAWN, WHITE), P2(6,1, PAWN, WHITE), P3(6,2, PAWN, WHITE), P4(6,3, PAWN, WHITE), P5(6,4, PAWN, WHITE), P6(6,5, PAWN, WHITE), P7(6,6, PAWN, WHITE), P8(6,7, PAWN, WHITE);
    white= {R1,R2,N1,N2,B1,B2,Q,K,P1,P2,P3,P4,P5,P6,P7,P8};
    //accomodate the pieces on the board
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            for (int p = 0; p < 16; p++) {
                if (black[p].getX() == i && black[p].getY() == j) {
                    board[i][j] = black[p].getCharacter();
                }
                else if (white[p].getX() == i && white[p].getY() == j) {
                    board[i][j] = white[p].getCharacter();
                }
            }
        }
    }
}

void ChessBoard::printBoard() const { //show board in the terminal
    for (int i = 0; i < ROW; i++) {
        cout << ROW-i <<"  |";
        for (int j = 0; j < COL; j++) {
            cout << "  " << board[i][j];
        }
        cout << endl;
    }
    cout << "      ----------------------- \n      a  b  c  d  e  f  g  h\n"<< endl;
}

bool ChessBoard::makeMove(string move, PieceColor color){ //make move
    bool checkMoveFlag=false;
    bool isErased=false;
    Pieces foundP;
    int a;
    int b;
    int i=0, y=0;
    bool notExist=true;
    //check whether input has 2 letter 2 number which is between a-h and 1-8
    if(move.length()!=4){
        cout << "valid input size!\n";
        return false;
    }
    if((move[0]<97 || move[0]>104) || (move[1]<49 || move[1]>56) || (move[2]<97 || move[2]>104) || (move[3]<49 || move[3]>56)){
        cout << "valid input content.\n";
        return false;
    }
    if(move[0]==move[2] && move[1]==move[3]){
        cout << "valid input content.\n";
        return false;
    }
    //convert move input to row and column index
    int currentCol= move[0]-'a'; //get the array column
    int currentRow= ROW-(move[1]-'0'); //get the array row
    int nextCol=move[2]-'a'; //get the array column
    int nextRow= ROW-(move[3]-'0'); //get the array row
    

    if(color==WHITE){
        for(i=0; i<white.size();i++){
            if(white[i].getX()== currentRow && white[i].getY()==currentCol){
                notExist=false; // if there a piece at the coordinate
                //check if move is legal
                checkMoveFlag=checkMove(white[i], currentRow, currentCol, nextRow, nextCol);
                if(checkMoveFlag){
                    if(isPieceExist(nextRow, nextCol, foundP)){
                        //if a piece is eaten delete it 
                        for(a=0; a<black.size(); a++){
                            if(black[a].getX()==foundP.getX() && black[a].getY()==foundP.getY()){
                                black.erase(black.begin() + a);
                                isErased=true;
                                break;
                            }
                        }
                    }
                    //update the coordinates
                    white[i].setX(nextRow);
                    white[i].setY(nextCol);
                    break;
                }
                else{
                    return false; //return false if move is not legal
                }
            }
        }

    }
    else{ // do the same things if piece is black
        for(i=0; i<black.size(); i++){
            if(black[i].getX()== currentRow && black[i].getY()==currentCol){
                notExist=false;// if there a piece at the coordinate
                checkMoveFlag=checkMove(black[i],currentRow, currentCol, nextRow, nextCol);
                if(checkMoveFlag){
                    if(isPieceExist(nextRow, nextCol, foundP)){
                        for(a=0; a<white.size(); a++){
                            if(white[a].getX()==foundP.getX() && white[a].getY()==foundP.getY()){
                                white.erase(white.begin() + a);
                                isErased=true;
                                break;
                            }
                        }
                    }
                    black[i].setX(nextRow);
                    black[i].setY(nextCol);
                    break;
                }
                else{
                    return false;
                }
            }
        }
    }

    if(notExist)return false; // if there is no piece at the coordinate return false

    updateBoard(); //update the chess board

    if(color==WHITE){
        for(b=0; b<white.size();b++){
            if(white[b].getType()==KING){
                if(isUnderAttack(white[b])){ // if KING is under attack undo the move 
                    white[i].setX(currentRow);
                    white[i].setY(currentCol);
                    if(isErased){ // if a piece is deleted re-upload it
                        black.push_back(foundP);
                    }
                    updateBoard();
                    return false;
                }
            }
        }
    }
    else{ //do the same things for black piece
        for(b=0; b<black.size();b++){
            if(black[b].getType()==KING){
                if(isUnderAttack(black[b])){
                    black[i].setX(currentRow);
                    black[i].setY(currentCol);
                    if(isErased){
                        white.push_back(foundP);
                    }
                    updateBoard();
                    return false;
                }
            }
        }
    }

    if(color==WHITE){ //update point
        checkPoint(foundP, white[i]);
    }
    else{ // update point
        checkPoint(foundP,black[i]);
    }
    return true; //move is suscessful
}

void ChessBoard::updateBoard(){ //update the coordinates of the pieces in the board
int flag;
for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
        flag=0;
        for(int a=0; a<black.size();a++){
            if (black[a].getX() == i && black[a].getY() == j) {
                board[i][j] = black[a].getCharacter(); //update the black pieces
                flag=1;
                break;
            }    
        }
        for (int a = 0; a < white.size(); a++) {
            if (white[a].getX() == i && white[a].getY() == j) {
                board[i][j] = white[a].getCharacter(); //update the white pieces
                flag=1;
                break;
            }
        }
        if(flag==0) board[i][j]= EMPTY; //if there is no piece, it is EMPTY='.'
    }
}
}

bool ChessBoard::checkMoveforRook(const Pieces &p,int currentRow, int currentCol, int nextRow, int nextCol)const{
//check if move is valid for rook
int i;
Pieces foundP; //the piece which is in the coordinates of the next position of current piece

if((currentRow==nextRow || currentCol==nextCol)){ //check x and y axes
    if(currentCol<nextCol){ //check x axis
        for(i=currentCol+1; i<nextCol; i++){
            if(isPieceExist(nextRow, i, foundP)){ //if there is another piece in the path return false
                return false;
            }
        }
    }
    else if(currentCol>nextCol){
        for(i=currentCol-1; i>nextCol; i--){
            if(isPieceExist(nextRow, i,foundP)){ //if there is another piece in the path return false
                return false;
            }
        }
    }
    else if(currentRow<nextRow){ //check y axis
        for(i=currentRow+1; i<nextRow; i++){
            if(isPieceExist(i, nextCol,foundP)){//if there is another piece in the path return false
                return false;
            }
        }
    }
    else if(currentRow>nextRow){
        for(i=currentRow-1; i>nextRow; i--){
            if(isPieceExist(i, nextCol,foundP)){//if there is another piece in the path return false
                return false;
            }
        }
    }
    if(isPieceExist(nextRow, nextCol,foundP) && foundP.getColor()!= p.getColor()){
        return true; //if rook is going to eat a piece, it should be opposite color
    }
    else if(!(isPieceExist(nextRow, nextCol,foundP))){
        return true; //if rook is not going to eat piece return true
    }
    return false; //return false otherwise
}
return false;

}

bool ChessBoard::checkMoveforBishop(const Pieces &p,int currentRow, int currentCol, int nextRow, int nextCol)const{
//check if move is valid for bishop
Pieces foundP; //the piece which is in the coordinates of the next position of current piece
int i=0, j=0;

if(abs(currentRow-nextRow)==abs(currentCol-nextCol)){ // if difference of x and y is equal move is cross
    if(currentRow>nextRow){
        if(currentCol>nextCol){ //left-up
            for(i=currentRow-1, j=currentCol-1; i>nextRow; i--, j--){
                if(isPieceExist(i, j,foundP)){//if there is another piece in the path return false
                    return false;
                }
            }
        }
        else{ //rigth-up
            for(i=currentRow-1, j=currentCol+1; i>nextRow; i--, j++){
                if(isPieceExist(i, j,foundP)){//if there is another piece in the path return false
                    return false;
                }
            }
        }
    }
    else{ 
        if(currentCol>nextCol){//right-bottom
            for(i=currentRow+1, j=currentCol-1; i<nextRow; i++, j--){//if there is another piece in the path return false
                if(isPieceExist(i, j,foundP)){
                    return false;
                }
            }
        }
        else{//left-bottom
            for(i=currentRow+1, j=currentCol+1; i<nextRow; i++, j++){//if there is another piece in the path return false
                if(isPieceExist(i, j,foundP)){
                    return false;
                }
            }
        }
    }
    //if there is piece at the target position it should be oppsite color
    //if there is no piece at target return true also otherwise return false
    if(isPieceExist(nextRow, nextCol,foundP) && foundP.getColor()!=p.getColor()) return true;
    else if(!(isPieceExist(nextRow, nextCol,foundP))) return true;
    return false;
}
return false;
}

bool ChessBoard::checkMove(const Pieces &p,int currentRow, int currentCol, int nextRow, int nextCol)const{
//check move for the specific types
bool flag=false;
Pieces foundP;// piece in the target position
double distance=0;
int i,j;
switch (p.getType())
{
case QUEEN:
    return (checkMoveforRook(p,currentRow,currentCol,nextRow,nextCol) || checkMoveforBishop(p,currentRow,currentCol,nextRow,nextCol));
case KING:
    distance=sqrt(pow((currentRow-nextRow),2)+pow(currentCol-nextCol,2));//check the distance
    if((abs(currentRow-nextRow)+ abs(currentCol-nextCol)==1) || distance==sqrt(2)){
        if(!(isPieceExist(nextRow, nextCol, foundP))){ //if there is no piece return true
            return true;
        }
        else if(isPieceExist(nextRow, nextCol, foundP)){ //if there is piece it should be opposite color
            if(foundP.getColor()!=p.getColor())return true;
            else return false;
        }
    }
    return false;
case ROOK:
    return checkMoveforRook(p,currentRow,currentCol,nextRow,nextCol);
case KNIGHT:
    distance= sqrt(pow((currentRow-nextRow),2)+pow(currentCol-nextCol,2));
    if(distance==sqrt(5)){ //the distance should be sqrt(2*2+1*1)
        if(isPieceExist(nextRow, nextCol,foundP) && foundP.getColor()!=p.getColor()) return true;
        else if(!(isPieceExist(nextRow, nextCol,foundP))) return true;
    }
    return false;
case BISHOP:
    return checkMoveforBishop(p,currentRow,currentCol,nextRow,nextCol);
case PAWN:
    if(p.getColor()==WHITE){ 
        if(currentRow==nextRow+2 && currentCol==nextCol){ //if want to go 2 square
            if(isPieceExist(nextRow, nextCol,foundP)) return false;
            if(!(p.getX()==6)){ //check if current position
                return false; // eğer ilk konumunda değilken 2 adım gitmeye çalışırsa
            }
            return true;
        }
        if(currentRow==nextRow+1 && (currentCol==nextCol-1 || currentCol==nextCol+1)){
            if(isPieceExist(nextRow, nextCol,foundP) && foundP.getColor()==BLACK){
                //if move is cross and there is opposite color piece at the position
                return true;
            }
            return false; //eğer çapraz yaptığı yerde siyah taş yoksa return false
        }
        if((currentRow==(nextRow+1)) && (currentCol==nextCol)){ //if want to go 1 square 
            if(isPieceExist(nextRow, nextCol,foundP)) return false;
            else return true;
        }
    }
    else{ // do the same things for black piece
        if(currentRow==nextRow-2 && currentCol==nextCol){
            if(isPieceExist(nextRow, nextCol,foundP)) return false;
            if(!(p.getX()==1)){
                return false; // eğer ilk konumunda değilken 2 adım gitmeye çalışırsa
            }
            return true;
        }
        if(currentRow==nextRow-1 && (currentCol==nextCol-1 || currentCol==nextCol+1)){
            if(isPieceExist(nextRow, nextCol,foundP) && foundP.getColor()==WHITE){
                //eğer çapraz yapıp beyaz taş yerse
                return true;
            }
            return false; //eğer çapraz yaptığı yerde beyaz taş yoksa return false
        }
        if((currentRow==nextRow-1) && (currentCol==nextCol)){
            if(isPieceExist(nextRow, nextCol,foundP)) return false;
            else return true;
        }
    }
    return false; //other cases
}
return false;
}

bool ChessBoard::isPieceExist(int nextRow,int nextCol, Pieces &foundP)const{

    for(int i=0; i<black.size(); i++){
        if(black[i].getX()==nextRow && black[i].getY()==nextCol){
            foundP=Pieces(black[i]); //founded piece
            return true; //if there is a black piece in the target position return true
        }
    }
    for(int i=0; i<white.size(); i++){
        if(white[i].getX()==nextRow && white[i].getY()==nextCol){
            foundP=Pieces(white[i]); //founded piece
            return true; //if there is a white piece in the target position return true
        }
    }
    return false; //if there is no piece in the target
}

bool ChessBoard::isUnderAttack(const Pieces &p)const{ //check if piece is under attack
Pieces attacker; //attacker piece
int size;
double distance=0;
bool flag=false;
if(p.getColor()==WHITE)size=black.size(); //select the size according to the color
else size=white.size();
for(int i=0; i<size; i++){
    flag=false; // if under attack becomes true
    if(p.getColor()==WHITE)attacker=Pieces(black[i]); //choose the opposite color piece
    else attacker=Pieces(white[i]);
    switch (attacker.getType()) //check whether piece is attacker or not
    {
    case QUEEN:
        flag=(isUnderAttackbyBishop(p, attacker) || isUnderAttackbyRook(p, attacker));
        break;
    case KING: //distance should be 1 or sqrt(1+1)
        distance = sqrt(pow(p.getX()-attacker.getX(),2)+pow(p.getY()-attacker.getY(),2));
        if(distance==sqrt(2) || distance==sqrt(1))flag=true;
        else flag=false; 
        break;
    case ROOK:
        flag= isUnderAttackbyRook(p, attacker);
        break;
    case KNIGHT://distance should be sqrt(2*2+1*1)
        distance = sqrt(pow(p.getX()-attacker.getX(),2)+pow(p.getY()-attacker.getY(),2));
        if(distance==sqrt(5))flag=true;
        else flag=false;
        break;
    case BISHOP:
        flag=isUnderAttackbyBishop(p, attacker);
        break;
    case PAWN:
        if(p.getColor()==WHITE){//at the cross
            if(attacker.getX()==p.getX()-1 && abs(attacker.getY()-p.getY())==1)flag=true;
            else flag=false;
        }
        else{
            if(attacker.getX()==p.getX()+1 && abs(attacker.getY()-p.getY())==1)flag=true;
            else flag=false;
        }
        break;
    }
    if(flag==true)return true; //return true if piece is under attack
}
return false;
}

bool ChessBoard::isUnderAttackbyBishop(const Pieces &p, const Pieces &attacker)const{
//check if piece is under attack of bishop
int i=0, j=0;
Pieces foundP;
if(abs(p.getX()-attacker.getX())==abs(p.getY()-attacker.getY())){ // x and y differences is equal when move is cross
    if(p.getX()>attacker.getX()){
        if(p.getY()>attacker.getY()){ //attacker is left-up of piece
            for(i=p.getX()-1, j=p.getY()-1; i>attacker.getX(); i--, j--){
                if(isPieceExist(i, j,foundP)){ //check if there is another piece int the path
                    return false;
                }
            }
        }
        else{ //rigth-up
            for(i=p.getX()-1, j=p.getY()+1; i>attacker.getX(); i--, j++){
                if(isPieceExist(i, j,foundP)){
                    return false;
                }
            }
        }
    }
    else{ 
        if(p.getY()>attacker.getY()){//left-bottom
            for(i=p.getX()+1, j=p.getY()-1; i<attacker.getX(); i++, j--){ 
                if(isPieceExist(i, j,foundP)){
                    return false;
                }
            }
        }
        else{//right-bottom
            for(i=p.getX()+1, j=p.getY()+1; i<attacker.getX(); i++, j++){
                if(isPieceExist(i, j,foundP)){
                    return false;
                }
            }
        }
    }
    return true; //return true if there is no piece in path 
}
return false;
}


bool ChessBoard::isUnderAttackbyRook(const Pieces &p, const Pieces &attacker)const{
//check if piece is under attack of rook
int i;
Pieces foundP;
if(p.getX()==attacker.getX()|| p.getY()==attacker.getY()){ // x or y axis should be same
    if(p.getY()<attacker.getY()){ //rook is in the right
        for(i=p.getY()+1; i<attacker.getY(); i++){
            if(isPieceExist(attacker.getX(), i, foundP)){ //check if there is another piece in the path
                return false;
            }
        }
    }
    else if(p.getY()>attacker.getY()){ //rook is the left
        for(i=p.getY()-1; i>attacker.getY(); i--){
            if(isPieceExist(attacker.getX(), i,foundP)){//check if there is another piece in the path
                return false;
            }
        }
    }
    else if(p.getX()<attacker.getX()){ //rook is in the bottom
        for(i=p.getX()+1; i<attacker.getX(); i++){
            if(isPieceExist(i, attacker.getY(),foundP)){//check if there is another piece in the path
                return false;
            }
        }
    }
    else if(p.getX()>attacker.getX()){//rook is in the abowe
        for(i=p.getX()-1; i>attacker.getX(); i--){
            if(isPieceExist(i, attacker.getY(),foundP)){//check if there is another piece in the path
                return false;
            }
        }
    }
    return true;//if there is no any piece between the two pieces return true
}
return false;
}


bool ChessBoard::CheckMate(const PieceColor &color){
//check mate
int size;
double distance=0;
int i=0,a=0;
bool isErased=false;
bool checkMoveFlag; //if move is valid or not
Pieces foundP;
int currentRow,currentCol,nextRow,nextCol;
bool stillAttacked=true; //after the move if king is still in danger
int m=0,n=0;

if(color==WHITE)size=white.size();
else size=black.size();

//move every pieces each by one end if king is still under attack then check mate
for(i=0 ;i<size;i++){
    if(color==WHITE){
        if(white[i].getType()==KING){ 
            if(isUnderAttack(white[i])){ //if KING is under attack do 'check mate' control 
                for(m=0;m<size;m++){ //check for every piece in vector
                    currentRow= white[m].getX();
                    currentCol= white[m].getY();
                    for(nextRow=0; nextRow<ROW; nextRow++){//check for every square in board
                        for(nextCol=0; nextCol<COL; nextCol++){
                            if(!(currentRow==nextRow && currentCol==nextCol)){ //dont try to go same position
                                //try to make piece goes to every square in the board
                                checkMoveFlag=checkMove(white[m], currentRow,currentCol, nextRow, nextCol);
                                if(checkMoveFlag){ //if move is valid do it
                                    isErased=false;
                                    stillAttacked=true;
                                    if(isPieceExist(nextRow, nextCol, foundP)){
                                        for(a=0; a<black.size(); a++){ // if there is piece in target delete it
                                            if(black[a].getX()==foundP.getX() && black[a].getY()==foundP.getY()){
                                                black.erase(black.begin() + a);
                                                isErased=true;
                                                break;
                                            }
                                        }
                                    }
                                    white[m].setX(nextRow);
                                    white[m].setY(nextCol);
                                    updateBoard();
                                    if(!isUnderAttack(white[i]))stillAttacked=false;
                                    //undo the move
                                    white[m].setX(currentRow);
                                    white[m].setY(currentCol);
                                    if(isErased){ //reload if a piece is eaten
                                        black.push_back(foundP);
                                    }
                                    updateBoard();
                                    if(stillAttacked==false) return false;
                                }
                            }

                        }
                    }
                }
            }
            else{ //if KING is not under attack the check mate is not correct
                return false;
            }
            break;
        }
    }
    else{ //do the same things for black pieces
        if(black[i].getType()==KING){
            if(isUnderAttack(black[i])){
                for(m=0;m<size ;m++){
                    currentRow= black[m].getX();
                    currentCol= black[m].getY();
                    for(nextRow=0; nextRow<ROW; nextRow++){
                        for(nextCol=0; nextCol<COL; nextCol++){
                            if(!(currentRow==nextRow && currentCol==nextCol)){
                                checkMoveFlag=checkMove(black[m], currentRow,currentCol, nextRow, nextCol);
                                if(checkMoveFlag){
                                    isErased=false;
                                    stillAttacked=true;
                                    if(isPieceExist(nextRow, nextCol, foundP)){
                                        for(a=0; a<white.size(); a++){
                                            if(white[a].getX()==foundP.getX() && white[a].getY()==foundP.getY()){
                                                white.erase(white.begin() + a);
                                                isErased=true;
                                                break;
                                            }
                                        }
                                    }
                                    black[m].setX(nextRow);
                                    black[m].setY(nextCol);
                                    updateBoard();
                                    if(!isUnderAttack(black[i]))stillAttacked=false;                                    
                                    black[m].setX(currentRow);
                                    black[m].setY(currentCol);
                                    if(isErased){
                                        black.push_back(foundP);
                                    }
                                    updateBoard();
                                    if(stillAttacked==false) return false;
                                }
                            }

                        }
                    }
                }
            }
            else{
                return false;
            }
            break;
        }
    }
}
return true; //if king is under attack and after every move still under attack then check mate

}

int ChessBoard::checkPoint(const Pieces &foundP, const Pieces &changedP){
//calculate the point and return the gained point
int point;
if(changedP.getColor()==WHITE)point= getWhitePoint();
else point=getBlackPoint();

if(!(foundP.getX()==100)){
    switch(foundP.getType()){
        case QUEEN:
            point=9;
            break;
        case ROOK:
            point=5;
            break;
        case KNIGHT:
            point=3;
            break;
        case BISHOP:
            point=3;
            break;
        case PAWN:
            point=1;
            break;
    }
}
if(changedP.getColor()==WHITE){
    if(isUnderAttack(changedP))point--; //if under attack -1
    setWhitePoint(getWhitePoint()+point); //update the point
}
else{
    if(isUnderAttack(changedP))point--;//if under attack -1
    setBlackPoint(getBlackPoint()+point); //update the point
}
return point; //return gained point

}


string ChessBoard::nextMove(PieceColor Color){ //suggestion
//make the highest-score suggestion for the user and implement it
int a=0,j=0,s=0,p=0;
Pieces foundP;
string move="0000";
bool isErased=false; //if any piece is deleted
int point;
int max=-20; //max point
bool endCheckMate=false; //if make the check mate it is the correct move
int currentRow, currentCol, nextRow, nextCol;
bool checkMoveFlag; //valid move
//find the KING's index in the vectors
if(Color==WHITE){
    for(s=0; s<white.size();s++){
        if(white[s].getType()==KING){
            break;
        }
    }
}else{
    for(j=0; j<black.size();j++){
        if(black[j].getType()==KING){
            break;
        }
    }
}

if(Color==WHITE){
    for(p=0;p<white.size();p++){ //check every piece
        for(int r=0; r<ROW; r++){ //for every square on the board
            for(int c=0; c<COL; c++){
                currentRow= white[p].getX();
                currentCol= white[p].getY();
                nextRow=r;
                nextCol=c;
                if(!(white[p].getX()==r && white[p].getY()==c)){ //dont stay in the same square
                    checkMoveFlag=checkMove(white[p], currentRow,currentCol, nextRow, nextCol);
                    if(checkMoveFlag){ //if move is valid do
                        isErased=false;
                        foundP= Pieces();
                        if(isPieceExist(nextRow, nextCol, foundP)){ //if there is piece in target, delete it
                            for(a=0; a<black.size(); a++){
                                if(black[a].getX()==foundP.getX() && black[a].getY()==foundP.getY()){
                                    black.erase(black.begin() + a);
                                    isErased=true;
                                    break;
                                }
                            }
                        }
                        white[p].setX(nextRow); //update coordinates
                        white[p].setY(nextCol);
                        updateBoard();
                        if(CheckMate(BLACK)){ //if check mate is happen end the loop with endCheckMate flag
                            endCheckMate=true;
                            move[0]= currentCol+'a'; //make the string of move
                            move[1]= ROW-currentRow+'0';
                            move[2]= nextCol+'a';
                            move[3]= ROW-nextRow+'0';
                            point= checkPoint(foundP, white[p]); //update point
                            setWhitePoint(getWhitePoint()-point);//puanı eski haline çevir
                            //make the move undo
                            white[p].setX(currentRow);
                            white[p].setY(currentCol);
                            if(isErased){  // if any piece is deleted, reload it
                                black.push_back(foundP);
                            }
                            updateBoard();
                        }
                        else if(CheckMate(WHITE) || ( isUnderAttack(white[s]) && !(CheckMate(BLACK)) ) ){
                            white[p].setX(currentRow); //if check mate happen for white or white king is under attack when there is black mate, undo move
                            white[p].setY(currentCol);
                            if(isErased){
                                black.push_back(foundP);
                            }
                            updateBoard();
                        }
                        else{ // calculate the point, undo move
                            point= checkPoint(foundP, white[p]);
                            if(max < point){ //if point is bigger then max save the move
                                max=point;
                                move[0]= currentCol+'a';
                                move[1]= ROW-currentRow+'0';
                                move[2]= nextCol+'a';
                                move[3]= ROW-nextRow+'0';
                            }
                            setWhitePoint(getWhitePoint()-point);//puanı eski haline çevir
                            white[p].setX(currentRow);
                            white[p].setY(currentCol);
                            if(isErased){
                                black.push_back(foundP);
                            }
                            updateBoard();
                        }
                    }
                }
                if(endCheckMate==true)break; //check mate is happen end the loop
            }
            if(endCheckMate==true)break;
        }
        if(endCheckMate==true)break;
    }
}
else{
   // do the same things for black piece
    for(p=0;p<black.size();p++){
        for(int r=0; r<ROW; r++){
            for(int c=0; c<COL; c++){
                currentRow= black[p].getX();
                currentCol= black[p].getY();
                nextRow=r;
                nextCol=c;
                if(!(black[p].getX()==r && black[p].getY()==c)){
                    checkMoveFlag=checkMove(black[p], currentRow,currentCol, nextRow, nextCol);
                    if(checkMoveFlag){
                        isErased=false;
                        foundP= Pieces();
                        if(isPieceExist(nextRow, nextCol, foundP)){
                            for(a=0; a<white.size(); a++){
                                if(white[a].getX()==foundP.getX() && white[a].getY()==foundP.getY()){
                                    white.erase(white.begin() + a);
                                    isErased=true;
                                    break;
                                }
                            }
                        }
                        black[p].setX(nextRow);
                        black[p].setY(nextCol);
                        updateBoard();
                        if(CheckMate(WHITE)){
                            endCheckMate=true;
                            move[0]= currentCol+'a';
                            move[1]= ROW-currentRow+'0';
                            move[2]= nextCol+'a';
                            move[3]= ROW-nextRow+'0';

                            black[p].setX(currentRow);
                            black[p].setY(currentCol);
                            if(isErased){
                                white.push_back(foundP);
                            }
                            updateBoard();
                        }
                        else if(CheckMate(BLACK) || ( isUnderAttack(black[j]) && !(CheckMate(WHITE)) ) ){
                            black[p].setX(currentRow);
                            black[p].setY(currentCol);
                            if(isErased){
                                white.push_back(foundP);
                            }
                            updateBoard();
                        }
                        else{
                            point= checkPoint(foundP, black[p]);
                            if(max < point){
                                max=point;
                                move[0]= currentCol+'a';
                                move[1]= ROW-currentRow+'0';
                                move[2]= nextCol+'a';
                                move[3]= ROW-nextRow+'0';
                            }
                            setBlackPoint(getBlackPoint()-point);//puanı eski haline çevir
                            black[p].setX(currentRow);
                            black[p].setY(currentCol);
                            if(isErased){
                                white.push_back(foundP);
                            }
                            updateBoard();
                        }
                    }
                }
                if(endCheckMate==true)break;
            }
            if(endCheckMate==true)break;
        }
        if(endCheckMate==true)break;
    }
}
makeMove(move, Color); //make the move
return move; //return move as a string
}

void ChessBoard::saveFile()const{
//save the board to the file
ofstream outputFile("chess.txt", ios::app);

if (!outputFile.is_open()) {
    cerr << "Error opening the file!" << endl;
}

for (int i = 0; i < ROW; i++) {
    outputFile << ROW-i <<"  |";
    for (int j = 0; j < COL; j++) {
        outputFile << "  " << board[i][j];
    }
    outputFile << endl;
}
outputFile << "      ----------------------- \n      a  b  c  d  e  f  g  h\n\n"<< endl;

// Close the file
outputFile.close();

}

void ChessBoard::score()const{
//print the scores of pieces
cout << "White point: " << getWhitePoint()<<endl;
cout << "Black point: " << getBlackPoint()<<endl;

}
