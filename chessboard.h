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
         * @brief sets all the chessboard bitboards to 0
        */
        void reset();

        /**
         * @brief changes the current board to the given fen-string https://www.chess.com/terms/fen-chess
        */
        void load_fen_string(string fen_str);

        /**
         * @brief displays the board in the terminal
        */
        void display();

        /**
         * @return returns a chessboard of the game after making the 
        */
        Chessboard make_move(Move move);
        
        /**
         * @return a list of legal moves for the current player
        */
        //vector<Move> generate_moves();
    private:
        // Game state
        PieceColor active_player;
        // Bitboards
        unsigned long long white_rook_bitboard;
        unsigned long long white_bishop_bitboard;
        unsigned long long white_knight_bitboard;
        unsigned long long white_queen_bitboard;
        unsigned long long white_king_bitboard;
        unsigned long long white_pawn_bitboard;

        unsigned long long black_rook_bitboard;
        unsigned long long black_bishop_bitboard;
        unsigned long long black_knight_bitboard;
        unsigned long long black_queen_bitboard;
        unsigned long long black_king_bitboard;
        unsigned long long black_pawn_bitboard;
};

#endif