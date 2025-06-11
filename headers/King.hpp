#ifndef KING_H
#define KING_H
#include "Piece.hpp"
#include "def.hpp"
#include <bits/stdc++.h>

class King: public Piece {
public:
    King(char color): Piece::Piece(color, 'q') {}
    void calculateAllMoves(pii a);
    ~King() = default;
};

#endif
