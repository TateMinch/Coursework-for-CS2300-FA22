#include <iostream>
#include <fstream>

using namespace std;

int** populateMatrix(int count, int incrementAmount, int rows, int cols, bool rowsFirst);
double** populateMatrix(double count, double incrementAmount, int rows, int cols, bool rowsFirst);
void freeMemory(int** mat, int numRows);
void freeMemory(double** mat, int numRows);
void writeMatrix(string filename, int** mat, int numRows, int numCols);
void writeMatrix(string filename, double** mat, int numRows, int numCols);