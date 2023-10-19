#include "constants.h"
#include "chessboard.h"
#include <iostream>
using namespace std;

string all_pawn_fen = "pppppppp/pppppppp/pppppppp/pppppppp/PPPPPPPP/PPPPPPPP/PPPPPPPP/PPPPPPPP w KQkq - 0 0";
string one_pawn_fen = "8/8/8/8/8/8/8/7P w KQkq - 0 0";
string kings_battle_fen = "4k3/8/8/8/8/8/8/4K3 w KQkq - 0 0";

int main() {
    Chessboard board(all_pawn_fen);
    string active_player;
    string start, target;
    int type;

    while (true) {
        active_player = board.get_active_player() == WHITE ? "White" : "Black";
        cout << "Active Player: " << active_player << endl;
        board.display();

        cout << "Enter the start square, target square, and piece type:" << endl;
        cin >> start;
        cin >> target;
        cin >> type;

        Move newMove(start, target);

        board.make_move(newMove);
    }

    return 0;
}