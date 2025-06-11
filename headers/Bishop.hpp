#ifndef BISHOP_H
#define BISHOP_H
#include <bits/stdc++.h>
#include "Piece.hpp"
#include "def.hpp"

class Bishop: public Piece {
public:
    Bishop(char color): Piece::Piece(color, 'r') {}
    void calculateAllMoves(pii a);
    ~Bishop() = default;
};

#endif
