/* Connect 4 in CPP
 * Maybe it will work
 * Never done this before
 * Jake Gendreau
 * Sep 15 2023
 */

//Prototypes
void printBoard(char board[6][7]);
void placePiece(char board[6][7], char color, int move);
bool checkMove(char board[6][7], int move);
void checkWin(char[6][7], int, int);
void checkHorizontal(char[6][7], int, int);
void checkVertical(char[6][7], int, int);
void checkUpperDiag(char[6][7], int, int);
void checkLowerDiag(char[6][7], int, int);
void badInput();

#include <iostream>
#include <limits>

using namespace std;

bool win;
char blank = ' ';

int main(){

    //Random seed
    srand(time(0));

    //Vars
    int player = 0;
    int move;
    char color;
    int pos;
    int bot = 0;

    cout << "Use bot?\n1) Yes\n2) No" << endl;
    while(cout << "> " && !(cin >> bot) || bot < 1 || bot > 2){
        badInput();
    }

    //Init board
    char board[6][7];

    //Fill board with O
    for (int i=0;i<6;i++){
        for(int j=0;j<7;j++){
            board[i][j] = blank;
        }
    }

    //Gameplay loop
    do{

        //Player turn
        if(player == 1){
            color = 'r';

            //Get user input
            while(printf("Red, enter your move (1 - 7): ") && !(cin >> move) || move > 7 || move < 1 || checkMove(board, move - 1) == false){
                    badInput();
            }
            move--;  
        }


        //Bot turn
        if(player == 0){

            color = 'g';

            if(bot == 1){
                do{
                    move = (rand() % 7);
                    for(int i=0;i<6;i++){
                        if(board[0][i] != blank && board[0][i+1] != blank && i == 5){
                            cout << "No more available spaces. The game is a tie" << endl;
                            exit(1);
                        }
                    }
                } while (checkMove(board, move) == false);

                printf("\nBot Move: %i\n\n", move);
            } else {
                //Get user input
                while(printf("Yellow, enter your move (1 - 7): ") && !(cin >> move) || move > 7 || move < 1 || checkMove(board, move - 1) == false){
                    cin.clear(); //clear bad input flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
                    cout << "Invalid input; please re-enter.\n";
                }
                move--; 
            }
        }

        placePiece(board, color, move);
        printBoard(board);

        //change player
        player = (player + 1) % 2;

    } while (win == false);

    if(player == 0){
        cout << "Player 1 wins!" << endl;
    } else if (player == 1){
        cout << "Player 2 wins!" << endl;
    }
}

void badInput(){
    cin.clear(); //clear bad input flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
    cout << "Invalid input; please re-enter.\n";
}

void printBoard(char board[6][7]){

    //Print nums at top of board
    for(int i=0;i<7;i++){
        cout << "\t" << i+1;
    }
    printf("\n\n");

    //print board
    for (int i=0;i<6;i++){
        for(int j=0;j<7;j++){
            cout << "\t" << board[i][j];
        }
        cout << "\n\n";
    }
}

void placePiece(char board[6][7], char color, int move){
    //Place piece in board
        for(int i=0;i<6;i++){
            //Check for piece under
            if(board[i+1][move] != blank || i+1 > 5){
                board[i][move] = color;
                checkWin(board, move, i);
                break;
            }
        }
}

bool checkMove(char board[6][7], int move){
    //If top space is empty, then column is playable
    if(board[0][move] == blank){
        return true;
    }
    return false;
}

void checkWin(char board[6][7], int xpos, int ypos){
    checkHorizontal(board, xpos, ypos);
    checkVertical(board, xpos, ypos);
    checkUpperDiag(board, xpos, ypos);
    checkLowerDiag(board, xpos, ypos);
}

void checkHorizontal(char board[6][7], int xpos, int ypos){//Works
    //Array of winnning pieces
    char* pieces[4];

    //Check horizontal
    //Go backwards to leftmost connecting piece
    while(xpos-1 >= 0 && board[ypos][xpos-1] == board[ypos][xpos]){
        xpos = xpos-1;
    }

    //Check for 4 pieces directly to the right
    for(int i =0;i<4;i++){
        if(board[ypos][xpos+i] != board[ypos][xpos] || xpos+i > 6){
            break;
        } 
        pieces[i] = &(board[ypos][xpos+i]);
        if(i == 3){
            win = true;

            //Highlight winning pieces
            for(int j=0; j<4; j++){
                (pieces[j])[0] -= 32;
            }
            cout << "Horizontal win!" << endl;
        }   
    }
}

void checkVertical(char board[6][7], int xpos, int ypos){//Works
    //Array of winnning pieces
    char* pieces[4];

    //Check vertical

    //Go backwards to top of stack
    while(ypos-1 >= 0 && board[ypos-1][xpos] == board[ypos][xpos]){
        ypos = ypos-1;
    }

    //Check for 4 pieces directly below
    for(int i=0;i<4;i++){
        if(board[ypos+i][xpos] != board[ypos][xpos] || ypos+i > 5){
            break;
        } 
        
        pieces[i] = &(board[ypos+i][xpos]);

        if(i == 3){
            win = true;

            //Highlight winning pieces
            for(int j=0; j<4; j++){
                (pieces[j])[0] -= 32;
            }
            cout << "Vertical Win!" << endl;
        }   
    }
}

void checkUpperDiag(char board[6][7], int xpos, int ypos){//Works
    //Array of winnning pieces
    char* pieces[4];

    //Check upper diag

    //Go backwards to top left of diag
    while(ypos-1 >= 0 && xpos-1 >= 0 && board[ypos-1][xpos-1] == board[ypos][xpos]){
        ypos = ypos-1;
        xpos = xpos-1;
    }

    //Check for 4 pieces directly lower left
    for(int i =0;i<4;i++){
        if(board[ypos+i][xpos+i] != board[ypos][xpos] || ypos+i > 5 || xpos+i > 6){
            break;
        } 
        pieces[i] = &(board[ypos+i][xpos+i]);

        if(i == 3){
            win = true;

            //Highlight winning pieces
            for(int j=0; j<4; j++){
                (pieces[j])[0] -= 32;
            }
            cout << "Upper Diagonal Win!" << endl;
        } 
    }
}

void checkLowerDiag(char board[6][7], int xpos, int ypos){//Works
    //Array of winnning pieces
    char* pieces[4];

    //Check lower diag

    //Go backwards to lower left of diag
    while(ypos+1 <= 5 && xpos-1 >= 0 && board[ypos+1][xpos-1] == board[ypos][xpos]){
        ypos = ypos+1;
        xpos = xpos-1;
    }

    //Check for 4 pieces directly upper right
    for(int i=0;i<4;i++){
        if(board[ypos-i][xpos+i] != board[ypos][xpos] || xpos+i > 7 || ypos-i < 0){
            break;
        }
        
        pieces[i] = &(board[ypos-i][xpos+i]);

        if(i == 3){
            win = true;

            //Highlight winning pieces
            for(int j=0; j<4; j++){
                (pieces[j])[0] -= 32;
            }
            cout << "Lower Diagonal Win!" << endl;
        } 
    }
}