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


typedef std::pair<int,int> piece_loc;
typedef std::pair<piece_loc, int> piece;

class pieceString {
public:
    bool operator==(const pieceString& ps);
    void add_piece(const int _count);
    void combine_pieceString(pieceString& s);
    std::vector<int>& get_pieceString();
    void set_pieceString_label(int _label);
    int get_pieceString_label();
    int getQi();
    void updateQi(int _diff);
    void updateQi();
    void setQi(int _qi);
    int find_piece(const int _count);
    int getSize() const {return this->piece_string.size();}
    int getPiece(const int i) {return this->piece_string[i];}
    private:
        int qi = 0;
        int pieceString_label;
        std::vector<int> piece_string;
};

#endif
