#ifndef PLAY_MENU
#define PLAY_MENU

#include "status.h"
#include <iostream>
#include "game.h"
#include "player_factory.h"
#include "board_factory.h"

game init(const int& board_size, const PLAYER_TYPE& player1, const PLAYER_TYPE& player2);

void play(game& mgame);

void get_start(const int& board_size, const PLAYER_TYPE& player1, const PLAYER_TYPE& player2);

#endif