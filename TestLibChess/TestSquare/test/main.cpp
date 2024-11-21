    #include <iostream>
    #include <chess.hpp>
    
    using namespace std;
    using namespace chess;
    
    int main()
    {
      	Board b(constants::STARTPOS);
	Move m=uci::uciToMove(b,"e2e4");   
        b.makeMove(m);
        //print all square values 
        //cout <<b.occ()<<endl;
        for ( int i=0; i<64; i++) { 
           cout << std::string(b.at(Square(i)))   ;
           if ( (i+1)%8 == 0 ) cout << endl;
        }
    }
