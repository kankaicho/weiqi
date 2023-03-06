#ifndef BOARD_FACTORY
#define BOARD_FACTORY

#include "board.h"
#include <memory>

class board_factory {
    public:
        board_ptr produce_board(const int& board_size)
        {
            board mboard;
            mboard.init_board(board_size);
            return std::make_unique<board>(mboard);
        }
};


#endif
