#ifndef GLOG_H
#define GLOG_H

#include <string>
#include <QQueue>
using namespace::std;

struct command {
    int type;
    int lz_piece;
    vector<int> rm_piece;
};

class Glog {
    public:
        void glog();
        string cmd2str();
        void addcmd(command _cmd) {cmd.push_back(_cmd);}
    private:
        QQueue<command> cmd;
};

#endif // GLOG_H
