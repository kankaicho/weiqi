#include "board.h"
#include <QDebug>
#include <iostream>

STATUS board::init_board(const int _size)
{
    assert(_size > 0);
    this->size = _size;
    this->mmap = new int*[this->size]();
    this->mesh_map = new int*[this->size]();
    for(int i = 0; i < this->size; i++) {
        this->mmap[i] = new int[this->size]();
        this->mesh_map[i] = new int[this->size]();
    }
    return 0;
}

void board::debug_info()
{
//    qDebug() << "cur mesh:" << this->mesh << ",ps_map size:" << ps_map.size();
//    for(auto i = ps_map.begin(); i != ps_map.end(); i ++) {
//        qDebug() << " \tqi:" << (*i).second.getQi() << "; chess num:" << (*i).second.getSize();
//    }
    string buginfo = this->mlog.cmd2str();
    qDebug() << buginfo.c_str();
}

void board::update_check() {
    for(auto iter = ps_map.begin(); iter != ps_map.end(); iter ++) {
        for(int i = 0; i < iter->second.getSize(); i ++) {
            auto loc = pieceString::decryption(iter->second.get_piece(i).second);
            int x = loc.first, y = loc.second;
            for(int j = 0; j < 4; j ++) {
                if(this->get_piecetype(x+x_srd[j],y+y_srd[j]) == emptypiece)
                    iter->second.freeloc.insert(pieceString::encryption(x+x_srd[j],y+y_srd[j]));
            }
        }
    }
}

int board::get_piecetype(const int pos_x, const int pos_y)
{
    if(pos_x < 0 || pos_x >= this->size || pos_y < 0 || pos_y >= this->size)
        return illegalpiece;
    return this->mmap[pos_y][pos_x];
}

void board::set_piecetype(const int pos_x, const int pos_y, const int p_type)
{
    this->mmap[pos_y][pos_x] = p_type;
}

bool board::isDead(pieceString ps, const int pos_x, const int pos_y, std::map<int,int> surround_piecestring, int piecetype) {
    std::map<int, pieceString> _ps_map = this->ps_map;

    for(auto iter = surround_piecestring.begin(); iter != surround_piecestring.end();iter ++) {
        int i = iter->second;
        int _label = iter->first;
        if(four_pieces[i] == piecetype) {
            ps.combine_string(_ps_map[_label]);
            _ps_map.erase(_label);
        }
        else if((four_pieces[i] ^ piecetype) == opponent) {
            _ps_map[_label].freeloc.erase(pieceString::encryption(pos_x,pos_y));
            if(_ps_map[_label].getQi() == 0) return false;
        }
    }

    if(ps.getQi() == 0) return true;
    return false;
}

bool board::lazi(const int pos_x, const int pos_y, const int piecetype)
{
    if(this->get_piecetype(pos_x,pos_y) != emptypiece) return false;

    for(int i = 0; i < 4; i ++) {
        four_pieces[i] = this->get_piecetype(pos_x+x_srd[i],pos_y+y_srd[i]);
    }

    pieceString ps;
    chess c(this->mesh,pos_x,pos_y);
    ps.init_piece(c);
    for(int i = 0; i < 4; i ++) {
        if(four_pieces[i] == emptypiece)
            ps.freeloc.insert(pieceString::encryption(pos_x+x_srd[i],pos_y+y_srd[i]));
    }

    std::map<int,int> surround_piecestring;
    for(int i = 0; i < 4; i ++) {
        if(four_pieces[i] == emptypiece || four_pieces[i] == illegalpiece) continue;

        int piece_mesh = this->get_meshmap(pos_x+x_srd[i],pos_y+y_srd[i]);
        for(auto iter = this->ps_map.begin(); iter != this->ps_map.end(); iter ++) {
            int label = (*iter).second.find_piece(piece_mesh);
            if(label != -1) {
                surround_piecestring[label] = i;
                break;
            }
        }
    }

    if(isDead(ps,pos_x,pos_y,surround_piecestring,piecetype)) return false;

    command mcmd;
    mcmd.type = piecetype;
    mcmd.lz_piece = pieceString::encryption(pos_x,pos_y);

    for(auto iter = surround_piecestring.begin(); iter != surround_piecestring.end();iter ++) {
        int i = iter->second;
        if(four_pieces[i] == piecetype) {
            this->update(iter->first,ps);
        }
        else if((four_pieces[i] ^ piecetype) == opponent) {
            auto ret = this->update_opponent(iter->first, pos_x,pos_y);
            mcmd.rm_piece.insert(mcmd.rm_piece.end(),ret.begin(),ret.end());
        }
    }

    this->ps_map[ps.get_label()] = ps;
    this->set_piecetype(pos_x,pos_y,piecetype);
    this->set_meshmap(pos_x,pos_y,this->mesh);

    this->mlog.addcmd(mcmd);
    this->add_mesh();

    return true;
}


void board::update(const int _label, pieceString& ps)
{
    ps.combine_string(this->ps_map[_label]);
    this->ps_map.erase(_label);
    return;
}

const vector<int> board::update_opponent(int _label, const int pos_x, const int pos_y)
{
    vector<int> ret;
    ps_map[_label].freeloc.erase(pieceString::encryption(pos_x,pos_y));
    if(ps_map[_label].getQi() == 0) {
        for(int i = 0; i < ps_map[_label].getSize(); i ++) {
            piece_info pi = ps_map[_label].get_piece(i);
            auto li = pieceString::decryption(pi.second);
            this->set_piecetype(li.first,li.second,emptypiece);
            ret.push_back(pieceString::encryption(pos_x,pos_y));
        }
        this->ps_map.erase(_label);
        this->update_check();
    }
    return ret;
}
