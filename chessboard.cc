#include "chessboard.h"
#include "constants.h"
#include "move.h"
#include "Bitboard_Utils.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

Bitboard_Utility BB_Utils;

Chessboard::Chessboard() {
    clear();
    load_fen_string(default_fen);
    compute_attack_boards();
}

Chessboard::Chessboard(const string fen_string) {
    clear();
    load_fen_string(fen_string);
    compute_attack_boards();
}

void Chessboard::clear() {
    active_player = WHITE;
    halfmove_clock = 0;
    fullmove_clock = 0;
    en_passant_target = "";

    // Clear castle rights
    castle_rights[WHITE][0] = false;
    castle_rights[WHITE][1] = false;
    castle_rights[BLACK][0] = false;
    castle_rights[BLACK][1] = false;

    // Clear bitboards
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            bitboards[i][j] = 0;
        }
    }

    color_bitboards[WHITE] = 0;
    color_bitboards[BLACK] = 0;

    // Clear square type board
    for (int i = 0; i < 64; i++) {
        type_board[i] = NONE;
    }
}

void Chessboard::load_fen_string(const string fen_str) {
    clear();
    int board_index = 0;
    int fen_proccessed = 0; // The fen-string indexes proccessed so far
    char token;

    // ======== 1. Board State ========
    for (fen_proccessed = 0; fen_proccessed < fen_str.length(); fen_proccessed++) {
        token = fen_str[fen_proccessed];

        // Token Gaurds
        if (token == ' ') { break; }
        if (token == '/') { continue; }

        // cout << "ASCII: "<< (int) token << " Token: " << token << endl; // Debug

        // If the token is an offset
        if ((int) token >= 49 && (int) token <= 56) { // If ascii is a number between 1-8 inclusive
            board_index += (token - '0'); // Convert to num
            continue;
        }

        PieceColor color;
        // If the token is uppercase, it is white
        if (token >= 65 && token <= 90) {
            color = WHITE;
            token += 32; // To lowercase
        } else {
            color = BLACK;
        }

        switch(token) {
            case 'p':
                BB_Utils.Set_Bit(bitboards[color][PAWN], board_index);
                type_board[board_index] = PAWN;
                break;
            case 'n':
                BB_Utils.Set_Bit(bitboards[color][KNIGHT], board_index);
                type_board[board_index] = KNIGHT;
                break;
            case 'b':
                BB_Utils.Set_Bit(bitboards[color][BISHOP], board_index);
                type_board[board_index] = BISHOP;
                break;
            case 'r':
                BB_Utils.Set_Bit(bitboards[color][ROOK], board_index);
                type_board[board_index] = ROOK;
                break;
            case 'q':
                BB_Utils.Set_Bit(bitboards[color][QUEEN], board_index);
                type_board[board_index] = QUEEN;
                break;
            case 'k':
                BB_Utils.Set_Bit(bitboards[color][KING], board_index);
                type_board[board_index] = KING;
                break;
        }
        board_index++;
    }

    // Compile Colored Bitboards
    for (int i = 0; i < 6; i++) {
        color_bitboards[WHITE] |= bitboards[WHITE][i];
        color_bitboards[BLACK] |= bitboards[BLACK][i];
    }
    color_bitboards[2] = color_bitboards[0] | color_bitboards[1];
    
    // ======== 2. Active Player ========
    if (fen_proccessed >= fen_str.length()) { return; } // Exit if fen is proccessed

    fen_proccessed++; // space character
    active_player = fen_str[fen_proccessed] == 'w' ? WHITE : BLACK;
    fen_proccessed++;

    // ======== 3. Castle rights ========
    if (fen_proccessed >= fen_str.length()) { return; }

    fen_proccessed++; // space character
    while(fen_str[fen_proccessed] != ' ') {
        switch(fen_str[fen_proccessed]) {
            case 'K':
                // White Kingside Castle Rights
                castle_rights[WHITE][0] = true;
                break;
            case 'Q':
                // White Queenside Castle Rights
                castle_rights[WHITE][1] = true;
                break;
            case 'k':
                // Black Kingside Castle Rights
                castle_rights[BLACK][0] = true;
                break;
            case 'q':
                // Black Queenside Castle Rights
                castle_rights[BLACK][1] = true;
                break;
        }
        fen_proccessed++;
    }
    
    // ======== 4. En passant targets ========
    if (fen_proccessed >= fen_str.length()) { return; }
    fen_proccessed++; // space character before

    if (fen_str[fen_proccessed] == '-') { // No en-passant target
        fen_proccessed++;
    } else { // Valid en-passant target
        en_passant_target = fen_str.substr(fen_proccessed, 2);
        fen_proccessed += 2;
    }

    // ======== 5. Halfmove clock ========
    if (fen_proccessed >= fen_str.length()) { return; }
    fen_proccessed++; // space character before

    string halfmove_count = fen_str.substr(fen_proccessed, fen_str.find(' ', fen_proccessed) - fen_proccessed);
    halfmove_clock = stoi(halfmove_count);

    fen_proccessed += halfmove_count.length();

    // ======== 6. Fullmove clock ========
    if (fen_proccessed >= fen_str.length()) { return; }
    fen_proccessed++; // space character before

    string fullmove_count = fen_str.substr(fen_proccessed);
    fullmove_clock = stoi(fullmove_count);

    fen_proccessed += fullmove_count.length();
}

