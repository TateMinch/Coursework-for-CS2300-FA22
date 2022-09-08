/*
* Name: Tate Minch
* Date: 7 September, 2022
* Assignment: CS2300 Programming Assignment 1
*/

#include "functions.h"

int main(){
    //populate the 5 matrices
    int** mat1 = populateMatrix(1,1,FIRST_LETTERS, LAST_LETTERS, true);
    int** mat2 = populateMatrix(4,2,LAST_LETTERS,FIRST_LETTERS, true);
    double** mat3 = populateMatrix(0.3,0.1,LAST_LETTERS,FIRST_LETTERS,false);
    int** mat4 = populateMatrix(3, 3, 9, 11, true);
    double** mat5 = populateMatrix(-5.0, 1.5, 9, 11, false);

    //write the matrices out to a file
    writeMatrix("tMinch_mat1.txt",mat1, FIRST_LETTERS, LAST_LETTERS);
    writeMatrix("tMinch_mat2.txt", mat2, LAST_LETTERS, FIRST_LETTERS);
    writeMatrix("tMinch_mat3.txt", mat3, LAST_LETTERS, FIRST_LETTERS);
    writeMatrix("tMinch_mat4.txt", mat4, 9, 11);
    writeMatrix("tMinch_mat5.txt", mat5, 9, 11);
    
    //free dynamically allocated memory
    freeMemory(mat1, FIRST_LETTERS);
    freeMemory(mat2, LAST_LETTERS);
    freeMemory(mat3, LAST_LETTERS);
    freeMemory(mat4, 9);
    freeMemory(mat5, 9);

    return 0;
}