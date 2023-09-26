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

    return 0;
}