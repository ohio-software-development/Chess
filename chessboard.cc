#include "chessboard.h"
#include "constants.h"
#include <string>
#include <iostream>
using namespace std;

Chessboard::Chessboard() {
    clear();
    load_fen_string(default_fen);
}

Chessboard::Chessboard(const string fen_string) {
    clear();
    load_fen_string(fen_string);
}

Chessboard::Chessboard(const Chessboard& other) {
    clear();
    this->active_player = other.active_player;

    // White bitboards
    for (int i = 0; i < 6; i++) {
        this->white_bitboards[i] = other.white_bitboards[i];
    }
    // Black bitboards
    for (int i = 0; i < 6; i++) {
        this->black_bitboards[i] = other.black_bitboards[i];
    }
}

void Chessboard::operator = (const Chessboard& other) {
    this->active_player = other.active_player;

    // White bitboards
    for (int i = 0; i < 6; i++) {
        this->white_bitboards[i] = other.white_bitboards[i];
    }
    // Black bitboards
    for (int i = 0; i < 6; i++) {
        this->black_bitboards[i] = other.black_bitboards[i];
    }
}

void Chessboard::clear() {
    active_player = WHITE;

    // White bitboards
    for (int i = 0; i < 6; i++) {
        white_bitboards[i] = 0;
    }
    // Black bitboards
    for (int i = 0; i < 6; i++) {
        black_bitboards[i] = 0;
    }
}

void Chessboard::load_fen_string(string fen_str) {
    clear();
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
                    white_bitboards[0] |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'N':
                    white_bitboards[1] |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'B':
                    white_bitboards[2] |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'R':
                    white_bitboards[3] |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'Q':
                    white_bitboards[4] |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'K':
                    white_bitboards[5] |= ((unsigned long long) 1 << (63 - board_index));
                    break;
            }
        } else {
            // Black
            switch(token) {
                case 'p':                                       // The 1 must be a 64 bit number, otherwise we would hit a bit shift limit of 32
                    black_bitboards[0] |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'n':
                    black_bitboards[1] |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'b':
                    black_bitboards[2] |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'r':
                    black_bitboards[3] |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'q':
                    black_bitboards[4] |= ((unsigned long long) 1 << (63 - board_index));
                    break;
                case 'k':
                    black_bitboards[5] |= ((unsigned long long) 1 << (63 - board_index));
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

void Chessboard::display() const {
    string output = board_str;
    for (int i = 0; i < 64; i++) {
        // White Pieces
        // These if-statements check if the index of the bit 'i' (left to right) is 1 (ON or TRUE) in the bitboard
        if (((white_bitboards[0] >> 63 - i) & 1) == 1) { // White Pawns
            output[board_indexes[i]] = 'P';
        }
        if (((white_bitboards[1] >> 63 - i) & 1) == 1) { // White Knights
            output[board_indexes[i]] = 'N';
        }
        if (((white_bitboards[2] >> 63 - i) & 1) == 1) { // White Bishops
            output[board_indexes[i]] = 'B';
        }
        if (((white_bitboards[3] >> 63 - i) & 1) == 1) { // White Rooks
            output[board_indexes[i]] = 'R';
        }
        if (((white_bitboards[4] >> 63 - i) & 1) == 1) { // White Queens
            output[board_indexes[i]] = 'Q';
        }
        if (((white_bitboards[5] >> 63 - i) & 1) == 1) { // White King
            output[board_indexes[i]] = 'K';
        }

        // Black Pieces
        if (((black_bitboards[0] >> 63 - i) & 1) == 1) { // Black Pawns
            output[board_indexes[i]] = 'p';
        }
        if (((black_bitboards[1] >> 63 - i) & 1) == 1) { // Black Knights
            output[board_indexes[i]] = 'n';
        }
        if (((black_bitboards[2] >> 63 - i) & 1) == 1) { // Black Bishops
            output[board_indexes[i]] = 'b';
        }
        if (((black_bitboards[3] >> 63 - i) & 1) == 1) { // Black Rooks
            output[board_indexes[i]] = 'r';
        }
        if (((black_bitboards[4] >> 63 - i) & 1) == 1) { // Black Queens
            output[board_indexes[i]] = 'q';
        }
        if (((black_bitboards[5] >> 63 - i) & 1) == 1) { // Black King
            output[board_indexes[i]] = 'k';
        }

    }
    cout << output << endl;
}

Chessboard Chessboard::make_move(Move move) const {
    // Move format is as follows (ffffffttttttssss) => 6 bits for (0-63) board index start, 6 for target index, 4 flags (16 possible flags)
    // Bits 0-5: start square index
    // Bits 6-11: target square index
    // Bits 12-15: flag (promotion type, etc)

    Chessboard newBoard(*this);

    unsigned short start_square  = ((move.move & start_square_mask) >> 10);
    unsigned short target_square = ((move.move & target_square_mask) >> 4);
    unsigned short flag          = ((move.move & flag_mask));

    if (active_player == WHITE) {
        // Flips the bit at the start square (probably should set it instead)
        newBoard.white_bitboards[move.type] ^= ((unsigned long long) 1 << (63 - start_square));
        // Set destination square to 1
        newBoard.white_bitboards[move.type] |= ((unsigned long long) 1 << (63 - target_square));
    } else {
        // Same this for black bitboard
        newBoard.black_bitboards[move.type] ^= ((unsigned long long) 1 << (63 - start_square));
        newBoard.black_bitboards[move.type] |= ((unsigned long long) 1 << (63 - target_square));
    }

    // Swap the current turn
    newBoard.set_active_player(active_player == WHITE ? BLACK : WHITE);

    return newBoard;
    // How do I know which bitboard to check?
    // I know the active player so that cuts my search space in half
    // I don't know what type the piece is so I will have to search all the bitboards (indexing 6 bitboards max) O(n)
    // I do know that the bit in that index is only ON in one of the bitboards
    // If I know what piece it is, the speed will be O(1)

}