#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "constants.h"
#include <vector>
#include <string>
using namespace std;

class Chessboard {
    public:
        // Constructors
        Chessboard();
        Chessboard(const string fen_string);
        Chessboard(const Chessboard& other);
        //Chessboard(const Chessboard& other);
        void operator = (const Chessboard& other);

        /**
         * @brief sets all the chessboard bitboards to 0 and sets the active player to white
        */
        void clear();

        /**
         * @brief changes the current board to the given fen-string https://www.chess.com/terms/fen-chess
        */
        void load_fen_string(string fen_str);

        /**
         * @brief displays the board in the terminal
        */
        void display() const;

        /**
         * @brief Sets the current active player to the given piececolor enum
        */
        void set_active_player(PieceColor color) { active_player = color; };

        /**
         * @return returns a new chessboard object after making the move
         *         THIS FUNCTION ASSUMES THE MOVE IS LEGAL
        */
        Chessboard make_move(Move move) const;
        
        /**
         * @return a list of legal moves for the current player
        */
        //vector<Move> generate_moves();
    private:
        // Game state
        PieceColor active_player;
        uint8_t halfmove_clock; // Counts the amount of turns (black and white) since the last pawn move or capture. Game ends in draw at 100
        uint8_t fullmove_clock; // Incremented by 1 after every black move
        /// Bitboards
        // Bitboards are stored like this:
        // Pawn board   - 0
        // Knight board - 1
        // Bishop board - 2
        // Rook board   - 3
        // Queeen board - 4
        // King board   - 5
        unsigned long long white_bitboards[6];
        unsigned long long black_bitboards[6];
};

#endif