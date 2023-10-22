/**
*    @file: move.h
*  @author: Brendan Smyers
*    @date: October 19, 2023
*   @brief: Defines the "Move" struct
*
*/

#ifndef MOVE_H
#define MOVE_H

const unsigned short flag_mask          = 0b1111000000000000;
const unsigned short start_square_mask  = 0b0000111111000000;
const unsigned short target_square_mask = 0b0000000000111111;

// Move format is as follows (ffffsssssstttttt) => 4 bits for flags, 6 bits for (0-63) board index start, 6 for target index
// Bits 0-5: target square index
// Bits 6-11: start square index
// Bits 12-15: flag (promotion type, etc)
struct Move {
    private:
        unsigned short move = 0;
    public:
    Move() {}
    // User friendly move constructor that takes board positions in traditional chess notation
    Move(string start_str, string target_str) {
        /*
        * Converts basic algebraic chess notation to start and end index
        * The code below handles lowercase 'e4' or uppercase 'E4' notation
        * This is literally just a word around to not use another library (tolower)
        */
        int start_x = (int) start_str[0] - 97; // Casts char into ascii, then -97 to put 'a' on 0
        int target_x = (int) target_str[0] - 97;

        if (start_x  < 0) { start_x += 32; } // If the ascii would end up below 0 then it must have been in uppercase, then we fix it
        if (target_x < 0) { target_x += 32; }

        // I hate this \/ but it does what its supposed to do
        int start_index  = ((8 - (start_str[1] - '0')) * 8 + start_x);
        int target_index = ((8 - (target_str[1]- '0')) * 8 + target_x);

        move = (start_index << 6 | target_index);
    }

    // Direct assignment
    Move(unsigned short move) {
        this->move = move;
    }

    // Move from indexes
    Move(int start_index, int target_index) {
        move = (start_index << 6 | target_index);    
    }

    // Move from indexes + flag
    Move(int start_index, int target_index, int flags) {
        move = (flags << 10 | start_index << 6 | target_index);
    }

    // Accessors
    int flag() {
        return (move & flag_mask) >> 10;
    }
    int start_index() {
        return (move & start_square_mask) >> 6;
    }
    int target_index() {
        return (move & target_square_mask);
    }

    // Operators
    bool operator == (Move other) {
        return (this->start_index() == other.start_index() && this->target_index() == other.target_index());
    }
};

#endif