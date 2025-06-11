#ifndef PIECE_H
#define PIECE_H
#include "def.hpp"
#include <bits/stdc++.h>
using namespace std;

class Piece {
private:
    char color;
    char code;
public:
    vector<pii> validMoves;

    Piece(char color, char code);
    char getColor();
    char getCode();
    virtual void calculateAllMoves(pii a) = 0;
    bool isValidMove(pii to);
    void validateMoves(pii a);
    ~Piece() = default;
};


#endif
