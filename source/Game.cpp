#include "Game.hpp"
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Queen.hpp"
#include "King.hpp"
#include "def.hpp"
#include <bits/stdc++.h>
using namespace std;

vector<vector<Piece*>> Game::board_ = vector<vector<Piece*>>(8, vector<Piece*>(8, nullptr));
vector<hmoves> Game::history{};
hmoves Game::lastMove;
vector<from_to> Game::enPassants{};
int Game::moves = 0;
set<pii> Game::opponentMoves = {};
set<pii> Game::playerMoves = {};
bool whiteKingMoved = false;
bool whiteRookKingSideMoved = false;
bool whiteRookQueenSideMoved = false;
bool blackKingMoved = false;
bool blackRookKingSideMoved = false;
bool blackRookQueenSideMoved = false;


Game::Game() {
    return;
}

/*

Initializing The Board

*/
void Game::initBoard() {
    for(auto &t: board_[1]) t = new Pawn('b');
    for(auto &t: board_[6]) t = new Pawn('w');
    board_[0][0] = new Rook('b');
    board_[0][7] = new Rook('b');
    board_[7][0] = new Rook('w');
    board_[7][7] = new Rook('w');
    board_[0][2] = new Bishop('b');
    board_[0][5] = new Bishop('b');
    board_[7][2] = new Bishop('w');
    board_[7][5] = new Bishop('w');
    board_[0][1] = new Knight('b');
    board_[0][6] = new Knight('b');
    board_[7][1] = new Knight('w');
    board_[7][6] = new Knight('w');
    board_[0][3] = new Queen('b');
    board_[7][3] = new Queen('w');
    board_[0][4] = new King('b');
    board_[7][4] = new King('w');


    // Test Cases
    // board_[3][4] = new King('b');
    // board_[6][5] = new Queen('b');
    // board_[4][6] = new Rook('b');
    // board_[5][5] = new Pawn('w');
    // board_[7][4] = new Rook('w');
    // board_[7][0] = new King('w');


    validMovesForAll();
}


void Game::calculateOppMoves(){
    opponentMoves.clear();
    int k = 1;
    int st = 7;
    if(moves%2==0){
        k = -1;
        st = 0;
    } 
    for(int i = 0; i < 8; i++){ 
        for(int j = 0; j < 8; j++){
            if(board_[i][j]) {
                char c = tolower(board_[i][j]->getCode());
                if(board_[i][j]->getColor() == 'w' && moves % 2 == 1 || board_[i][j]->getColor() == 'b' && moves % 2 == 0){
                    if(c == 'y'){
                        if(i - k != st){
                            if(j != 0) opponentMoves.insert({i-k,j-1});
                            if(j != 7) opponentMoves.insert({i-k,j+1});
                        }
                    }else {
        		        board_[i][j]->calculateAllMoves({i,j});
                        for(auto& t: board_[i][j]->validMoves) opponentMoves.insert(t);
                    }
                }   
            }
        }
    }
}

/*

Calculating All Moves

*/
void Game::validMovesForAll(){
    playerMoves.clear();
    calculateOppMoves();
    enPassants.clear();

    int f = 1;
    int t = 3;
    if(moves%2){
      f = 6;
      t = 4;
    }

    for(int i = 0; i < 8; i++){ 
        for(int j = 0; j < 8; j++){
            if(board_[i][j]) {
                if(board_[i][j]->getColor() == 'w' && moves % 2 == 0 || board_[i][j]->getColor() == 'b' && moves % 2 == 1){
        		    board_[i][j]->calculateAllMoves({i,j});
                    board_[i][j]->validateMoves({i,j});
                    for(auto& t: board_[i][j]->validMoves) playerMoves.insert(t);
                }
            }
        }
    }

    if (moves % 2 == 0 && whiteKingMoved == false) {
      if (whiteRookKingSideMoved == false) {
        bool canCastle = true;
        for (int i = 5; i < 7; i++){
          if(board_[7][i]) canCastle = false;
        }
        if(canCastle){
          for (int i = 5; i < 7; i++){
            board_[7][i] = board_[7][4];
            board_[7][4] = nullptr;
            calculateOppMoves();
            if(testCheck()) canCastle = false;
            board_[7][4] = board_[7][i];
            board_[7][i] = nullptr;
          }
          if (canCastle) board_[7][4]->validMoves.push_back({7,6});
        }
      }
      if(whiteRookQueenSideMoved == false){
        bool canCastle = true;
        for (int i = 3; i > 1; i--){
          if(board_[7][i]) canCastle = false;
        }
        if(canCastle){
          for (int i = 3; i > 1; i--){
            board_[7][i] = board_[7][4];
            board_[7][4] = nullptr;
            calculateOppMoves();
            if(testCheck()) canCastle = false;
            board_[7][4] = board_[7][i];
            board_[7][i] = nullptr;
          }
        }
        if (canCastle) board_[7][4]->validMoves.push_back({7,6});
      }
    }

    if (moves % 2 == 1 && blackKingMoved == false) {
      if (blackRookKingSideMoved == false) {
        bool canCastle = true;
        for (int i = 5; i < 7; i++){
          if(board_[0][i]) canCastle = false;
        }
        if(canCastle){
          for (int i = 5; i < 7; i++){
            board_[0][i] = board_[0][4];
            board_[0][4] = nullptr;
            calculateOppMoves();
            if(testCheck()) canCastle = false;
            board_[0][4] = board_[0][i];
            board_[0][i] = nullptr;
          }
          if (canCastle) board_[0][4]->validMoves.push_back({0,6});
        }
      }
      if(blackRookQueenSideMoved == false){
        bool canCastle = true;
        for (int i = 3; i > 1; i--){
          if(board_[0][i]) canCastle = false;
        }
        if(canCastle){
          for (int i = 3; i > 1; i--){
            board_[0][i] = board_[0][4];
            board_[0][4] = nullptr;
            calculateOppMoves();
            if(testCheck()) canCastle = false;
            board_[0][4] = board_[0][i];
            board_[0][i] = nullptr;
          }
        }
        if (canCastle) board_[0][4]->validMoves.push_back({0,6});
      }
    }


    vector<int> m{};
    if(tolower(lastMove.code) == 'y' && lastMove.from.first == f && lastMove.to.first == t) {
        if(lastMove.from.second > 0) m.push_back(-1);
        if(lastMove.from.second < 7) m.push_back(1);

        for(int i:m){
          auto& pn = board_[t][lastMove.from.second + i];
          if(pn != nullptr && tolower(pn->getCode()) == 'y' && pn->getColor() != lastMove.color){
            int x = (f+t)/2;
            int y = lastMove.from.second;
            pn->validMoves.push_back({x, y});
            enPassants.push_back({{t, lastMove.from.second + i}, {x, y}});
          }
        }
    }
}

