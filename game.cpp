#include "game.h"
#include "board_factory.h"
#include "player_factory.h"
#include "status.h"

#include <iostream>
#include <set>
#include <QDebug>

void game::debug_info()
{
//    for(auto i = ps_vec.begin(); i != ps_vec.end(); i ++)
//    {
//        std::cout << "label:" << i->get_pieceString_label() << '\n';
//        for(int j = 0; j < i->getSize(); j ++)
//        {
//            std::cout << " " << i->getPiece(j);
//        }
//        std::cout << '\n';
//    }
    qDebug() << "cur cout:" << this->count << ",vec size:" << ps_vec.size();
    for(int i = 0; i < ps_vec.size(); i ++) {
        qDebug() << "\tqi:" << ps_vec[i].getQi();
    }
}

void game::init(const int& board_size, const PLAYER_TYPE& player1, const PLAYER_TYPE& player2) {
    board_factory bf;
    board_ptr b1 = bf.produce_board(board_size);
    this->make_board(std::move(b1));

    player_factory pf;
    player_ptr p1 = pf.produce(player1);
    player_ptr p2 = pf.produce(player2);
    this->make_player(std::move(p1),std::move(p2));
}

int game::get_piecetype(int pos_x, int pos_y)
{
    return this->mboard->get_piecetype(pos_x,pos_y);
}

STATUS game::make_board(board_ptr&& _mboard) {
    this->mboard = std::move(_mboard);
    return 0;
}

STATUS game::make_player(player_ptr&& p1, player_ptr&& p2) {
    this->p1 = std::move(p1);
    this->p2 = std::move(p2);
    return 0;
}

void game::set_piecePool(const int pos_x, const int pos_y, const int _mesh) {
    int count_key = pos_x*1000+pos_y;
    int loc_key = _mesh;
    this->pieceCount_pool[count_key] = _mesh;
    this->pieceLoc_pool[loc_key] = count_key;
}

int game::get_pieceMesh(const int pos_x, const int pos_y) {
    int mesh_key = pos_x*1000+pos_y;
    if(this->pieceCount_pool.find(mesh_key) == this->pieceCount_pool.end())
        return NOT_FOUND;
    return this->pieceCount_pool[mesh_key];
}

std::pair<int,int> game::get_pieceLoc(const int _mesh)
{
    int loc_key = _mesh;
    int loc_value = this->pieceLoc_pool[loc_key];
    int pos_x = loc_value/1000;
    int pos_y = loc_value%1000;
    return std::make_pair(pos_x,pos_y);
}

void game::update(const int _label, pieceString& ps, const int pos_x, const int pos_y)
{
    ps.combine_pieceString(this->ps_map[_label]);
    this->ps_map.erase(_label);

    for(auto i = ps_vec.begin(); i != ps_vec.end(); i ++) {
        if(i->get_pieceString_label() == _label) {
            ps_vec.erase(i);
            break;
        }
    }
    return;
}

int game::update_opponent(int _label, const int pos_x, const int pos_y)
{
    this->ps_map[_label].updateQi(-1);
    if(this->ps_map[_label].getQi() == 0)
    {
        for(int i = 0; i < ps_map[_label].getSize(); i ++) {
            int piece = ps_map[_label].getPiece(i);
            auto loc_info = this->get_pieceLoc(piece);
            this->mboard->set_piecetype(loc_info.first,loc_info.second,emptypiece);
        }
        this->ps_map.erase(_label);

        for(auto i = ps_vec.begin(); i != ps_vec.end(); i ++) {
            if(i->get_pieceString_label() == _label) {
                ps_vec.erase(i);
                break;
            }
        }
    }
    return 0;
}


bool game::lazi(const int pos_x, const int pos_y, const int p_type) {
    if(this->mboard->get_piecetype(pos_x,pos_y) != emptypiece) {
        return false;
    }

    int piece_surround[4];
    for(int i = 0; i < 4; i ++) {
        piece_surround[i] = this->mboard->get_piecetype(pos_x+x_srd[i],pos_y+y_srd[i]);
    }

    int ini_qi = 0;
    for(int i = 0; i < 4; i ++) {
        if(piece_surround[i] == emptypiece) ini_qi++;
    }

    if(ini_qi == 0) return false;

    this->add_count();

    pieceString ps;
    ps.add_piece(this->count);
    ps.setQi(ini_qi);

    std::map<int,int> surround_ps_map;
    surround_ps_map.clear();
    for(int i = 0; i < 4; i ++) {
        if(piece_surround[i] == emptypiece || piece_surround[i] == illegalpiece) continue;

        int piece_mesh = this->get_pieceMesh(pos_x+x_srd[i],pos_y+y_srd[i]);
        for(auto iter = this->ps_vec.begin(); iter != this->ps_vec.end(); iter ++) {
            int label = (*iter).find_piece(piece_mesh);
            if((label != -1)) {
                if(surround_ps_map.find(label) == surround_ps_map.end())
                    surround_ps_map[label] = i;
                break;
            }
        }
    }

    for(auto iter = surround_ps_map.begin(); iter != surround_ps_map.end();iter ++) {
        int i = iter->second;
        if(piece_surround[i] == p_type) this->update(iter->first,ps, pos_x+x_srd[i],pos_y+y_srd[i]);
        else if((piece_surround[i] ^ p_type) == 1) this->update_opponent(iter->first, pos_x+x_srd[i],pos_y+y_srd[i]);
    }

    this->ps_map[ps.get_pieceString_label()] = ps;
    this->ps_vec.push_back(ps);

    this->mboard->set_piecetype(pos_x,pos_y,p_type);
    this->set_piecePool(pos_x,pos_y,this->count);
    return true;

}
