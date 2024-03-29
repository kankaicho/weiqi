#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"
#include <vector>
#include <unordered_set>

typedef std::pair<int,int> op_unit;

class game {
    public:
        int get_piecetype(const int pos_x, const int pos_y) const;
        void init(const int& board_size, const PLAYER_TYPE& player1, const PLAYER_TYPE& player2);
        STATUS make_board(board_ptr&& _mboard);
        STATUS make_player(player_ptr&& p1, player_ptr&& p2);
        void debug_info();
        bool lazi(const int pos_x, const int pos_y, const int p_type);
    private:
        board_ptr mboard;
        player_ptr p1, p2;
};

#endif