void Chessboard::display() const {
    string output = board_str;
    char piece_chars[12] = {'P','N','B','R','Q','K','p','n','b','r','q','k'};
    unsigned long long tmp_bitboard = 0;
    int piece_index = 0;

    // White Pieces
    for (int i = 0; i < 6; i++) {
        // Create a copy of each bitboard
        tmp_bitboard = bitboards[WHITE][(PieceType) i];

        while(tmp_bitboard != 0) {
            // Pop the pieces and add their respective chars to the board
            piece_index = BB_Utils.Pop_LSB(tmp_bitboard);
            output[board_indexes[piece_index]] = piece_chars[i];
        }
    }

    // Black Pieces
    for (int i = 0; i < 6; i++) {
        tmp_bitboard = bitboards[BLACK][(PieceType) i];

        while(tmp_bitboard != 0) {
            piece_index = BB_Utils.Pop_LSB(tmp_bitboard);
            output[board_indexes[piece_index]] = piece_chars[i+6];
        }
    }

    cout << output << endl;
}

void Chessboard::display_gamestate() const {
    cout << " Active Player: " << (active_player == WHITE ? "White" : "Black") << endl;
    cout << "Halfmove Clock: " << halfmove_clock << endl;
    cout << "Fullmove Clock: " << fullmove_clock << endl;
}

// Handles moving pieces without captures
void Chessboard::make_move(Move move, bool is_search) {
    unsigned short start  = move.start_index();
    unsigned short target = move.target_index();

    BB_Utils.Flip_Bits(bitboards[active_player][type_board[start]], start, target);

    BB_Utils.Flip_Bits(color_bitboards[active_player], start, target);

    type_board[target] = type_board[start];
    type_board[start] = NONE;

    // Swap the current turn
    active_player = active_player == WHITE ? BLACK : WHITE;
}

vector<Move> Chessboard::generate_moves() const { // Work in progress
    vector<Move> legal_moves;
    PieceColor non_active_player = active_player == WHITE ? BLACK : WHITE;

    // King moves
    unsigned long long king_bitboard = bitboards[active_player][KING];
    int king_index = BB_Utils.Pop_LSB(king_bitboard);
    unsigned long long king_attack_bitboard = king_attacks[king_index] & (king_attacks[king_index] ^ color_bitboards[active_player]);
    int target_index = BB_Utils.Pop_LSB(king_attack_bitboard);
    while (king_attack_bitboard != 0) {
        legal_moves.push_back(Move(king_index, target_index));
        target_index = BB_Utils.Pop_LSB(king_attack_bitboard);
    }
    // Pawn moves
    // Knight moves
    // Bishop moves
    // Rook moves
    // Queen moves

    return legal_moves;
}

void Chessboard::compute_attack_boards() { // Work in progress
    // King
    const int king_moves[8] = {9,8,7,1,-1,-7,-8,-9};
    for (int i = 0; i < 64; i++) {
        king_attacks[i] = 0; // Clear bitboard
        for (int j = 0; j < 8; j++) {
            BB_Utils.Set_Bit(king_attacks[i], i+king_moves[j]);
        }

        // Mask off moves that wrap around the board
        if(i % 7 == 0) { // If the king is on the H file
            king_attacks[i] &= not_A_file;
        } else if (i % 8 == 0) { // If king is on A file
            king_attacks[i] &= not_H_file;
        }
    }

    // Knight
    const int knight_moves[8] = {-17,-15,-10,-6,6,10,15,17};
    for (int i = 0; i < 64; i++) {
        knight_attacks[i] = 0; // Clear bitboard
        for (int j = 0; j < 8; j++) {
            BB_Utils.Set_Bit(knight_attacks[i], i+knight_moves[j]);
        }

        // Mask off moves that wrap around the board
        if (i % 6 == 0 || i % 7 == 0) { // If knight is on the G or H file
            knight_attacks[i] &= not_A_file & not_B_file;
        } else if (i % 8 == 0 || i % 9 == 0) { // If knight is on the A or B file
            knight_attacks[i] &= not_G_file & not_H_file;
        }
    }

    // Pawn
    const int white_pawn_attacked_squares[2] = {-9, -7};
    for (int i = 0; i < 64; i++) {
        white_pawn_attacks[i] |= 0; // Clear
        if (i <= 7) { // White pawns can't attack when they are on the eigth rank, also they promote
            continue;
        }
        BB_Utils.Set_Bit(white_pawn_attacks[i], i + white_pawn_attacked_squares[0]);
        BB_Utils.Set_Bit(white_pawn_attacks[i], i + white_pawn_attacked_squares[1]);
        // Clamp to board bounds
        if (i % 7 == 0) { // If pawn is on H file
            white_pawn_attacks[i] &= not_A_file;
        } else if (i % 8 == 0) { // If pawn is on A file
            white_pawn_attacks[i] &= not_H_file;
        }
    }

    const int black_pawn_attacked_squares[2] = {9, 7};
    for (int i = 0; i < 64; i++) {
        black_pawn_attacks[i] |= 0; // Clear
        if (i >= 55) { // Black pawns can't attack when they are on the first rank, also they promote
            continue;
        }
        BB_Utils.Set_Bit(black_pawn_attacks[i], i + black_pawn_attacked_squares[0]);
        BB_Utils.Set_Bit(black_pawn_attacks[i], i + black_pawn_attacked_squares[1]);
        // Clamp to board bounds
        if (i % 7 == 0) { // If pawn is on H file
            black_pawn_attacks[i] &= not_A_file;
        } else if (i % 8 == 0) { // If pawn is on A file
            black_pawn_attacks[i] &= not_H_file;
        }
    }
}