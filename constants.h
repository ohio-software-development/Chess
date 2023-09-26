#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>
using namespace std;

enum PieceType {
    ROOK,
    BISHOP,
    KNIGHT,
    QUEEN,
    KING,
    PAWN
};

enum PieceColor {
    BLACK,
    WHITE
};

struct Move {
    unsigned short move = 0;
    PieceType type;
};

const unsigned short start_square_mask  = 0b1111110000000000;
const unsigned short target_square_mask = 0b0000001111110000;
const unsigned short flag_mask          = 0b0000000000001111;

const string default_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0";

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