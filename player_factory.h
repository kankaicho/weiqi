#ifndef PLAYER_FACTORY
#define PLAYER_FACTORY

#include "player.h"

class player_factory {
    public:
        player_ptr produce(const PLAYER_TYPE player_info) {
            switch (player_info)
            {
            case PLAYER_BOT:
                return std::make_unique<bot_player>(bot_player{});
                break;
            
            case PLAYER_USER:
                return std::make_unique<human_player>(human_player{});
                break;
            }

            return nullptr;
        }
};

#endif