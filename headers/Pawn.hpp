#ifndef PAWN_H
#define PAWN_H
#include <bits/stdc++.h>
#include "Piece.hpp"
#include "def.hpp"

class Pawn: public Piece {
public:
    Pawn(char color): Piece::Piece(color, 'y') {};
    void calculateAllMoves(pii a);
    ~Pawn() = default;
};

#endif
