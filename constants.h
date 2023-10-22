#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>
#include <iostream>
using namespace std;

enum PieceType {
    PAWN,   // 0
    KNIGHT, // 1
    BISHOP, // 2
    ROOK,   // 3
    QUEEN,  // 4
    KING,   // 5
    NONE    // 6
};

enum PieceColor {
    WHITE,
    BLACK
};

enum Flags {
    NO_FLAG,
    EN_PASSANT,
    CASTLE_Q,
    CASTLE_K,
    PROMOTION
};

// const uint8_t pawn_moves[2] = {-8,-16}; // Will calculate possible en passant later, can also invert this for black
// Sliding moves will be calculated later

const unsigned long long not_A_file = 0b0111111101111111011111110111111101111111011111110111111101111111;
const unsigned long long not_B_file = 0b1011111110111111101111111011111110111111101111111011111110111111;
const unsigned long long not_G_file = 0b1111110111111101111111011111110111111101111110111111110111111101;
const unsigned long long not_H_file = 0b1111111011111110111111101111111011111110111111101111111011111110;

const string default_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0";

// Board is indexed from the top left
// Binary 0000...001 is top left, 1000...000 is bottom right
const string board_str = "+---+---+---+---+---+---+---+---+\n"
                         "|   |   |   |   |   |   |   |   | 8\n"
                         "+---+---+---+---+---+---+---+---+\n"
                         "|   |   |   |   |   |   |   |   | 7\n"
                         "+---+---+---+---+---+---+---+---+\n"
                         "|   |   |   |   |   |   |   |   | 6\n"
                         "+---+---+---+---+---+---+---+---+\n"
                         "|   |   |   |   |   |   |   |   | 5\n"
                         "+---+---+---+---+---+---+---+---+\n"
                         "|   |   |   |   |   |   |   |   | 4\n"
                         "+---+---+---+---+---+---+---+---+\n"
                         "|   |   |   |   |   |   |   |   | 3\n"
                         "+---+---+---+---+---+---+---+---+\n"
                         "|   |   |   |   |   |   |   |   | 2\n"
                         "+---+---+---+---+---+---+---+---+\n"
                         "|   |   |   |   |   |   |   |   | 1\n"
                         "+---+---+---+---+---+---+---+---+\n"
                         "  a   b   c   d   e   f   g   h";

const int board_indexes[64] = {36, 40, 44, 48, 52, 56, 60, 64,
                              106,110,114,118,122,126,130,134,
                              176,180,184,188,192,196,200,204,
                              246,250,254,258,262,266,270,274,
                              316,320,324,328,332,336,340,344,
                              386,390,394,398,402,406,410,414,
                              456,460,464,468,472,476,480,484,
                              526,530,534,538,542,546,550,554};

#endif