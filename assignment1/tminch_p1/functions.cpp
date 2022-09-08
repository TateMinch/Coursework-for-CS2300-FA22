#include "functions.h"
/*
* populateMatrix function with overloaded parameter type. Takes in starting value, 
* amount to increment by, rows, cols, and a boolean indicating what order to iterate in.
*/
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

/*
* populateMatrix function with overloaded parameter type. Takes in starting value, 
* amount to increment by, rows, cols, and a boolean indicating what order to iterate in.
*/
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

/*
* Function to free dynamically allocated memory. Overloaded input type to deal with ints
* and doubles.
*/
void freeMemory(int** mat, int numRows){
    for(int i = 0; i < numRows; i++)
        delete[] mat[i];
    delete[] mat;
}

/*
* Function to free dynamically allocated memory. Overloaded input type to deal with ints
* and doubles.
*/
void freeMemory(double** mat, int numRows){
    for(int i = 0; i < numRows; i++)
        delete[] mat[i];
    delete[] mat;
}

/*
* Takes in filename, 2d array, num of rows, and num of cols, and writes
* out the contents of the 2d array to the specified file. Overloaded operator
* to deal with ints and doubles.
*/
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

/*
* Takes in filename, 2d array, num of rows, and num of cols, and writes
* out the contents of the 2d array to the specified file. Overloaded operator
* to deal with ints and doubles.
*/
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