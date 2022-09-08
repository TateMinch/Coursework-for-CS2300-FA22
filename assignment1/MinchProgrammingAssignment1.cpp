/*
* Name: Tate Minch
* Date: 7 September, 2022
* Assignment: CS2300 Programming Assignment 1
*/

#include "functions.h"

int main(){
    const int FIRST_LETTERS = 4;
    const int LAST_LETTERS = 5;

    int** mat1 = populateMatrix(1,1,FIRST_LETTERS, LAST_LETTERS, false);
    int** mat2 = populateMatrix(4,2,LAST_LETTERS,FIRST_LETTERS, false);
    double** mat3 = populateMatrix(0.3,0.1,LAST_LETTERS,FIRST_LETTERS,true);
    int** mat4 = populateMatrix(3, 3, 9, 11, false);
    double** mat5 = populateMatrix(-5.0, 1.5, 9, 11, true);

    writeMatrix("tMinch_mat1.txt",mat1, FIRST_LETTERS, LAST_LETTERS);
    writeMatrix("tMinch_mat2.txt", mat2, LAST_LETTERS, FIRST_LETTERS);
    writeMatrix("tMinch_mat3.txt", mat3, LAST_LETTERS, FIRST_LETTERS);
    writeMatrix("tMinch_mat4.txt", mat4, 9, 11);
    writeMatrix("tMinch_mat4.txt", mat5, 9, 11);

    
    freeMemory(mat1, FIRST_LETTERS);
    freeMemory(mat2, LAST_LETTERS);
    freeMemory(mat3, LAST_LETTERS);
    freeMemory(mat4, 9);
    freeMemory(mat5, 9);

    return 0;
}