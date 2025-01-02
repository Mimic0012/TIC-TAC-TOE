#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

char board [3][3]; //we have created a 2d array of char which can hold x and o
char PLAYER;
char COMPUTERS;

void updateglobalvariable();//updates the global variable
void resetBoard();  //reset the board
void printBoard();  // print our board which is a 2d array
int checkFreespaces(); // checks free spaces if it is zero than the game is over
void playerMove();   // checks and make player moves
void computerMove(); // checks and make computers moves
char checkWinner();  // checks who is the winner
void printWinner(char);  // prints the winner


int main ()
{
    char winner =' ';// winner is not decided yet if X wins then it will show x,we can modify this variable later on
    char response;
    updateglobalvariable();
    printf("Player's symbol: %c\n",PLAYER); 
    printf("Computer's symbol: %c\n",COMPUTERS);

    do
    {
        winner = ' ';
        response = ' ';
        resetBoard();
        while(winner==' ' && checkFreespaces() !=0) //
        {
            printBoard();
            playerMove();//this is only for the value
            winner = checkWinner();//this will return values of the return values which will be like X OR O
            if(winner !=' '|| checkFreespaces() ==0)
            {
                break;
            }

            computerMove();
            winner = checkWinner();
            if(winner !=' '|| checkFreespaces() ==0)
            {
                break;
            }
        }

        printBoard();// Print the board after the game loop ends
        printWinner(winner);// Print the winner after the game loop ends

        printf("would you like to play again? (Y/N):");
        scanf(" %c",&response);
        response = toupper(response);//to make it bigger
    } while (response == 'Y');
    printf("Thanks for playing!");
    
    return 0;
}

void updateglobalvariable()
{
    printf("please enter what you want to play as 'X' OR 'O'\n");
    scanf(" %c",&PLAYER);//gap should be given to avoid the newline be taken by the buffer
    PLAYER = toupper(PLAYER);//ctype is used to make char uppercase its not necessary
    if(PLAYER == 'X')
    {
        COMPUTERS = 'O';
    }else if (PLAYER == 'O')
    {
        COMPUTERS = 'X';
    }else{
        printf("Invalid choice. Please choose 'X' or 'O'.\n");
        updateglobalvariable();// Prompt the user again for a correct choice
    }
}

void resetBoard()
{
    for(int i =0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            board[i][j]=' ';
        }
    }
}
void printBoard()
{
    printf("    %c | %c   | %c  ",board[0][0],board[0][1],board[0][2]);
    printf("\n -----|-----|-----\n");
    printf("    %c | %c   | %c  ",board[1][0],board[1][1],board[1][2]);
    printf("\n -----|-----|-----\n");
    printf("    %c | %c   | %c  ",board[2][0],board[2][1],board[2][2]);
    printf("\n");

}
int checkFreespaces() 
{
    int freespaces = 9;
    for (int i =0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[i][j]!=' ') //we check if the spaces in board are occupied and if yes then it will decrement the freespaces and return the value
            {
                freespaces--;
            }
        }
    }
    return freespaces;
}
void playerMove()
{
    int x,y;
    do
    {
        printf("please enter rows#(1-3)\n");
        scanf("%d",&x);
        x--; //
        printf("please enter the columns#(1-3)\n");
        scanf("%d",&y);
        y--;

        if(board[x][y]!=' ')
        {
            printf("Invalid move.The spot is already taken");
        }
        else{
            board[x][y]= PLAYER;// jo bhi move chala he use PLAYER KE EQUAL kardiya which is equal to the user what they have chosen above
            break; //if it enters the correct cond then it will break
        }
    } while (board[x][y]!=' ');//if the board is not occupied then we will prompt the user to enter a choice again
    
}
void computerMove()
{
    srand(time(0));
    int x,y;
    if(checkFreespaces() >0)
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] !=' ');

        board[x][y]= COMPUTERS;//takes the randomly genrated x and y and make it equal to the computer
    }
    else
    {
        printWinner(' ');//this means there is no winner and its a tie
    }    
}
char checkWinner()
{
    // check rows
    for(int i=0;i<3;i++)
    {
        if(board[i][0]==board[i][1]&& board[i][1]==board[i][2])
        {
            return board[i][0];
        }
    }
    //check columns
    for(int j=0;j<3;j++)
    {
        if(board[0][j]==board[1][j]&& board[1][j]==board[2][j])
        {
            return board[0][j];//this will tell if there is a matching set presnt yet
        }
    }
    //check diagonals
    if(board[0][0]==board[1][1]&& board[1][1]==board[2][2])
    {
        return board[0][0];
    }
    if(board[0][2]==board[1][1]&& board[1][1]==board[2][0])
    {
        return board[0][2];
    }
    return ' '; //if there is no winner yet
    
}
void printWinner(char winner)
{
    if(winner == PLAYER)
    {
        printf("YOU WIN!\n");
    }else if(winner == COMPUTERS)
    {
        printf("YOU LOOSE!\n");
    }else{
        printf("IT'S A TIE!\n");
    }
}