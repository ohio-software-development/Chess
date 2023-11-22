#include "chessboard.h"
#include <iostream>
#include <vector>
using namespace std;

string all_pawn_fen = "pppppppp/pppppppp/pppppppp/pppppppp/PPPPPPPP/PPPPPPPP/PPPPPPPP/PPPPPPPP w KQkq - 0 0";
string one_pawn_fen = "P7/8/8/8/8/8/8/8 w KQkq - 22 59";
string kings_battle_fen = "4k3/8/8/8/8/8/8/4K3 w KQkq - 0 0";

int main() {
    Chessboard board(kings_battle_fen);
    string active_player;
    string start, target;
    vector<Move> moves;

    while (true) {
        active_player = board.get_active_player() == WHITE ? "White" : "Black";
        cout << "Active Player: " << active_player << endl;
        board.display();

        moves = board.generate_moves();

        for (int i = 0; i < moves.size(); i++) {
            cout << "Start Index: " << moves[i].start_index() << " Target Index: " << moves[i].target_index() << endl;
        }

        cout << "Start Square: ";
        cin >> start;
        cout << "Target Square: ";
        cin >> target;

        Move newMove(start, target);

        board.make_move(newMove);
    }

    return 0;
}