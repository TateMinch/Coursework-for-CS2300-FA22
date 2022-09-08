#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<double> > readMatrix(string filename){
    ifstream infile(filename);
    string myline, myline2, temp2;
    vector<double> arr;
    vector<vector<double> > result;

    while(getline(infile,myline)){
        for(int i = 0; i < myline.length(); i++){
            if(myline[i] == ' ' || i == myline.length() - 1){
                if(i == myline.length() - 1)
                    temp2.push_back(myline[i]);
                arr.push_back(stod(temp2));
                temp2 = "";
            }else
                temp2.push_back(myline[i]);
        }
        int size = arr.size();
        result.push_back(arr);
        arr.clear();
    }
    return result;
}

int main(int argc, char *argv[]){
    if(argc != 4){
        cout << "USAGE: ./tminch_p2 <matrixFile1> <matrixFile2> <outputFileName>" << endl;
        return 1;
    }
    
    string outputFileName = argv[3];
    vector<vector<double> > file1 = readMatrix(argv[1]);
    vector<vector<double> > file2 = readMatrix(argv[2]);
    if (file1.size() != file2.size()){
        cout << "Error! Matrices are not the same dimensions and cannot be added!" << endl;
        return 0;
    }

    ofstream outfile;
    outfile.open(outputFileName);

    for(int i = 0; i < file1.size(); i++){
        for(int j = 0; j < file1[i].size();j++)
            outfile << file1[i][j] + file2[i][j] << " ";
        outfile << "\n";
    }

    return 0;
}