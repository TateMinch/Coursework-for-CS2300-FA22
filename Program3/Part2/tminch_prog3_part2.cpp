#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

vector<vector<double> > readMatrix(string filename){
    ifstream infile(filename);
    //error checking on file open
    if(!infile.is_open())
        throw std::invalid_argument("File failed to open or was not found");
    string myline, myline2, temp2;
    vector<double> arr;
    vector<vector<double> > result;

    while(getline(infile,myline)){
        //if there are more than 2 lines/rows
        if(result.size() > 2)
            throw invalid_argument("Matrix in file is too large! Try again!");
        for(int i = 0; i < myline.length(); i++){
            if(myline[i] == ' ' || i == myline.length() - 1){
                if(i == myline.length() - 1)
                    temp2.push_back(myline[i]);
                arr.push_back(stod(temp2));
                temp2 = "";
            }else
                temp2.push_back(myline[i]);
            //if there are more than 3 elements in a row
            if(arr.size() > 3)
                throw invalid_argument("Matrix in file is too large! Try again!");
        }
        result.push_back(arr);
        arr.clear();
    }
    //if matrix is not a 2x3
    if(result.size() != 2 || result[0].size() != 3){
        throw invalid_argument("Matrix in file is too small! Try again!");
    }
    return result;
}

int main(int argc, char *argv[]){
    //check arguments
    if(argc != 2){
        cout << "USAGE: ./<progName> <input file>\n";
        return -1;
    }
    vector<vector<double> > temp;
    try{
        //read in matrix
        temp = readMatrix(argv[1]);
    }
    //verify size
    catch(const exception& e){
        std::cerr << e.what() << '\n';
        return -1;
    }

    //populate A
    double mat[2][2];
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            mat[i][j] = temp[i][j];
        }
    }

    //calculate B and C
    double b = -mat[0][0] + -mat[1][1];
    double c = (mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]);
    if(b == 0 && c >= 0){
        cout << "No real eigenvalues." << endl;
        return 0;
    }

    //solve for eigen values
    double eigen1 = (-b + sqrt(pow(b,2) - 4 * c)) / 2;
    double eigen2 = (-b - sqrt(pow(b,2) - 4 * c)) / 2;

    cout << "EigenValues: " << endl;
    //populate eigen vector and output
    double alpha[2][2] = {{eigen1, 0},{0, eigen2}};
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            cout << alpha[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //For eigen 1, subtract from A
    mat[0][0] -= eigen1;
    mat[1][1] -= eigen1;
    //shear eigenmatrix and B
    double shear[2][2] = {{1,0},{-mat[1][0] / mat[0][0],1}};

    double shearedA[2][2];
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                shearedA[i][j] += shear[i][k] * mat[k][j];
            }
        }
    }
    double R[2][2];
    if(shearedA[1][0] == 0 && shearedA[1][1] == 0){
        R[0][0] = -shearedA[0][1] / shearedA[0][0];
        R[1][0] = 1;
    }

    //For eigen 2
    mat[0][0] += eigen1;
    mat[1][1] += eigen1;
    mat[0][0] -= eigen2;
    mat[1][1] -= eigen2;
    shear[1][0] = -mat[1][0] / mat[0][0];
    double shearedA2[2][2];
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                shearedA2[i][j] += shear[i][k] * mat[k][j];
            }
        }
    }
    mat[0][0] += eigen2;
    mat[1][1] += eigen2;
    if(shearedA2[1][0] == 0 && shearedA2[1][1] == 0){
        R[0][1] = -shearedA2[0][1] / shearedA2[0][0];
        R[1][1] = 1;
    }

    cout << "R: " << endl;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            cout << R[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //get the transpose of r
    double rTranspose[2][2];
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++)
            rTranspose[i][j] = R[j][i];
    }

    //Matrix multiplication for r, r transpose, and eigenvectors
    double temp2[2][2];
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                temp2[i][j] += R[i][k] * alpha[k][j];
            }
        }
    }
    double eigenDecomp[2][2];
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                eigenDecomp[i][j] += temp2[i][k] * rTranspose[k][j];
            }
        }
    }
    
    cout << "Eigen Decomposition: \n";
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            cout << eigenDecomp[i][j] << " ";
        }
        cout << endl;
    }

    bool comparisonTrue = true;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            if(eigenDecomp[i][j] != mat[i][j])
                comparisonTrue = false;
        }
    }
    cout << comparisonTrue << endl;

    return 0;
}