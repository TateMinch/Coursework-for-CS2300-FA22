#include "board.h"

Board::Board(){
    bool manualPlay = true;
    gameOver = false, p1InvalidMove = false, p2InvalidMove = false;
    p1Cells = 0, p2Cells = 0;
    cout << "Enter N for NxN grid: ";
    cin >> n;
    cout << "Enter whatever K is: ";
    cin >> k;
    playGame(manualPlay);
    freeMemory();
}

Board::Board(string file){
    bool manualPlay = false;
    gameOver = false, p1InvalidMove = false, p2InvalidMove = false;
    p1Cells = 0, p2Cells = 0;
    infile.open(file);
    if(!infile.is_open())
        throw invalid_argument("Failed to open file. Try again!");
    
    infile >> n, infile >> k;
    playGame(manualPlay);
    freeMemory();
}

void Board::playGame(bool isManual){
    generateBoard(n);
    int i = 0;
    if(!isManual){
        readFile();
        //while still moves in list AND game is not over, validate
        while(i < moves.size() && !gameOver){
            //if valid
            if(isValid(moves[i], i)){
                //flip cells, compute scores
                flipCells(moves[i], i);
            }else{
                cout << "INVALID MOVE - NEXT PLAYERS MOVE" << endl;
            }
            //display grid and score
            displayBoard(moves[i], i);
            i++;
            bool breakOut = false;
            for(int j = 0; j < n && !breakOut; j++){
                for(int t = 0; t < n && !breakOut; t++){
                    if(mat[j][t] == '.'){
                        gameOver = false;
                        breakOut = true;
                    }
                    else
                        gameOver = true;
                }
            }
            if(p1InvalidMove && p2InvalidMove)
                gameOver = true;
        }
        //if game ended successfully
        if(gameOver){
            //Display game over score and grid
            displayBoardEnd();
        }
        //if game not over AND no moves, display error
        else{
            cout << "DID NOT PROVIDE ENOUGH MOVES FOR FULL GAME. TRY AGAIN." << endl;
        }
    }
    else{
        //while game is not over
        while(!gameOver){
            pair<pair<int,int>, pair<int,int> > move;
            if(i % 2 == 0)
                cout << "PLAYER 1" << "\n";
            else
                cout << "PLAYER 2" << "\n";
            //take in move, validate
            cout << "Enter x1: ";
            cin >> move.first.first;
            cout << "Enter y1: ";
            cin >> move.first.second;
            cout << "Enter x2: ";
            cin >> move.second.first;
            cout << "Enter y2: ";
            cin >> move.second.second;
            //if valid, flip cells, compute scores
            if(isValid(move, i)){
                flipCells(move, i);
            }
            //display grid and score
            displayBoard(move, i);
            i++;
            bool breakOut = false;
            for(int j = 0; j < n && !breakOut; j++){
                for(int t = 0; t < n && !breakOut; t++){
                    if(mat[j][t] == '.'){
                        gameOver = false;
                        breakOut = true;
                    }
                    else
                        gameOver = true;
                }
            }
            if(p1InvalidMove && p2InvalidMove)
                gameOver = true;
        }
    }
}

bool Board::isValid(pair<pair<int,int>, pair<int,int> > move, int i){
    //if any are out of bounds
    if(move.first.first > n || move.first.first <= 0 || move.first.second > n || move.first.second <= 0
        || move.second.first > n || move.second.first <= 0 || move.second.second > n || move.second.second <= 0){
            if(i % 2 == 0)
                p1InvalidMove = true;
            else
                p2InvalidMove = true;
            return false;
        }
    //get slope and inverse of slope of move line
    double slope = (move.first.second - move.second.second) / (move.first.first - move.second.first);
    double perpTest = -(move.first.first - move.second.first) / (move.first.second - move.second.second);
    //if there is a k specified
    if(k!= 0){
        //if there have been less than k moves made
        if(slopeList.size() < k){
            //check everything in list of slopes against current move
            for(int j = 0; j < slopeList.size();j++){
                if(slopeList[j] == perpTest){
                    if(i % 2 == 0)
                        p1InvalidMove = true;
                    else
                        p2InvalidMove = true;
                    return false;
                }
            }
        }else{
            //check only the last k slopes against current move
            for(int j = 0; j < k; j++){
                if(slopeList[slopeList.size() - 1 - j] == perpTest){
                    if(i % 2 == 0)
                        p1InvalidMove = true;
                    else
                        p2InvalidMove = true;
                    return false;
                }
            }
        }
    }
    //if both start and end point are empty
    if(mat[move.first.first - 1][move.first.second - 1] != 'X' &&
        mat[move.first.first - 1][move.first.second - 1] != 'O' &&
        mat[move.second.first - 1][move.second.second - 1] != 'X' &&
        mat[move.second.first - 1][move.second.second - 1] != 'O')
    {
        //if k is greater than 0
        if(k != 0){
            //if it is a single point, do not add to slope list
            if(move.first.first == move.second.first && move.first.second == move.second.second){
                //then do nothing
            }
            else
                slopeList.push_back(slope);
        }
        return true;
    }
    if(i % 2 == 0)
        p1InvalidMove = true;
    else
        p2InvalidMove = true;
    return false;
}

