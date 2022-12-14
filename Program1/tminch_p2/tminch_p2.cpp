#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*
* Takes in filename, opens and reads in by line, parses by space,
* pushes onto 2d vector and returns full matrix
*/
vector<vector<double> > readMatrix(string filename){
    ifstream infile(filename);
    if(!infile.is_open())
        throw std::invalid_argument("File failed to open or was not found");
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
        result.push_back(arr);
        arr.clear();
    }
    return result;
}

int main(int argc, char *argv[]){
    //2d arrays for each of the files
    vector<vector<double> > file1;
    vector<vector<double> > file2;

    //checking command line arguments
    if(argc != 4){
        cout << "USAGE: ./tminch_p2 <matrixFile1> <matrixFile2> <outputFileName>" << endl;
        return 1;
    }
    
    string outputFileName = argv[3];
    try{
        file1 = readMatrix(argv[1]);
        file2 = readMatrix(argv[2]);
    }
    catch(std::invalid_argument& e){
        cerr << e.what() << endl;
        return -1;
    }
    //if files arent the same size or one is empty, raise error
    if(file1.size() == 0 || file2.size() == 0){
        cout << "Error! One or both of the matrix files was empty! Try again!" << endl;
        return 0;
    }else if (file1.size() != file2.size()){
        cout << "Error! Matrices are not the same dimensions and cannot be added!" << endl;
        return 0;
    }

    ofstream outfile;
    outfile.open(outputFileName);
    if(!outfile.is_open()){
        cout << "Error opening file, try again";
        return -1;
    }

    //write out the addition of each element of the 2d arrays to file
    for(int i = 0; i < file1.size(); i++){
        for(int j = 0; j < file1[i].size();j++)
            outfile << file1[i][j] + file2[i][j] << " ";
        outfile << "\n";
    }

    return 0;
}