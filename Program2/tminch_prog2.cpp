#include "board.h"

int main(int argc, char *argv[]){
    if(argc == 2){
        try{
            Board game(argv[1]);
        }
        catch(const exception& e){
            std::cerr << e.what() << '\n';
        }
    }else{
        Board game;
    }
    

    return 0;
}