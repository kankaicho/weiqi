#include "chess_piece.h"
#include <algorithm>

//bool pieceString::operator==(const pieceString& ps)
//{
//    return this->pieceString_label == ps.pieceString_label;
//}

//void pieceString::add_piece(const int _mesh)
//{
//    this->piece_string.push_back(_mesh);
//    this->set_pieceString_label(_mesh);
//}

void pieceString::init_piece(chess& c) {
    int _mesh = c.get_mesh();
    int _loc_code = pieceString::encryption(c.get_x(), c.get_y());
    this->piece_string.push_back(std::make_pair(_mesh, _loc_code));
    this->set_label(_mesh);
    this->freeloc.insert(_loc_code);
}

void pieceString::setQi(int _qi)
{
    this->qi = _qi;
}

int pieceString::getQi()
{
    return this->freeloc.size()-this->piece_string.size();
}

void pieceString::updateQi(int _diff)
{
    this->qi += _diff;
}

void pieceString::updateQi()
{

}

void pieceString::set_label(int _label)
{
    this->label = _label;
}

int pieceString::get_label()
{
    return this->label;
}

std::vector<piece_info>& pieceString::get_string()
{
    return this->piece_string;
}

int pieceString::find_piece(const int _mesh)
{
    for(auto i : this->piece_string) {
        if(_mesh == i.first) return this->get_label();
    }
    return -1;
}

void pieceString::combine_string(pieceString& s)
{
    std::vector<piece_info> ps = s.get_string();
    for(auto i = ps.begin(); i != ps.end(); i ++) {
        this->piece_string.push_back(*i);
    }
    for(auto iter = s.freeloc.begin(); iter != s.freeloc.end(); iter ++) {
        this->freeloc.insert(*iter);
    }
}
