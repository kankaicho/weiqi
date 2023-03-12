#include "game.h"
#include "board_factory.h"
#include "player_factory.h"
#include "status.h"

#include <iostream>
#include <set>
#include <QDebug>

#define TRY_DFS

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
//    qDebug() << "cur cout:" << this->count << ",vec size:" << ps_vec.size();
//    for(int i = 0; i < ps_vec.size(); i ++) {
//        qDebug() << " \tqi:" << ps_vec[i].getQi();
//    }
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

STATUS game::make_board(board_ptr&& _mboard) {
    this->mboard = std::move(_mboard);
    return 0;
}

STATUS game::make_player(player_ptr&& p1, player_ptr&& p2) {
    this->p1 = std::move(p1);
    this->p2 = std::move(p2);
    return 0;
}

int game::get_piecetype(const int pos_x, const int pos_y) const
{
    return this->mboard->get_piecetype(pos_x,pos_y);
}

bool game::try_lazi(const int pos_x, const int pos_y, const int piecetype) {
    board nboard;
    int _size = this->mboard->get_size();
    nboard.init_board(_size);
    for(int i = 0; i < _size; i ++) {
        for(int j = 0; j < _size; j ++) {
            nboard.set_piecetype(i,j,this->mboard->get_piecetype(pos_x,pos_y));
        }
    }

    int trypiece = piecetype^1;

}


bool game::lazi(const int pos_x, const int pos_y, const int p_type) {

    if(this->mboard->get_piecetype(pos_x,pos_y) != emptypiece) {
        return false;
    }


#ifndef TRY_DFS
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
 #endif

}
