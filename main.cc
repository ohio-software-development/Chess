#include "constants.h"
#include "chessboard.h"
#include <iostream>
using namespace std;

string all_pawn_fen = "PPPPPPPP/PPPPPPPP/PPPPPPPP/PPPPPPPP/PPPPPPPP/PPPPPPPP/PPPPPPPP/PPPPPPPP w KQkq - 0 0";
string one_pawn_fen = "8/8/8/8/8/8/8/7P w KQkq - 0 0";

int main() {
    Chessboard board;

    board.load_fen_string(default_fen);

    board.display();

    // Whites turn
    Move whites_move;   // 52   36
    whites_move.move = 0b1101001001000010;

    Chessboard afterWhite = board.make_move(whites_move);
    afterWhite.display();

    // Blacks turn
    Move blacks_move;
    blacks_move.move = 0b0010110110110001;
    blacks_move.type = 0;

    Chessboard blacksResponse = afterWhite.make_move(blacks_move);

    blacksResponse.display();

    return 0;
}