#include "Queen.hpp"
#include "Game.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include <bits/stdc++.h>
using namespace std;

void Queen::calculateAllMoves(pair<int,int> a) {
    validMoves.clear();

    auto r = new Rook(this->getColor());
    auto b = new Bishop(this->getColor());

    r->calculateAllMoves(a);
    b->calculateAllMoves(a);

    while(r->validMoves.size() || b->validMoves.size()){
        if(r->validMoves.size()){
            validMoves.push_back(r->validMoves[r->validMoves.size()-1]);
            r->validMoves.pop_back();
        }
        if(b->validMoves.size()){
            validMoves.push_back(b->validMoves[b->validMoves.size()-1]);
            b->validMoves.pop_back();
        }
    }

    free(r);
    free(b);
}
