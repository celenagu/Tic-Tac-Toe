#include <iostream>
#include <string>

#define N 3
#define mask_play1 0b1
#define mask_play2 0b10

int main();
void print_board(char *board);
char *createboard();
void cleanboard(char *board);
int mark(char *board, int x, int y, bool isDone);
void game();
bool gameOver(char *board, int x, int y, bool turn1);

int pos_1D(int x, int y);

//Converting from x,y coordinate to 1D array index
int pos_1D(int x, int y){
    int pos = (y*N) + x;
    return pos;
}

//Constructor
char *createboard(){
    std::size_t capacity {N*N};
    char *board {new char [capacity]{}};
    return board; 
}

//Destructor
void cleanboard(char *board){
    delete[] board;
    board = nullptr;
    return;
}


void print_board(char *board){
    std::size_t curr_field{};
    std::cout << " _____ _____ _____ " << std::endl ;

    for (std::size_t i{}; i<N; i++){
    std::cout << "|     |     |     |" << std::endl;
    std::cout << "|";

        for (std::size_t j{}; j<N; j++){

            
            curr_field = board[j+(i*N)];
            //check if play 1
            if ((mask_play1&curr_field) == mask_play1){
                std::cout << "  X  ";
            }
            //check if play 2
            else if ((mask_play2&curr_field) == mask_play2){
                std::cout << "  O  ";
            }
            //otherwise, empty
            else{
                //need parentheses around bitwise &, low priority
                std::cout << "  -  ";
            }
            std::cout << "|";
        }
        std::cout << std::endl;
        std::cout << "|_____|_____|_____|" ;
        std::cout << std::endl;

    }
    std::cout << std::endl;
    return;
}

//mark = 1 > already marked 
//mark = 0 > empty, not marked
int mark(char *board, int x, int y, bool isDone){
    if (board[pos_1D(x, y)]!=0){
        std::cout <<std::endl << "Enter an unmarked location." << std::endl;
        return 1;
    }
    else {
        if (isDone){ //player 1
            board[pos_1D(x, y)] = 1;
        }
        else{
            board[pos_1D(x, y)] = 2;
        }
        return 0;
    }
}

//if 1, game is over
//if 0, game is not over
bool gameOver(char *board, int x, int y, bool turn1){
    int val;
    if (turn1){
        val = mask_play1;
    }
    else{
        val = mask_play2;
    }

    //Check if board is filled
    for (int i{0}; i<(N*N); i++){
        if(board[i]==0){
            break;
        }
        else if (i==(N*N-1)){
            std::cout << "Draw!" << std::endl;
            board[pos_1D(x, y)] = 0;
            return 1;
        }
    }

    //Check if board is in a won state
    //check row

    for (int i{}; i<N; i++){
        if (board[pos_1D(x, i)] != val){
            break;
        }
        else if (i==(N-1)){
            return 1;
        }
    }

    //check column
    for (int i{}; i<N; i++){
        if (board[pos_1D(i, y)] != val){
            break;
        }
        else if (i==(N-1)){
            return 1;
        }
    }

    //check diagonal
    for (int i{}; i<(N); i++){
        if (board[pos_1D(i, i)] != val){
            break;
        }
        else if (i==(N-1)){
            return 1;
        }
    }

    //check antidiagonal
    for (int i{}; i<N; i++){
        if (board[pos_1D(i, N-1-i)] != val){
            break;
        }
        else if (i==(N-1)){
            return 1;
        }
    }

    //if none of the above conditions are met, game is not over
    return 0;

}

void game(){
    std::string play1 = "";
    std::string play2 = "";
    std::string curr = "";
    std::string x_val;
    std::string y_val;
    int x;
    int y;
    bool isDone = false;
    bool turn1 = true;
    bool quit = false;

    std::cout << std::endl << "Welcome to Tic Tac Toe!" << std::endl;
    std::cout << "Enter name of Player 1: ";
    std::cin >> play1;
    std::cout << "Enter name of Player 2: ";
    std::cin >> play2;
    std::cout << std::endl;
    std::cout << "Enter 'Q' at any time to quit" << std::endl << std::endl;

    char *board = createboard();
    print_board(board);

    while (true){
        
        if (turn1){
            curr = play1;
        }
        else{
            curr = play2;
        }

        while (true){
            std::cout << std::endl << curr << "'s turn" << std::endl;   
            std::cout << "Enter coordinates of where you would like to play." << std::endl;

            std::cout << "x-coord: ";
            std::cin >> x_val;
            if(x_val.substr(0,1) == "Q"){
                quit = true;
                break;
            }
            
            std::cout << "y-coord: ";
            std::cin >> y_val;
            if (y_val.substr(0,1) == "Q"){
                quit = true;
                break;
            }

            if (isdigit(x_val[0]) && isdigit(y_val[0])){
                try
                {
                    int x_end = x_val.find_first_not_of("0123456789");
                    int y_end = y_val.find_first_not_of("0123456789");
                    x = std::stoi(x_val.substr(0, x_end));
                    y = std::stoi(y_val.substr(0,y_end)); 

                    if (!(x >= 0 && x < N && y >= 0 && y<N)){
                        throw ("Enter coordinates within range.");
                    }
                }
                catch(const char* message)
                {
                    std::cout << message << std::endl;
                    // turn1 = !turn1;
                }
            }
            else{
                std::cout << "Enter valid coordinates." << std::endl;
            }

            if (board[pos_1D(x, y)]==0){
                mark(board, x,y, turn1);
                break;
            }
            else{
                continue;
            }
        }
        print_board(board);
        isDone = gameOver(board, x, y, turn1);


        if(isDone){
            if(board[pos_1D(x, y)]!=0){
                if (turn1){
                    std::cout << play1 << " has won!" << std::endl;
                }
                else{
                    std::cout << play2 << " has won!" << std::endl;
                }
            }
            quit = true;
        }


        if (quit == true){
            std::cout << std::endl <<"Quitting..."<< std::endl;
            cleanboard(board);
            break;
        }
        else{
            turn1 = !turn1;
        }
    }
    return;
}


int main(){
    game();
    return 0;
}
