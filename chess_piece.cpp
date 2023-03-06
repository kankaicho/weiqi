#include "chess_piece.h"
#include <algorithm>

bool pieceString::operator==(const pieceString& ps)
{
    return this->pieceString_label == ps.pieceString_label;
}

void pieceString::add_piece(const int _mesh)
{
    this->piece_string.push_back(_mesh);
    this->set_pieceString_label(_mesh);
}

void pieceString::setQi(int _qi)
{
    this->qi = _qi;
}

int pieceString::getQi()
{
    return this->qi;
}

void pieceString::updateQi(int _diff)
{
    this->qi += _diff;
}

void pieceString::updateQi()
{

}

void pieceString::set_pieceString_label(int _label)
{
    this->pieceString_label = _label;
}

int pieceString::get_pieceString_label()
{
    return this->pieceString_label;
}

std::vector<int>& pieceString::get_pieceString()
{
    return this->piece_string;
}

int pieceString::find_piece(const int _mesh)
{
    auto res = std::find(this->piece_string.begin(),this->piece_string.end(),_mesh);
    if(res == this->piece_string.end()) {
        return -1;
    }
    return this->get_pieceString_label();
}

void pieceString::combine_pieceString(pieceString& s)
{
    std::vector<int> ps = s.get_pieceString();
    for(auto i = ps.begin(); i != ps.end(); i ++) {
        this->piece_string.push_back(*i);
    }

    int diff_qi = s.getQi()-1;
    this->updateQi(diff_qi);
}
