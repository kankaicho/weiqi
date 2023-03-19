#include "Glog.h"

string Glog::cmd2str() {
    command _cmd = cmd.back();
    cmd.pop_back();
    string rets = "";
    rets += to_string(_cmd.type);
    rets += " ";
    rets += to_string(_cmd.lz_piece);
    rets += " ";
    rets += to_string(_cmd.rm_piece.size());
    rets += " ";
    for(int i = 0; i < _cmd.rm_piece.size(); i ++) {
        rets += to_string(_cmd.rm_piece[i]);
        rets += " ";
    }
    return rets;
}
