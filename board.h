#ifndef BOARD_H
#define BOARD_H

#include "status.h"
#include <memory>
#include <assert.h>

//enum {blackpiece = 2, whitepiece};

class board {
    public:
        STATUS init_board(const int& _size)
        {
            assert(_size > 0);
            this->size = _size;
            this->mmap = new int*[this->size]();
            for(int i = 0; i < this->size; i++) {
                this->mmap[i] = new int[this->size]();
            }
            return 0;
        }

        int get_piecetype(int pos_x, int pos_y);
        void set_piecetype(const int pos_x, const int pos_y, const int p_type);
    private:
        int** mmap;
        int size;
};

typedef std::unique_ptr<board> board_ptr;

#endif
