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

class Game {
public:
    static vector<vector<Piece*>> board_;
    static set<pii> opponentMoves;
    static set<pii> playerMoves;
    static int moves;
    static vector<hmoves> history; 

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
