#include <memory>
#include <utility>
#include <vector>
#include <algorithm>

#include "minmax.h"

using namespace std;

MinMax::MinMax(unsigned char id) : Player(id),
    oid(id == 1 ? 2 : 1)
{
}

MinMax::~MinMax()
{
}

unsigned char MinMax::get_move(shared_ptr<Board> board) const
{
    unsigned char move;
    int score;
    tie(move, score) = this->max(board);
    return move;
}


int MinMax::evaluate(shared_ptr<Board> board) const
{
    unsigned char winner_id = board->get_winner_id();
    if (winner_id == 4)
        return 0;
    if (winner_id == this->id)
        return 1;
    return -1;
}

pair<unsigned char, int> MinMax::max(shared_ptr<Board> board) const
{
    int best_score = -1000;
    auto best_moves = vector<unsigned char> {};
    auto moves = this->get_possible_moves(board);
    int score;
    unsigned char mtrash;
    for (auto& e : *moves)
    {
        board->update(e, this->id);
        
        if (board->is_over())
            score = this->evaluate(board);
        else
            tie(mtrash, score) = this->min(board);

        if (score == best_score)
            best_moves.push_back(e);
        else if (score > best_score)
        {
            best_score = score;
            best_moves.clear();
            best_moves.push_back(e);
        }
        
        board->undo(e);
    }
    random_shuffle(best_moves.begin(), best_moves.end());
    return make_pair(best_moves[0], best_score);
}

pair<unsigned char, int> MinMax::min(shared_ptr<Board> board) const
{
    int worst_score = 1000;
    auto worst_moves = vector<unsigned char> {};
    auto moves = this->get_possible_moves(board);
    int score;
    unsigned char mtrash;
    for (auto& e : *moves)
    {
        board->update(e, this->oid);
        
        if (board->is_over())
            score = this->evaluate(board);
        else
            tie(mtrash, score) = this->max(board);

        if (score == worst_score)
            worst_moves.push_back(e);
        else if (score < worst_score)
        {
            worst_score = score;
            worst_moves.clear();
            worst_moves.push_back(e);
        }
        
        board->undo(e);
    }
    random_shuffle(worst_moves.begin(), worst_moves.end());
    return make_pair(worst_moves[0], worst_score);
}
