#include "functions.h"
int** populateMatrix(int count, int incrementAmount, int rows, int cols, bool colsFirst){    
    int** mat = new int*[rows];
    for(int i = 0; i < rows; i++)
        mat[i] = new int[cols];
    if(colsFirst){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++, count += incrementAmount)
                mat[i][j] = count;
        }
    }
    else{
        for(int i = 0; i < cols; i++){
            for(int j = 0; j < rows; j++, count += incrementAmount)
                mat[j][i] = count;
        }
    }
    return mat;
}

double** populateMatrix(double count, double incrementAmount, int rows, int cols, bool colsFirst){
    double** mat = new double*[rows];
    for(int i = 0; i < rows; i++)
        mat[i] = new double[cols];
    if(colsFirst){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++, count += incrementAmount)
                mat[i][j] = count;
        }
    }
    else{
        for(int i = 0; i < cols; i++){
            for(int j = 0; j < rows; j++, count += incrementAmount)
                mat[j][i] = count;
        }
    }
    return mat;
}

void freeMemory(int** mat, int numRows){
    for(int i = 0; i < numRows; i++)
        delete[] mat[i];
    delete[] mat;
}

void freeMemory(double** mat, int numRows){
    for(int i = 0; i < numRows; i++)
        delete[] mat[i];
    delete[] mat;
}

void writeMatrix(string filename, int** mat, int numRows, int numCols){
    ofstream myfile;
    myfile.open(filename);
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++)
            myfile << mat[i][j] << " ";
        myfile << "\n";
    }
    myfile.close();
}

void writeMatrix(string filename, double** mat, int numRows, int numCols){
    ofstream myfile;
    myfile.open(filename);
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++)
            myfile << mat[i][j] << " ";
        myfile << "\n";
    }
    myfile.close();
}