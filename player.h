#ifndef PLAYER_H
#define PLAYER_H

#include "status.h"
#include <memory>

class player {
    public:
        virtual void play()  = 0;
        // virtual STATUS init(PLAYER_TYPE p_type) = 0;
        player() = default;
    // protected:
    //     PLAYER_TYPE type;
};

typedef std::unique_ptr<player> player_ptr;

class bot_player : public player {
    public:
        bot_player() = default;
        void play() override {return;}
};

class human_player : public player {
    public:
        human_player() = default;
        void play() override {return;}
};

#endif