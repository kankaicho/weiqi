#ifndef CHESS_PIECE
#define CHESS_PIECE

#include <utility>
#include <vector>
#include <map>
#include <set>
#include <memory>

/* <mesh, loc_code> pice_info */
typedef std::pair<int,int> piece_info;


class chess {
public:
    chess(int _mesh, int _pos_x, int _pos_y) {
        this->mesh = _mesh;
        this->pos_x = _pos_x;
        this->pos_y = _pos_y;
    }

    int get_x() const {return this->pos_x;}
    int get_y() const {return this->pos_y;}
    int get_mesh() const {return this->mesh;}

private:
    int mesh;
    int pos_x;
    int pos_y;
};

class pieceString {
public:
    void init_piece(chess& c);
    void combine_string(pieceString& s);
    std::vector<piece_info>& get_string();
    void set_label(int _label);
    int get_label();
    int getQi();
    void updateQi(int _diff);
    void updateQi();
    void setQi(int _qi);
    int find_piece(const int _mesh);
    int getSize() const {return this->piece_string.size();}
//    int getPiece(const int i) {return this->piece_string[i].first;}
    piece_info get_piece(const int i) { return this->piece_string[i]; }
    static int encryption(const int pos_x, const int pos_y) { return pos_x*1000+pos_y; }
    static std::pair<int,int> decryption(const int code) {return {code/1000, code%1000};}
    std::set<int> freeloc;
    private:
        int qi = 0;
        int label;
//        std::vector<int> piece_string;
        std::vector<piece_info> piece_string;
//        std::set<int> freeloc;
};

#endif
