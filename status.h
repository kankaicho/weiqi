#ifndef STATUS_H
#define STATUS_H

#define PLAYER_BOT  1
#define PLAYER_USER 2

typedef int PLAYER_TYPE;
typedef int STATUS;

enum {illegalpiece = -1, emptypiece = 0, blackpiece = 2, whitepiece = 3};

enum {x_lef = -1, x_rig = 1};
enum {y_up = -1, y_down = 1};

const int x_srd[4] = {-1,1,0,0};
const int y_srd[4] = {0,0,-1,1};


const STATUS NOT_FOUND = -1;
#endif
