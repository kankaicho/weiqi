#ifndef BOARD_H
#define BOARD_H

#include "status.h"
#include "Glog.h"
#include "chess_piece.h"
#include <memory>
#include <map>
#include <assert.h>

//enum {blackpiece = 2, whitepiece};

class board {
    public:
        void debug_info();
        STATUS init_board(const int _size);
        void set_meshmap(int pos_x, int pos_y, int _mesh) { this->mesh_map[pos_y][pos_x] = _mesh; }
        int get_meshmap(const int pos_x, const int pos_y) {return this->mesh_map[pos_y][pos_x]; }
        int get_piecetype(const int pos_x, const int pos_y);
        void set_piecetype(const int pos_x, const int pos_y, const int p_type);
        int get_size() const { return this->size; }
        void add_mesh() {this->mesh ++;}
        std::pair<int,int> get_pieceLoc(const int _mesh);
        void update(const int _label, pieceString& ps);
        const vector<int> update_opponent(const int _label, const int pos_x, const int pos_y);
        bool isDead(pieceString ps, const int pos_x, const int pos_y, std::map<int,int> surround_piecestring, int piecetype);
        bool lazi(const int x, const int y, const int type);
        void update_board();
        void update_check();
    private:
        int mesh = 0;
        int size;
        std::map<int, pieceString> ps_map;
//        std::vector<pieceString> ps_vec;
        int** mmap;
        int** mesh_map;
        int four_pieces[4];
        Glog mlog;
};

typedef std::unique_ptr<board> board_ptr;

#endif
