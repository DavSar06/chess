// #include "Game.hpp"
// #include <bits/stdc++.h>
// using namespace std;
//
// int main(){
//     Game::initBoard();
//     Game::displayBoard();
//
//     int x1,y1;
//     int x2,y2;
//     while(true){
//         cout<<"Input Coordinates of the piece you want to move: ";
//         cin>>x1>>y1;
//         cout<<"Input Coordinates where you want to move: ";
//         cin>>x2>>y2;
//         Game::movePiece({x1,y1},{x2,y2});
//         Game::displayBoard();
//
//         if(Game::endCheck()) break;
//     }
//     cout<<endl;
//
//
//     return 0;
// }


#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "def.hpp"
#include <bits/stdc++.h>

const int WINDOW_SIZE = 600;
const int SQUARE_SIZE = WINDOW_SIZE / 8;
const sf::Color LIGHT_SQUARE(240, 217, 181);
const sf::Color DARK_SQUARE(181, 136, 99);
const sf::Color TEXT_COLOR(70, 70, 70);
const sf::Color POSSIBLE_COLOR(100, 200, 100, 150);
const sf::Color HIGHLIGHT_COLOR(255, 100, 100, 150);
const float HIGHLIGHT_SQUARE_SIZE = SQUARE_SIZE * 0.8f;

int main() {
    Game::initBoard();
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Chess Board");

    // Load a font for the coordinates
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/chessnota.ttf")) {
        std::cerr << "Failed to load font! Using default." << std::endl;
        // You can proceed without font or handle the error differently
    }

    sf::Font textFont;
    if (!textFont.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Failed to load font! Using default." << std::endl;
        // You can proceed without font or handle the error differently
    }

    bool pieceSelected = false;
    int selectedRow = -1;
    int selectedCol = -1;
    vector<pii> possibleMoves;

    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }else if (event.type == sf::Event::MouseButtonPressed) {
              if (event.mouseButton.button == sf::Mouse::Left) {
                // Get clicked square
                int col = event.mouseButton.x / SQUARE_SIZE;
                int row = event.mouseButton.y / SQUARE_SIZE;

                auto& sq = Game::board_[row][col];

                if (!pieceSelected) {
                  // Select a piece if there is one
                  if (sq && (Game::moves % 2 == 1 && sq->getColor() == 'b' || Game::moves % 2 == 0 && sq->getColor() == 'w')){
                    selectedRow = row;
                    selectedCol = col;
                    pieceSelected = true;
                    // Get possible moves for this piece
                    possibleMoves = sq->validMoves;
                  }
                }
                else {  
                  // Try to move the selected piece
                  if (Game::board_[selectedRow][selectedCol]->isValidMove({row, col})) {
                    Game::movePiece({selectedRow, selectedCol}, {row, col});
                  }
                  // Reset selection
                  pieceSelected = false;
                  possibleMoves.clear();
                }
              }
            }
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Draw the chess board
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                sf::RectangleShape square(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
                square.setPosition(col * SQUARE_SIZE, row * SQUARE_SIZE);
                square.setFillColor((row + col) % 2 == 0 ? LIGHT_SQUARE : DARK_SQUARE);

                window.draw(square);

                if (pieceSelected && row == selectedRow && col == selectedCol) {
                    square.setFillColor(sf::Color(255, 255, 0, 150));
                    window.draw(square);
                }
                // Highlight possible moves
                else if (pieceSelected && std::find(possibleMoves.begin(), possibleMoves.end(), std::make_pair(row, col)) != possibleMoves.end()) {
                    bool isCapture = (Game::board_[row][col] != nullptr);
                    sf::RectangleShape highlightSquare(sf::Vector2f(HIGHLIGHT_SQUARE_SIZE, HIGHLIGHT_SQUARE_SIZE));
                    highlightSquare.setPosition(col * SQUARE_SIZE + SQUARE_SIZE/2.0f, row * SQUARE_SIZE + SQUARE_SIZE/2.0f);
                    highlightSquare.setOrigin(HIGHLIGHT_SQUARE_SIZE/2, HIGHLIGHT_SQUARE_SIZE/2);
                    highlightSquare.setFillColor(isCapture ? HIGHLIGHT_COLOR : POSSIBLE_COLOR);
                    if(isCapture) {
                      highlightSquare.setOutlineThickness(2);
                      highlightSquare.setOutlineColor(sf::Color(200, 50, 50, 200));
                    }
                    window.draw(highlightSquare);
                }
                else {
                    square.setFillColor((row + col) % 2 == 0 ? LIGHT_SQUARE : DARK_SQUARE);
                    window.draw(square);
                }

                if(Game::board_[row][col]){
                  sf::Text pieceText;
                  pieceText.setFont(font);
                  pieceText.setString(Game::board_[row][col]->getCode());
                  pieceText.setCharacterSize(SQUARE_SIZE * 0.65f);
                  sf::FloatRect bounds = pieceText.getLocalBounds();
                  pieceText.setFillColor(Game::board_[row][col]->getColor() == 'w' ? sf::Color::White : sf::Color::Black);
                  pieceText.setOrigin(bounds.left + bounds.width/2.0f, bounds.top + bounds.height/2.0f);
                  pieceText.setPosition(col * SQUARE_SIZE + SQUARE_SIZE/2.0f, row * SQUARE_SIZE + SQUARE_SIZE/2.0f);
                    
                  window.draw(pieceText);
                }
            }
        }

        // Draw the coordinates (letters a-h)
        for (int col = 0; col < 8; ++col) {
            sf::Text letter;
            letter.setFont(textFont);
            letter.setString(std::string(1, 'a' + col));
            letter.setCharacterSize(16);
            letter.setFillColor(TEXT_COLOR);
            
            // Position at the bottom of each file
            letter.setPosition(
                col * SQUARE_SIZE + SQUARE_SIZE - 20,  // Right-aligned in square
                WINDOW_SIZE - 20                       // Near bottom of window
            );
            window.draw(letter);
        }

        // Draw the coordinates (numbers 1-8)
        for (int row = 0; row < 8; ++row) {
            sf::Text number;
            number.setFont(textFont);
            number.setString(std::to_string(8 - row));
            number.setCharacterSize(16);
            number.setFillColor(TEXT_COLOR);
            
            // Position at the left of each rank
            number.setPosition(
                5,  // Near left edge
                row * SQUARE_SIZE + 5  // Top of square
            );
            window.draw(number);
        }

        if(Game::endCheck()){
          break;
        }

        // Display everything
        window.display();
    }
    return 0;
}
