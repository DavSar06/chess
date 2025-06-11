#ifndef KNIGHT_H
#define KNIGHT_H
#include <bits/stdc++.h>
#include "Piece.hpp"
#include "def.hpp"

class Knight: public Piece {
public:
    Knight(char color): Piece::Piece(color, 't') {}
    void calculateAllMoves(pii a);
    ~Knight() = default;
};

#endif
