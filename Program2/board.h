#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Board{
public:
    Board();
    Board(string file);
private:
    ifstream infile;
    char** mat;
    int n, k, p1Cells, p2Cells;
    bool gameOver;
    vector< pair<pair<int,int>,
            pair<int,int> > > moves;
    vector<double> slopeList;

    //control method
    void playGame(bool isManual);
    void generateBoard(int n);
    void printBoard();
    //accepts input from file for play
    void readFile();
    //displays board during active game
    void displayBoard(pair<pair<int,int>, pair<int, int> > move);
    //frees dynamically allocated memory
    void freeMemory();
    //confirms move is valid
    bool isValid(pair<pair<int,int>, pair<int,int> > move);
    //flips cells and calculates score
    void flipCells(pair<pair<int,int>, pair<int,int> > move, int i);
    //displays board at complete game
    void displayBoardEnd();
    // void computeScore();
};
#endif