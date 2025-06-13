#ifndef GAME_H
#define GAME_H
#include <bits/stdc++.h>
#include "Piece.hpp"
#include "def.hpp"
using namespace std;

struct hmoves {
    char color;
    char code; 
    pii from; 
    pii to;  
};

struct from_to {
  pii from;
  pii to;
};

class Game {
public:
    static vector<vector<Piece*>> board_;
    static set<pii> opponentMoves;
    static set<pii> playerMoves;
    static int moves;
    static vector<hmoves> history; 
    static hmoves lastMove;
    static vector<from_to> enPassants;
    Game();
    static void initBoard();
    static void displayBoard();
    static bool testCheck();
    static void movePiece(pii from, pii to);
    static void calculateOppMoves();
    static void validMovesForAll();
    static bool endCheck();
};

#endif
