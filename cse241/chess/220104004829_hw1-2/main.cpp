#include "ChessBoard.h"

using namespace std;


int main(){

ChessBoard chess; //generate the object
string input;
int flag=false;
int turn=2;
PieceColor pColor=WHITE, rivalC=BLACK;
bool checkMateFlag=false;
string nextMoveStr;

cout <<"Welcome to the Chess Game!\n"<<endl;
chess.printBoard();

do{
    flag=false;
    if(turn%2==0){
        cout << "[White's Turn]"<<endl;
        pColor=WHITE;
        rivalC=BLACK;
    } 
    else{
        cout << "[Black's Turn]"<<endl;
        pColor=BLACK;
        rivalC=WHITE;
    }
    while(!flag){
        cout <<"Enter your move: "<<endl;
        getline(cin, input);
        if(input=="suggest"){
            nextMoveStr= chess.nextMove(pColor);
            cout << "Suggestion is "<<nextMoveStr<<endl;
            chess.printBoard();
            flag=true;
        }else{
            flag=chess.makeMove(input, pColor);
            if(flag==true){
                cout << "\n[Updated Board]"<<endl;
                chess.printBoard();
            }
        }
    }
    chess.saveFile();
    turn++;
    checkMateFlag= chess.CheckMate(rivalC);
}while(!checkMateFlag); //if check mate happened game is over

if(pColor==BLACK){
    cout<< "Black Player Won!"<<endl;
}
else{
    cout<< "White Player Won!"<<endl;
}
chess.score();

return 0;
}


