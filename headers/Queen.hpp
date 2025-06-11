#ifndef QUEEN_H
#define QUEEN_H
#include <bits/stdc++.h>
#include "Piece.hpp"
#include "def.hpp"

class Queen: public Piece {
public:
    Queen(char color): Piece::Piece(color, 'w') {}
    void calculateAllMoves(pii a);
    ~Queen() = default;
};

#endif
