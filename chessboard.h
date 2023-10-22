#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "constants.h"
#include "move.h"
#include <vector>
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
         * @brief attempts to interpret as much of the given fen-string as possible and load it https://www.chess.com/terms/fen-chess
        */
        void load_fen_string(const string fen_str);

        /**
         * @brief displays the board in the terminal
        */
        void display() const;

        /**
         * @brief displays current gamestate information like, halfmove/fullmove clocks, active player, etc
        */
        void display_gamestate() const;

        /**
         * @brief Sets the current active player to the given piececolor enum
        */
        void set_active_player(PieceColor color) { active_player = color; };

        /**
         * @return an enum of the active player
        */
        PieceColor get_active_player() const { return active_player; };

        /**
         * @brief Makes a move on the current board
         * @param move a move to take
         * @param is_search if the move should be made recorded in the move history
         *         THIS FUNCTION ASSUMES THE MOVE IS LEGAL
        */
        void make_move(Move move, bool is_search = false);
        
        /**
         * @return a list of legal moves for the current player
        */
        vector<Move> generate_moves() const;

        // bool is_legal_move(Move move);
        
    private:
        /// Game state
        PieceColor active_player;
        int halfmove_clock; // Counts the amount of turns (black and white) since the last pawn move or capture. Game ends in draw at 100
        int fullmove_clock; // Incremented by 1 after every black move
        string en_passant_target;
        /// Castle Rights
        // castle_rights[WHITE][0] = white kingside
        // castle_rights[WHITE][1] = white queenside
        // castle_rights[BLACK][0] = black kingside
        // castle_rights[BLACK][1] = black queenside
        bool castle_rights[2][2];
        /// Bitboards
        // Bitboards are stored like this:
        // Pawn board   - 0 / PAWN enum
        // Knight board - 1 / KNIGHT
        // Bishop board - 2 / BISHOP
        // Rook board   - 3 / ROOK
        // Queen board  - 4 / QUEEN
        // King board   - 5 / KING
        unsigned long long bitboards[2][6];
        // Color Bitboard stored like this:
        // All White occupied squares     - 0
        // All Black occupied squares     - 1
        // Black & White occupied squares - 2
        unsigned long long color_bitboards[3];

        /// Pre Computed Attack Boards
        // Board index returns a bitboard of the legal attacks from that index
        unsigned long long king_attacks[64];
        unsigned long long knight_attacks[64];
        unsigned long long white_pawn_attacks[64];
        unsigned long long black_pawn_attacks[64];
        void compute_attack_boards();

        PieceType type_board[64];
};

#endif