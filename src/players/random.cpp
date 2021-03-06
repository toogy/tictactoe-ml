#include "random.h"
#include <vector>
#include <algorithm>

using namespace std;

RandomPlayer::RandomPlayer(short id) : Player(id)
{
}

RandomPlayer::~RandomPlayer()
{
}


short RandomPlayer::get_move(shared_ptr<Board> board) const
{
    auto moves = this->get_possible_moves(board);
    random_shuffle(moves->begin(), moves->end());
    return moves->at(0);
}

