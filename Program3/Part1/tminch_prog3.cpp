#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<double> > readMatrix(string filename){
    ifstream infile(filename);
    if(!infile.is_open())
        throw std::invalid_argument("File failed to open or was not found");
    string myline, myline2, temp2;
    vector<double> arr;
    vector<vector<double> > result;

    while(getline(infile,myline)){
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
            if(arr.size() > 3)
                throw invalid_argument("Matrix in file is too large! Try again!");
        }
        result.push_back(arr);
        arr.clear();
    }
    if(result.size() != 2 || result[0].size() != 3){
        throw invalid_argument("Matrix in file is too small! Try again!");
    }
    return result;
}

int main(int argc, char *argv[]){
    if(argc != 2){
        cout << "USAGE: ./<progName> <input file>\n";
        return -1;
    }
    vector<vector<double> > temp;
    try{
        temp = readMatrix(argv[1]);
    }
    catch(const exception& e){
        std::cerr << e.what() << '\n';
        return -1;
    }

    double A[2][2];
    double B[2];
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            A[i][j] = temp[i][j];
        }
    }
    B[0] = temp[0][2];
    B[1] = temp[1][2];

    double shear[2][2] = {{1,0},{-A[1][0] / A[0][0],1}};

    double shearedA[2][2];
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                shearedA[i][j] += shear[i][k] * A[k][j];
            }
        }
    }

    double shearedB[2];
    for(int i = 0; i < 2; i++){
        for(int k = 0; k < 2; k++){
            shearedB[i] += shear[i][k] * B[k];
        }
    }

    if(shearedA[1][1] == 0 && shearedB[1] != 0){
        cout << "Inconsistent solution.\n";
        return 0;
    }else if(shearedA[1][1] == 0 && shearedB[1] == 0){
        cout << "Undetermined solution.\n";
        return 0;
    }
    cout << "x1: " << shearedB[1] / shearedA[1][1] << endl;
    cout << "x2 : " << shearedB[0] - (shearedA[0][1] * (shearedB[1] / shearedA[1][1])) / shearedA[0][0] << endl;

    return 0;
}