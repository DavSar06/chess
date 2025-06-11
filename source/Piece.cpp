#include "Piece.hpp"
#include "Game.hpp"
#include "def.hpp"
#include <bits/stdc++.h>
using namespace std;

Piece::Piece(char color, char code) {
    this->color = color;
    if(color == 'b') code -= ' ';
    this->code = code;
    this->validMoves = {};
}

char Piece::getColor() {
    return this->color;
}
char Piece::getCode() {
    return this->code;
}

bool Piece::isValidMove(pii to) {
    for(auto &t: validMoves){
        if(t.first == to.first && t.second == to.second) return true;
    }
    return false;
}

void Piece::validateMoves(pii a) {
    vector<pii> tries = validMoves;
    validMoves.clear();
    for(auto& t: tries) {
        if(!Game::board_[t.first][t.second] || Game::board_[t.first][t.second]->getColor() != Game::board_[a.first][a.second]->getColor()) {
            auto* save = Game::board_[t.first][t.second];
            Game::board_[t.first][t.second] = Game::board_[a.first][a.second];
            Game::board_[a.first][a.second] = nullptr;
            Game::calculateOppMoves();
            if(!Game::testCheck()){
                validMoves.push_back(t);
            }
            Game::board_[a.first][a.second] = Game::board_[t.first][t.second];
            Game::board_[t.first][t.second] = save;
            Game::calculateOppMoves();
        }
    }
}
