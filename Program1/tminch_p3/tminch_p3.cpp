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

    //Read file line by line and parse by spaces
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
    }catch(std::invalid_argument& e){
        cerr << e.what() << endl;
        return -1;
    }
    
    //if files aren't compatible or ar empty
    if(file1.size() == 0 || file2.size() == 0){
        cout << "Error! One or both of the matrix files was empty! Try again!" << endl;
        return 0;
    }else if (file1[0].size() != file2.size()){
        cout << "Error! Matrix 1 cols and matrix 2 rows are not the same. Try again!" << endl;
        return 0;
    }
    
    //Allocate memory for array
    int finalRows = file1.size();
    int finalCols = file2[0].size();
    double** final = new double*[finalRows];
    for(int i = 0; i < file1.size();i++)
        final[i] = new double[finalCols];

    //initialize array to all 0s
    for(int i = 0; i < finalRows; i++){
        for(int j = 0; j < finalCols; j++)
            final[i][j] = 0;
    }

    //perform matrix multiplication
    for(int i = 0; i < finalRows; i++){
        for(int j = 0; j < finalCols; j++){
            for(int k = 0; k < file1[0].size(); k++){
                final[i][j] += file1[i][k] * file2[k][j];
            }
        }
    }

    ofstream outfile;
    outfile.open(outputFileName);
    if(!outfile.is_open()){
        cout << "Error opening file, try again";
        return -1;
    }

    //Write out multiplied matrix to file.
    for(int i = 0; i < finalRows; i++){
        for(int j = 0; j < finalCols;j++)
            outfile << final[i][j] + final[i][j] << " ";
        outfile << "\n";
    }

    for(int i = 0; i < finalRows; i++)
        delete [] final[i];
    delete [] final;

    return 0;
}