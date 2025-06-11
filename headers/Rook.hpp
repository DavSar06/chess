#ifndef ROOK_H
#define ROOK_H
#include <bits/stdc++.h>
#include "Piece.hpp"
#include "def.hpp"

class Rook: public Piece {
public:
    Rook(char color): Piece::Piece(color, 'e') {};
    void calculateAllMoves(pii a);
    ~Rook() = default;
};

#endif