/*

Displays the Chess board in terminal

*/
void Game::displayBoard() {
    cout<<"#";
    for(int i = 0; i < 8; i++){
        cout<<(char)('A'+i);
    }
    cout<<"#\n";

    for(int i = 0; i < 8; i++){
        cout << i + 1;
        for(int j = 0; j < 8; j++){
            if(board_[i][j] == nullptr){
                cout<<'.';
            }else {
                cout<<board_[i][j]->getCode();
            }
        }
        cout << i + 1;
        cout<<endl;
    }

    cout<<"#";
    for(int i = 0; i < 8; i++){
        cout<<(char)('A'+i);
    }
    cout<<"#\n";
}

/*

Tests Check for the one who has to move

*/
bool Game::testCheck() {
    int ki = 0, kj = 0;
    int c = 'q';
    if(moves % 2 == 1){
        c = 'Q';
    }

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board_[i][j] && board_[i][j]->getCode() == c) {
                ki = i;
                kj = j;
                break;
            }
        }
    }
    if(opponentMoves.contains({ki,kj})) return true;    
    return false;
}

/*

Moving piece from the coordinate "from" to coordinate "to" handling errors

Does not work yet

*/
void Game::movePiece(pii from, pii to){
    string errorMessage = "";
    bool err = false;

    if(board_[from.first][from.second]){
        if(board_[from.first][from.second]->getColor() == 'w' && moves % 2 == 0 || board_[from.first][from.second]->getColor() == 'b' && moves % 2){
            if(board_[from.first][from.second]->isValidMove(to)){
                bool isEnPassant = false;
                if (from.first == 7 && from.second == 0) whiteRookQueenSideMoved = true;
                if (from.first == 7 && from.second == 7) whiteRookKingSideMoved = true;
                if (from.first == 0 && from.second == 0) blackRookQueenSideMoved = true;
                if (from.first == 0 && from.second == 7) blackRookKingSideMoved = true;
                if (from.first == 7 && from.second == 4) whiteKingMoved = true;
                if (from.first == 0 && from.second == 4) blackKingMoved = true;

                if (tolower(board_[from.first][from.second]->getCode()) == 'q' && abs(from.second - to.second) > 1){
                  board_[to.first][to.second] = board_[from.first][from.second];
                  board_[from.first][from.second] = nullptr;
                  if (to.second > 4) {
                    board_[from.first][5] = board_[from.first][7];
                    board_[from.first][7] = nullptr;
                  }else {
                    board_[from.first][3] = board_[from.first][0];
                    board_[from.first][0] = nullptr;
                  }
                }else {
                  for (auto& z: enPassants) {
                    if (z.from.first == from.first && z.from.second == from.second && z.to.first == to.first && z.to.second == to.second) {
                      isEnPassant = true;
                    }
                  }
                  if (isEnPassant){
                    free(board_[from.first][to.second]);
                    board_[from.first][to.second] = nullptr;
                  }
                  else free(board_[to.first][to.second]);
                  
                  board_[to.first][to.second] = board_[from.first][from.second];
                  board_[from.first][from.second] = nullptr;
                }
                lastMove = {board_[to.first][to.second]->getColor(),board_[to.first][to.second]->getCode(),from,to};
                history.push_back(lastMove);
                moves++;
                validMovesForAll();
                
            }else {
                err = true;
                errorMessage = "Invalid Move \n";
            }
        }else {
            err = true;
            errorMessage = "Not Your Turn \n";
        }
    }else {
        err = true;
        errorMessage = "There Is No Piece In That Cell To Move \n";
    }

    if(err){
        cout<<errorMessage;
    }
}

bool Game::endCheck(){
    string side = "White";
    if(moves%2) side = "Black";
    if(!playerMoves.size()){
        if(testCheck()){
            cout<<side<<" is Checkmated!";
        }else {
            cout<<side<<" is in Stalemate!";
        }
        return true;
    }else return false;
}
