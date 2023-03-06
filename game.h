#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"
#include "chess_piece.h"
#include <vector>
#include <unordered_set>

typedef std::pair<int,int> op_unit;

class game {
    public:
        void init(const int& board_size, const PLAYER_TYPE& player1, const PLAYER_TYPE& player2);
        STATUS make_board(board_ptr&& _mboard);
        STATUS make_player(player_ptr&& p1, player_ptr&& p2);
        bool lazi(const int pos_x, const int pos_y, const int p_type);
        void add_count() {count ++;}
        void set_piecePool(const int pos_x, const int pos_y, const int _count);
        int get_pieceMesh(const int pos_x, const int pos_y);
        std::pair<int,int> get_pieceLoc(const int _mesh);
        void update(const int _label, pieceString& ps, const int pos_x, const int pos_y);
        int update_opponent(const int _label, const int pos_x, const int pos_y);
        int get_piecetype(int pos_x, int pos_y);

        void debug_info();

        bool try_lazi(const int pos_x, const int pos_y, const int piecetype);
    private:
        int count = 0;
        board_ptr mboard;
        player_ptr p1, p2;
        std::map<int, int> pieceCount_pool;
        std::map<int, int> pieceLoc_pool;
        std::map<int, pieceString> ps_map;
        std::vector<pieceString> ps_vec;
//        std::unordered_set<pieceString> ps_set;
};

#endif
