#ifndef BOARD_H
#define BOARD_H

#include "status.h"
#include "chess_piece.h"
#include <memory>
#include <assert.h>

//enum {blackpiece = 2, whitepiece};

class board {
    public:
        STATUS init_board(const int _size);

        int get_piecetype(const int pos_x, const int pos_y);
        void set_piecetype(const int pos_x, const int pos_y, const int p_type);
        int get_size() const { return this->size; }
        void add_mesh() {this->mesh ++;}
        std::pair<int,int> get_pieceLoc(const int _mesh);
        void update(const int _label, pieceString& ps, const int pos_x, const int pos_y);
        int update_opponent(const int _label, const int pos_x, const int pos_y);

        bool lazi(const int x, const int y, const int type);
        void update_board();
    private:
        int mesh = 0;
        int size;
        std::map<int, pieceString> ps_map;
        std::vector<pieceString> ps_vec;
        int** mmap;
};

typedef std::unique_ptr<board> board_ptr;

#endif