void Board::generateBoard(int n){
    //dynamically allocate memory for board
    mat = new char*[n];
    for(int i = 0; i < n; i++)
        mat[i] = new char[n];

    //fill board with periods
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            mat[i][j] = '.';
    }
}

void Board::freeMemory(){
    for(int i = 0; i < n; i++)
        delete[] mat[i];
    delete[] mat;
}

void Board::readFile(){
    int temp;
    pair<pair<int,int>,
    pair<int,int> > points;

    //while there are still moves in file
    while(infile >> temp){
        //get points and add to move list
        points.first.first = temp;
        infile >> temp;
        points.first.second = temp;
        infile >> temp;
        points.second.first = temp;
        infile >> temp;
        points.second.second = temp;
        moves.push_back(points);
    }

    //if there weren't any moves, throw error
    if(moves.size() < 1){
        freeMemory();
        throw invalid_argument("No moves in file. Try again!");
    }
}

void Board::displayBoard(pair<pair<int,int>, pair<int, int> > move, int i){
    if(i % 2 == 0)
        cout << "PLAYER 1 ";
    else
        cout << "PLAYER 2 ";
    cout << "MOVE: " << move.first.first << " " << move.first.second << " "
        << move.second.first << " " << move.second.second << endl;
    cout << "PLAYER 1 SCORE: " << p1Cells << endl;
    cout << "PLAYER 2 SCORE: " << p2Cells << endl;
    for(int l = 0; l < n; l++){
        for(int j = 0; j < n; j++){
            cout << mat[l][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void Board::displayBoardEnd(){
    cout << "---- GAME OVER ----\n";
    cout << "Player 1 score: " << p1Cells << endl;
    cout << "Player 2 score: " << p2Cells << endl;
    if(p1Cells > p2Cells)
        cout << "PLAYER 1 WINS\n";
    else if(p2Cells > p1Cells)
        cout << "PLAYER 2 WINS\n";
    else
        cout << "ITS A DRAW!\n";
}

void Board::flipCells(pair<pair<int,int>, pair<int,int> > move, int i)
{
    //if the first point is after the second
    if(move.first.first > move.second.first){
        //swap the points in the move
        int temp = move.first.first;
        move.first.first = move.second.first;
        move.second.first = temp;
        temp = move.first.second;
        move.first.second = move.second.second;
        move.second.second = temp;
    }
    //if one of the divisors for slope is 0, set slope to 0
    double slope;
    if( ( (double)move.first.second - (double)move.second.second) == 0 ||
        ((double)move.first.first - (double)move.second.first == 0)){
            slope = 0;
    }
    else
        slope = ((double)move.first.second - (double)move.second.second) / 
            ((double)move.first.first - (double)move.second.first);
    //if slope is 0 and the x coordinates are the same
    if(slope == 0 && move.first.first == move.second.first){
        //increment over cols and set value
        for(int j = 1; j <= n; j++){
            if(j >= move.first.second && j <= move.second.second){
                if(i % 2 == 0){
                    if(mat[move.first.first - 1][j - 1] == 'O')
                        p2Cells--;
                    mat[move.first.first - 1][j - 1] = 'X';
                    p1Cells++;
                }else{
                    if(mat[move.first.first - 1][j - 1] == 'X')
                        p1Cells--;
                    mat[move.first.first - 1][j - 1] = 'O';
                    p2Cells++;
                }
            }
        }
    }
    //if slope is 0 and y coordinates are the same
    else if(slope == 0 && move.first.second == move.second.second){
        //increment over rows and set values
        for(int j = 1; j <= n; j++){
            if(j >= move.first.first && j <= move.second.first){
                if(i % 2 == 0){
                    if(mat[j - 1][move.first.second - 1] == 'O')
                        p2Cells--;
                    mat[j - 1][move.first.second - 1] = 'X';
                    p1Cells++;
                }else{
                    if(mat[j - 1][move.first.second - 1] == 'X')
                        p1Cells--;
                    mat[j - 1][move.first.second - 1] = 'O';
                    p2Cells++;
                }
            }
        }
    }
    else{
        //calculate b
        double b = -((double)slope * (double)move.first.first) + (double)move.first.second;
        //for the values in the board
        for(int j = 1; j <= n; j++){
            //if the x value is in the bounds of the move
            if(j >= move.first.first && j <= move.second.first){
                //calculate y value
                double y = slope * j + b;
                //round to nearest number to get the closest cell
                y = round(y);
                //set cell
                if(i % 2 == 0){
                    if(mat[j-1][(int)y-1] == 'O')
                        p2Cells--;
                    mat[j - 1][(int)y - 1] = 'X';
                    p1Cells++;
                }
                else{
                    if(mat[j - 1][(int)y-1] == 'X')
                        p1Cells--;
                    mat[j - 1][(int)y - 1] = 'O';
                    p2Cells++;
                }
            }
        }
    }

}