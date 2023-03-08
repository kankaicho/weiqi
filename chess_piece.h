#ifndef CHESS_PIECE
#define CHESS_PIECE

#include <utility>
#include <vector>
#include <map>
#include <memory>

#define OFF_BUG
#ifndef OFF_BUG
typedef std::pair<int,int> piece_loc;
typedef std::vector<piece_loc> string_piece;
typedef std::shared_ptr<string_piece> string_piece_ptr;

class piece {
    public:
        piece(int _piecetype):piecetype(_piecetype){}
        ~piece() = default;
        int count_Qi();
        void add_stringPiece(int posx, int posy);
        bool exist_stringPiece(int posx, int posy);
        void combine_stringPiece(string_piece_ptr&& p1, string_piece_ptr&& p2);
    private:
        int piecetype;
        int string_count = 0;
        std::map<string_piece_ptr, int> string_piece_pool;
        std::vector<string_piece_ptr> string_piece_ptr;

        void add_stringCount();
};
#endif


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
//    bool operator==(const pieceString& ps);
//    void add_piece(const int _count);
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
    int encryption(const int pos_x, const int pos_y) { return pos_x*1000+pos_y; }
    std::pair<int,int> decryption(const int code) {return {code/1000, code%1000};}

    private:
        int qi = 0;
        int pieceString_label;
//        std::vector<int> piece_string;
        std::vector<piece_info> piece_string;
};

#endif
