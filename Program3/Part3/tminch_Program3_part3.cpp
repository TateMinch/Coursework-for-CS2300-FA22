#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

vector<vector<double> > readMatrix(string filename){
    ifstream infile(filename);
    if(!infile.is_open())
        throw std::invalid_argument("File failed to open or was not found");
    string myline, myline2, temp2;
    vector<double> arr;
    vector<vector<double> > result;

    while(getline(infile,myline)){
        if(result.size() == 3)
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
    if((result.size() != 2 && result.size() != 3) || result[0].size() != 3){
        throw invalid_argument("Matrix in file is too small! Try again!");
    }
    return result;
}

double areaTwoByThree(vector<vector<double> > mat){
    double p1[2] = {mat[0][0], mat[1][0]};
    double p2[2] = {mat[0][1], mat[1][1]};
    double p3[3] = {mat[0][2], mat[1][2]};

    return 0.5 * abs((p1[0] * (p2[1] - p3[2])) + (p2[0] * (p3[1] - p1[1]) + (p3[0] * (p1[1] - p2[1]))));

}
double areaThreeBythree(vector<vector<double> > mat){
    double p1[3] = {mat[0][0], mat[1][0], mat[2][0]};
    double p2[3] = {mat[0][1], mat[1][1], mat[2][1]};
    double p3[3] = {mat[0][2], mat[1][2], mat[2][2]};

    double a1[3] = {p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2]};
    double a2[3] = {p3[0] - p1[0], p3[1] - p1[1], p3[2] - p1[2]};

    double crossProduct[3] = {(a1[1] * a2[2]) - (a1[2] * a2[1]), 
                            -((a1[0] * a2[2]) - (a1[2] * a2[0])),
                            (a1[0] * a2[1]) - (a1[1] * a2[0])};
    return abs(0.5 * (sqrt(pow(crossProduct[0], 2) + pow(crossProduct[1], 2) + pow(crossProduct[2], 2))));
}

int main(int argc, char *argv[]){

    vector<vector<double> > temp;
    try{
        temp = readMatrix(argv[1]);
    }
    catch(const exception& e){
        std::cerr << e.what() << '\n';
        return -1;
    }

    if(temp.size() == 2){
        cout << areaTwoByThree(temp) << endl;
    }else{
        cout << areaThreeBythree(temp) << endl; 
    }

    return 0;
}