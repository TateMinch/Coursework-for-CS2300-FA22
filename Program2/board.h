#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

class Board{
public:
    Board();
    Board(string file);
private:
    ifstream infile;
    char** mat;
    int n, k, p1Cells, p2Cells;
    bool gameOver, p1InvalidMove, p2InvalidMove;
    vector< pair<pair<int,int>,
            pair<int,int> > > moves;
    vector<double> slopeList;

    //control method
    void playGame(bool isManual);
    //generate and print board
    void generateBoard(int n);
    void printBoard();
    //accepts input from file for play
    void readFile();
    //displays board during active game
    void displayBoard(pair<pair<int,int>, pair<int, int> > move, int i);
    //frees dynamically allocated memory
    void freeMemory();
    //confirms move is valid
    bool isValid(pair<pair<int,int>, pair<int,int> > move, int i);
    //flips cells and calculates score
    void flipCells(pair<pair<int,int>, pair<int,int> > move, int i);
    //displays board at complete game
    void displayBoardEnd();
};
#endif