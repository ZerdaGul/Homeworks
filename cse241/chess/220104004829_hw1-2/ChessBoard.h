#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

enum PieceType { KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN }; //types of pieces
enum PieceColor { WHITE, BLACK }; //colors
const char EMPTY= '.'; //for empty spaces on the board
const int ROW=8;
const int COL=8;

class Pieces {
private:
    int x;
    int y;
    PieceType type;
    PieceColor color;
    char character;

public:
    Pieces(int row=100, int col=100, PieceType t=KING, PieceColor c=WHITE);//100 is for temp pieces
    Pieces(const Pieces &p);//copy constructor
    Pieces& operator=(const Pieces& p);
    int getX() const { return x; };
    int getY() const { return y; };
    PieceType getType() const { return type; };
    char getCharacter() const { return character; }
    PieceColor getColor() const { return color; };
    void setX(int row) { x = row; };
    void setY(int col) { y = col; };
    void setType(PieceType t) { type = t; };
    void setCharacter(char c) { character = c; };
    void setColor(PieceColor c) { color = c; };
    ~Pieces(){/*intentionally empty*/};
};

class ChessBoard {
private:
    vector<Pieces> white;  //keep white pieces
    vector<Pieces> black; //keep black pieces
    vector<vector<char>> board; // keep characters on the board
    int whitePoint;
    int blackPoint;
    void setWhitePoint(int point){whitePoint=point;};
    void setBlackPoint(int point){blackPoint=point;};
    void updateBoard();
    bool checkMove(const Pieces &p,int currentRow, int currentCol, int nextRow, int nextCol)const;
    bool isUnderAttack(const Pieces &p)const;
    bool isUnderAttackbyRook(const Pieces &p, const Pieces &attacker)const;
    bool isUnderAttackbyBishop(const Pieces &p, const Pieces &attacker)const;
    int checkPoint(const Pieces &foundP, const Pieces& changedP);
    bool isPieceExist(int nextRow,int nextCol,Pieces &p)const;
    bool checkMoveforRook(const Pieces &p,int currentRow, int currentCol, int nextRow, int nextCol)const;
    bool checkMoveforBishop(const Pieces &p,int currentRow, int currentCol, int nextRow, int nextCol)const;
    int getWhitePoint()const{return whitePoint;};
    int getBlackPoint()const{return blackPoint;};
public:
    ChessBoard();
    ChessBoard(const ChessBoard& c);
    ChessBoard& operator=(const ChessBoard& c);
    vector<Pieces> getWhite()const{return white;};
    vector<Pieces> getBlack()const{return black;}; 
    vector<vector<char>> getBoard()const{return board;};  
    void printBoard()const;
    bool makeMove(string move, PieceColor color);
    string nextMove(PieceColor Color);
    bool CheckMate(const PieceColor &color);
    void saveFile()const;
    void score()const;
    ~ChessBoard(){/*intentionally empty*/};
};



#endif
