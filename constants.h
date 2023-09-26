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
    KING    // 5
};

enum PieceColor {
    WHITE,
    BLACK
};

struct Move {
    unsigned short move = 0;
    PieceType type = PAWN; // Number (0-5) that represents the type
    Move() { };
    // User friendly move constructor that takes board positions in traditional chess notation
    //                                I do not like the solution of taking the type as an arguement
    Move(string start, string target, PieceType type) {
        this->type = type;

        // Convert start and target to index
        // This assumes column letter is lowercase
        int start_x = (int) start[0] - 97; // Casts char into ascii, then -97 to put 'a' on 0
        int target_x = (int) target[0] - 97;

        if (start_x  < 0) { start_x += 32; } // If the ascii would end up below 0 then it must have been in uppercase, then we fix it
        if (target_x < 0) { target_x += 32; }

        int start_index =  ((8 - (start[1] - '0')) * 8 + start_x);
        int target_index = ((8 - (target[1]- '0')) * 8 + target_x);

        // Set the move into short

        move |= (start_index << 10);
        move |= (target_index << 4);
        move |= 0b0000; // Any possible flags
    }
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