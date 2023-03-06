#include "play_menu.h"
#define ON_BUG

game init(const int& board_size, const PLAYER_TYPE& player1, const PLAYER_TYPE& player2) {
    game mgame;

    board_factory bf;
    board_ptr b1 = bf.produce_board(board_size);
    mgame.make_board(std::move(b1));

    player_factory pf;
    player_ptr p1 = pf.produce(player1);
    player_ptr p2 = pf.produce(player2);
    mgame.make_player(std::move(p1),std::move(p1));

    return mgame;
}

void play(game& mgame) {
    #ifdef ON_BUG
        std::cout << "game start success!\n";
        
    #endif
    return;
}


void get_start(const int& board_size, const PLAYER_TYPE& player1, const PLAYER_TYPE& player2) {
    game mgame = init(board_size,player1,player2);
    play(mgame);
}
