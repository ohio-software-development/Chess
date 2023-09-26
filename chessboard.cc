#include "chessboard.h"
#include <string>
#include <iostream>
using namespace std;

Chessboard::Chessboard() {
    reset();
    load_fen_string(default_fen);
}

Chessboard::Chessboard(const string fen_string) {
    reset();
    load_fen_string(fen_string);
}

void Chessboard::operator = (const Chessboard& other) {
    this->active_player         = other.active_player;

    this->white_rook_bitboard   = other.white_rook_bitboard;
    this->white_bishop_bitboard = other.white_bishop_bitboard;
    this->white_knight_bitboard = other.white_knight_bitboard;
    this->white_queen_bitboard  = other.white_queen_bitboard;
    this->white_king_bitboard   = other.white_king_bitboard;
    this->white_pawn_bitboard   = other.white_pawn_bitboard;

    this->black_rook_bitboard   = other.black_rook_bitboard;
    this->black_bishop_bitboard = other.black_bishop_bitboard;
    this->black_knight_bitboard = other.black_knight_bitboard;
    this->black_queen_bitboard  = other.black_queen_bitboard;
    this->black_king_bitboard   = other.black_king_bitboard;
    this->black_pawn_bitboard   = other.black_pawn_bitboard;
}

void Chessboard::reset() {
    white_rook_bitboard   = 0;
    white_bishop_bitboard = 0;
    white_knight_bitboard = 0;
    white_queen_bitboard  = 0;
    white_king_bitboard   = 0;
    white_pawn_bitboard   = 0;

    black_rook_bitboard   = 0;
    black_bishop_bitboard = 0;
    black_knight_bitboard = 0;
    black_queen_bitboard  = 0;
    black_king_bitboard   = 0;
    black_pawn_bitboard   = 0;
}

void Chessboard::load_fen_string(string fen_str) {
    reset();
    int board_index = 0;
    int fen_proccessed = 0; // The fen-string indexes proccessed so far
    char token;

    // ======== 1. Board State ========
    for (int i = 0; i < fen_str.length(); i++) {
        token = fen_str[i];

        // Token Gaurds
        if (token == ' ') { break; }
        if (token == '/') { fen_proccessed++; continue; }

        // cout << "ASCII: "<< (int) token << " Token: " << token << endl; // Debug

        // If the token is an offset
        if ((int) token >= 49 && (int) token <= 56) { // If ascii is between 49-56/1-8 inclusive
            board_index += (token - '0'); // Convert to num
            fen_proccessed++;
            continue;
        }
        // If the token is uppercase, it is white
        if ((int) token >= 65 && (int) token <= 90) { // If ascii is in capital letter range
            // White
            switch(token) {
                case 'P':                                       // The 1 must be a 64 bit number, otherwise we would hit a bit shift limit of 32
                    white_pawn_bitboard |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'R':
                    white_rook_bitboard |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'B':
                    white_bishop_bitboard |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'N':
                    white_knight_bitboard |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'Q':
                    white_queen_bitboard |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'K':
                    white_king_bitboard |= ((unsigned long long) 1 << (63 - board_index));
                    break;
            }
        } else {
            // Black
            switch(token) {
                case 'p':
                    black_pawn_bitboard |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'r':
                    black_rook_bitboard |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'b':
                    black_bishop_bitboard |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'n':
                    black_knight_bitboard |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'q':
                    black_queen_bitboard |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'k':
                    black_king_bitboard |= ((unsigned long long) 1 << (63 - board_index));
                    break;
            }
        }
        board_index++;
        fen_proccessed++;
    }

    // Incomplete Fen-String Gaurd
    if (fen_proccessed > fen_str.length()) { return; }
    
    // ======== 2. Active Player ========
    fen_proccessed++; // space character
    active_player = fen_str[fen_proccessed] == 'w' ? WHITE : BLACK;
    fen_proccessed++;

    // 3. Castle rights
        // Not implemented
    // 4. En passant targets
        // Not implemented
    // 5. Turn Counters
        // Not implemented
}

void Chessboard::display() {
    string output = board_str;
    for (int i = 0; i < 64; i++) {
        // White Pieces
        // These if-statements check if the index of the bit 'i' (left to right) is 1 (ON or TRUE) in the bitboard
        if (((white_pawn_bitboard >> 63 - i) & 1) == 1) { // White Pawns
            output[board_indexes[i]] = 'P';
        }
        if (((white_rook_bitboard >> 63 - i) & 1) == 1) { // White Rooks
            output[board_indexes[i]] = 'R';
        }
        if (((white_knight_bitboard >> 63 - i) & 1) == 1) { // White Knights
            output[board_indexes[i]] = 'N';
        }
        if (((white_bishop_bitboard >> 63 - i) & 1) == 1) { // White Bishops
            output[board_indexes[i]] = 'B';
        }
        if (((white_queen_bitboard >> 63 - i) & 1) == 1) { // White Queens
            output[board_indexes[i]] = 'Q';
        }
        if (((white_king_bitboard >> 63 - i) & 1) == 1) { // White King
            output[board_indexes[i]] = 'K';
        }

        // Black Pieces
        if (((black_pawn_bitboard >> 63 - i) & 1) == 1) { // Black Pawns
            output[board_indexes[i]] = 'p';
        }
        if (((black_rook_bitboard >> 63 - i) & 1) == 1) { // Black Rooks
            output[board_indexes[i]] = 'r';
        }
        if (((black_knight_bitboard >> 63 - i) & 1) == 1) { // Black Knights
            output[board_indexes[i]] = 'n';
        }
        if (((black_bishop_bitboard >> 63 - i) & 1) == 1) { // Black Bishops
            output[board_indexes[i]] = 'b';
        }
        if (((black_queen_bitboard >> 63 - i) & 1) == 1) { // Black Queens
            output[board_indexes[i]] = 'q';
        }
        if (((black_king_bitboard >> 63 - i) & 1) == 1) { // Black King
            output[board_indexes[i]] = 'k';
        }

    }
    cout << output << endl;
}

Chessboard Chessboard::make_move(Move move) {
    // Move format is as follows (ffffffttttttssss) => 6 bits for (0-63) board index start, 6 for target index, 4 flags (16 possible flags)
    // Bits 0-5: start square index
    // Bits 6-11: target square index
    // Bits 12-15: flag (promotion type, etc)

    // To be implemented
}