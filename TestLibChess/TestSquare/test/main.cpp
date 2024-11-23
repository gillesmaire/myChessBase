    #include <iostream>
    #include <chess.hpp>
    
    using namespace std;
    using namespace chess;
    void Debug( Board B )
{       
        std::cout<<"********"<<std::endl;
        for ( int f=7; f>=0; f--) 
         for ( int r=0;r<=7;r++){
           Piece p = B.at(Square(File(r),Rank(f)));
           std::cout << std::string(p)   ;
           if ( r==7 ) std::cout << std::endl;
        }
        std::cout<<"********"<<std::endl;
}
    int main()
    {
      	Board b(constants::STARTPOS);
      	Debug(b);
        chess::Move move=chess::uci::parseSan(b,std::string_view("d4"));
        b.makeMove(move);
	move=chess::uci::parseSan(b,std::string_view("Nf6"));
        b.makeMove(move);
        move=chess::uci::parseSan(b,std::string_view("e4"));
        b.makeMove(move);
        Debug(b);
    }
