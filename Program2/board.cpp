#include "board.h"

Board::Board(){
    bool manualPlay = true;
    gameOver = false;
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
    gameOver = false;
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
            if(isValid(moves[i])){
                //flip cells, compute scores
                flipCells(moves[i], i);
            }
            //display grid and score
            displayBoard(moves[i]);
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
            if(isValid(move)){
                flipCells(move, i);
            }
            //display grid and score
            displayBoard(move);
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
        }
    }
}

bool Board::isValid(pair<pair<int,int>, pair<int,int> > move){
    if(move.first.first > n || move.first.first <= 0 || move.first.second > n || move.first.second <= 0
        || move.second.first > n || move.second.first <= 0 || move.second.second > n || move.second.second <= 0)
            return false;
    double slope = (move.first.second - move.second.second) / (move.first.first - move.second.first);
    double perpTest = -(move.first.first - move.second.first) / (move.first.second - move.second.second);

    for(int i = 0; i < slopeList.size();i++){
        if(slopeList[i] == perpTest)
            return false;
    }
    if(mat[move.first.first - 1][move.first.second - 1] != 'X' &&
        mat[move.first.first - 1][move.first.second - 1] != 'O' &&
        mat[move.second.first - 1][move.second.second - 1] != 'X' &&
        mat[move.second.first - 1][move.second.second - 1] != 'O')
    {
        if(move.first.first == move.second.first && move.first.second == move.second.second){
            //then do nothing
        }
        else
            slopeList.push_back(slope);
        return true;
    }
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

void Board::displayBoard(pair<pair<int,int>, pair<int, int> > move){
    cout << move.first.first << " " << move.first.second << " "
        << move.second.first << " " << move.second.second << endl;
    cout << "PLAYER 1 SCORE: " << p1Cells << endl;
    cout << "PLAYER 2 SCORE: " << p2Cells << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }
}

void Board::displayBoardEnd(){
    cout << "\n---- GAME OVER ----\n";
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
    // int m_new = 2 * (move.second.second - move.first.second);
    // int slope_error_new = m_new - (move.second.first - move.first.first);
    if(i % 2 == 0){
        mat[move.first.first - 1][move.first.second - 1] = 'X';
        mat[move.second.first - 1][move.second.second - 1] = 'X';
        p1Cells += 2;
    }else{
        mat[move.first.first - 1][move.first.second - 1] = 'O';
        mat[move.second.first - 1][move.second.second - 1] = 'O';
        p2Cells += 2;
    }

    // for (int x = move.first.first, y = move.first.second; x <= move.second.first; x++) {
    //     if(i % 2 == 0){
    //         mat[x-1][y-1] = 'X';
    //         p1Cells++;
    //     }
    //     else{
    //         mat[x-1][y-1] = 'O';
    //         p2Cells++;
    //     }
 
    //     // Add slope to increment angle formed
    //     slope_error_new += m_new;
 
    //     // Slope error reached limit, time to
    //     // increment y and update slope error.
    //     if (slope_error_new >= 0) {
    //         y++;
    //         slope_error_new -= 2 * (move.second.first - move.first.first);
    //     }
    // }
}