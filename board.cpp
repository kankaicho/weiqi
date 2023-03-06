#include "board.h"

int board::get_piecetype(int pos_x, int pos_y)
{
    if(pos_x < 0 || pos_x >= this->size || pos_y < 0 || pos_y >= this->size)
        return illegalpiece;
    return this->mmap[pos_y][pos_x];
}


void board::set_piecetype(const int pos_x, const int pos_y, const int p_type)
{
    this->mmap[pos_y][pos_x] = p_type;
}
