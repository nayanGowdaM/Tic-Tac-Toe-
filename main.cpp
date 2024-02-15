#include<bits/stdc++.h>
using namespace std;

class Tictactoe{
    int board[3][3];
    public:
        Tictactoe(){
            memset(board, -1, sizeof(board));
        }
        void printBoard(){
            for( int i=0;i<=2;i++){
                for(int j=0;j<=2; j++){
                    cout<<"\t" << board[i][j];
                    if(j!=2)
                    cout<<"\t|";
                    
                }
                cout<<endl;
                if(i!=2)
                cout<<"-------------------------------------------";
                cout<<endl;
            }
        }

        void set(int i, int j, int player){
            board[i][j] = player;
        }

        bool isFull(){
            for( int i=0;i<=2;i++) 
                for( int j=0;j<=2;j++) 
                    if(board[i][j]==-1) return false;
            return true;
        }

        bool isWinner(int player){
            if((board[0][0]==player && board[1][1]==player && board[2][2]==player) ||
                (board[0][2]==player && board[1][1]==player && board[2][0]==player ))
                    return true;
            for(int i=0;i<=2;i++){
                if((board[i][0]==player && board[i][1]==player && board[i][2]==player ) ||
                    (board[0][i]==player && board[1][i]==player && board[2][i]==player)) 
                        return true;
            }
            return false;
        }

        vector<pair<int,int>> getEmptyCells(){
            vector<pair<int,int>> list;
            for(int i=0;i<=2;i++)
                for( int j=0;j<=2;j++) 
                    if(board[i][j]==-1)
                        list.push_back({i,j});
            return list;
        }

        bool gameover(){
            if(isFull() || isWinner(0) || isWinner(1)) return true;
            else return false;
        }

        bool isValid( int i, int j){
            if(i>=0 &&  i<3 && j>=0 && j<3)
            return board[i][j]==-1;
            else return false;
        }
};

void diplaychoice(){
    cout<<"Enter \n";
    cout<<"1. View Board\n2.Mark the board\n";
}

int main(){
    Tictactoe game;
    int player1, player2;
    cout<<"Enter the choice of Player 1: ";
    cin>>player1;
    if(player1==1){
        cout<<"Player 2 choice is "<< 0<<endl;
        player2=0;
    }
    else {
        cout<<"Player 2 choice is "<< 1<<endl;
        player2=1;
    }
        
    bool turn = true;
    diplaychoice();
    while(!game.gameover()){
        int choice;
        if(turn){
            cout<<"Player1's Turn!!\n";
        }
        else{
            cout<<"Player2's Turn!!\n";
        }
        cout<<"Enter your Choice: ";
        cin>>choice;
        if(choice==1){
            game.printBoard();
        }
        else{
            int x=-1,y=-1;
            while(!game.isValid(x,y)){
                cout<<"Give the location of the mark:\nx: ";
                cin>>x;
                cout<<"y: ";
                cin>>y;
            }
            if(turn){
                game.set(x,y,player1);
                if(game.isWinner(player1)){
                    game.printBoard();
                    cout<<endl;
                    cout<<"Player 1 Wins\n";
                    return 0;
                }
                else if(game.isFull()){
                    cout<<"Game drawed\n";
                    return 0;
                }
    
            }
            else {
                game.set(x,y,player2);
                if(game.isWinner(player2)){
                    game.printBoard();
                    cout<<endl;
                    cout<<"Player 2 Wins\n";
                    return 0;
                }
                else if(game.isFull()){
                    cout<<"Game drawed\n";
                    return 0;
                }
    
            }
            turn = !turn ;


        }

    }
}