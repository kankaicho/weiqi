#include "board.h"

STATUS board::init_board(const int _size)
{
    assert(_size > 0);
    this->size = _size;
    this->mmap = new int*[this->size]();
    for(int i = 0; i < this->size; i++) {
        this->mmap[i] = new int[this->size]();
    }
    return 0;
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

bool board::lazi(const int pos_x, const int pos_y, const int piecetype)
{
    if(mmap[pos_x][pos_y] != emptypiece) return false;

//    int piece_surround[4];
//    for(int i = 0; i < 4; i ++) {
//        piece_surround[i] = this->get_piecetype(pos_x+x_srd[i],pos_y+y_srd[i]);
//    }

//    int ini_qi = 0;
//    for(int i = 0; i < 4; i ++) {
//        if(piece_surround[i] == emptypiece) ini_qi++;
//    }

//    if(ini_qi == 0) return false;

//    this->add_mesh();

//    pieceString ps;
//    chess c();
//    ps.init_piece(this->mesh);
//    ps.setQi(ini_qi);

//    std::map<int,int> surround_ps_map;
//    surround_ps_map.clear();
//    for(int i = 0; i < 4; i ++) {
//        if(piece_surround[i] == emptypiece || piece_surround[i] == illegalpiece) continue;

//        int piece_mesh = this->get_pieceMesh(pos_x+x_srd[i],pos_y+y_srd[i]);
//        for(auto iter = this->ps_vec.begin(); iter != this->ps_vec.end(); iter ++) {
//            int label = (*iter).find_piece(piece_mesh);
//            if((label != -1)) {
//                if(surround_ps_map.find(label) == surround_ps_map.end())
//                    surround_ps_map[label] = i;
//                break;
//            }
//        }
//    }

//    for(auto iter = surround_ps_map.begin(); iter != surround_ps_map.end();iter ++) {
//        int i = iter->second;
//        if(piece_surround[i] == p_type) this->update(iter->first,ps, pos_x+x_srd[i],pos_y+y_srd[i]);
//        else if((piece_surround[i] ^ p_type) == 1) this->update_opponent(iter->first, pos_x+x_srd[i],pos_y+y_srd[i]);
//    }

//    this->ps_map[ps.get_pieceString_label()] = ps;
//    this->ps_vec.push_back(ps);

//    this->mboard->set_piecetype(pos_x,pos_y,p_type);
//    this->set_piecePool(pos_x,pos_y,this->count);
//    return true;
}


void board::update(const int _label, pieceString& ps, const int pos_x, const int pos_y)
{
    ps.combine_string(this->ps_map[_label]);
    this->ps_map.erase(_label);

    for(auto i = ps_vec.begin(); i != ps_vec.end(); i ++) {
        if(i->get_label() == _label) {
            ps_vec.erase(i);
            break;
        }
    }
    return;
}

int board::update_opponent(int _label, const int pos_x, const int pos_y)
{
    this->ps_map[_label].updateQi(-1);
    if(this->ps_map[_label].getQi() == 0)
    {
        for(int i = 0; i < ps_map[_label].getSize(); i ++) {
            piece_info pi = ps_map[_label].get_piece(i);
            auto li = std::make_pair(pi.first/1000, pi.second%1000);
            this->set_piecetype(li.first,li.second,emptypiece);
        }
        this->ps_map.erase(_label);

        for(auto i = ps_vec.begin(); i != ps_vec.end(); i ++) {
            if(i->get_label() == _label) {
                ps_vec.erase(i);
                break;
            }
        }
    }
    return 0;
}
