#include<bits/stdc++.h>
using namespace std;
enum class PieceType {
    X,
    O,
    None
};


static char pieceTypeToChar(PieceType pieceType){
    char ans;
    if(pieceType==PieceType::None) 
        ans=' ';
    else if(pieceType==PieceType::O)
        ans='O';
    else if( pieceType==PieceType::X)
        ans='X';
    return ans;
}
class PlayingPiece{
    public:
    PieceType piecetype;
    PlayingPiece(): piecetype(PieceType::None){}
    PlayingPiece(PieceType piecetype){
        this->piecetype=piecetype;
    }

};

class PlayingPieceO : PlayingPiece{
    public:
    PlayingPieceO():PlayingPiece(PieceType::O){
        
    }
};

class PlayingPieceX : PlayingPiece{
    public:
    PlayingPieceX():PlayingPiece(PieceType::X){
        
    }
};


class Board{
    public :
    int size;
    vector<vector<PieceType>> board;
    Board(){}
    Board(int size): size(size), board(size, vector<PieceType>(size, PieceType::None)){}

    void printBoard() const {
        cout<<endl;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout<<pieceTypeToChar(board[i][j])<<" ";
                std::cout << " | ";
            }
            std::cout << std::endl;
        }
    }

    vector<pair<int,int>> getFreeCells(){
        vector<pair<int,int>> freeCells;
        for( int i=0;i<size;i++){
            for( int j=0;j<size;j++){
                if(board[i][j]==PieceType::None);
                freeCells.push_back({i,j});
            }
        }
        return freeCells;
    }

    bool addPiece(int row, int col, PieceType playingPiece){
        if(board[row][col]!=PieceType::None) return false;
        board[row][col]=playingPiece;
        return true;
    }
};


class Player{
    public:
    string name;
    PlayingPiece playingPiece;

    Player( string name, PlayingPiece playingPiece ): name(name) , playingPiece(playingPiece){}
};


class TicTacToe{
public:
    deque<Player> players;
    Board gameboard;

    TicTacToe(){

        players.push_back(Player("Player1", PlayingPiece(PieceType::X)));
        players.push_back(Player("Player2", PlayingPiece(PieceType::O)));
        gameboard=Board(3);
    }

    TicTacToe(int size, string name1, string name2){

        players.push_back(Player(name1, PlayingPiece(PieceType::X)));
        players.push_back(Player(name2, PlayingPiece(PieceType::O)));
        gameboard=Board(size);
    }

    bool isThereWinner( int row, int col, PieceType pieceType){
        bool rowMatch=true;
        bool colMatch=true;
        bool diaMatch=true;
        bool antiDiamatch=true;

        for( int i=0;i<gameboard.size;i++){
            if(gameboard.board[row][i]==PieceType::None || gameboard.board[row][i]!=pieceType)
                rowMatch=false;
        }
        for( int i=0;i<gameboard.size;i++){
            if(gameboard.board[i][col]==PieceType::None || gameboard.board[i][col]!=pieceType)
                colMatch=false;
        }
        for( int i=0, j=0;i<gameboard.size;i++, j++){
            if(gameboard.board[i][j]==PieceType::None || gameboard.board[i][j]!=pieceType)
                diaMatch=false;
        }
        for( int i=0, j=gameboard.size-1;i<gameboard.size;i++, j--){
            if(gameboard.board[i][j]==PieceType::None || gameboard.board[i][j]!=pieceType)
                antiDiamatch=false;
        }

        return rowMatch||colMatch||diaMatch||antiDiamatch;
    }

    string startGame(){
        bool noWinner = true;
        while(noWinner){
            Player playerTurn = players.front();
            players.pop_front();

            gameboard.printBoard();
            vector<pair<int,int>>freeSpaces=gameboard.getFreeCells();
            if(freeSpaces.size()==0){
                noWinner=false;
                continue;
            }

            //Read The user input 
            cout<<"Player: "+playerTurn.name+"\nEnter the row number:";
            int row, col;
            cin>>row;
            cout<<"Enter the column number: ";
            cin>>col;

            //Placing The piece 
            bool pieceAddedSuccesfully=gameboard.addPiece(row,col,playerTurn.playingPiece.piecetype);
            if(!pieceAddedSuccesfully){
                cout<<"Incorredt possition chosen, try again";
                players.push_front(playerTurn);
                continue;
            }
            players.push_back(playerTurn);
            bool winner = isThereWinner(row, col, playerTurn.playingPiece.piecetype);
            if(winner){
                return playerTurn.name;
            }
        }
        return "Tie";
    }
};


int main(){
    TicTacToe game;
    string winner = game.startGame();
    cout<<"The winner is : " << winner<<endl; 

}