    #include <iostream>
    #include <chess.hpp>
    
    using namespace std;
    using namespace chess;
    
    int main()
    {
        // initialize the board to START POS
        Board b(constants::STARTPOS);

        // make a move in UCI notation
        Move m=uci::uciToMove(b,"e2e4");
    
        // generate a FEN from position
        // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
        cout<<b.getFen()<<endl;
    
        // make te move 
        b.makeMove(m);
    
        // qkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 
        cout<<b.getFen()<<endl;
        
       // Move number => 1 
        cout<<b.fullMoveNumber()<<endl;
       //  print the chess board with 1 on occupated square  
       // and 0 on free square
       // 11111111
       // 11111111
       // 00000000
       // 00000000
       // 00001000
       // 00000000
       // 11110111
       // 11111111
       
       // same result
       cout<<b.all()<<endl;
        
        //print all square values 
        //cout <<b.occ()<<endl;
        for ( int i=0; i<64; i++) {
           cout << std::string(b.at(Square(i)))   ;
           if ( (i+1)%8 == 0 ) cout << endl;
        }
            
        for ( int i=0; i<64; i++) {
           cout << std::string(b.at(Square(i)))   ;
           if ( (i+1)%8 == 0 ) cout << endl;
        }
        auto c=b.us(Color::WHITE); 
        auto d=b.them(Color::WHITE); 
        cout <<"US"<<endl;
        cout <<c<<endl;
        cout <<"THEM"<<endl;
        cout <<d<<endl;
        
    }
