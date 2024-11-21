#include "chess.hpp"

using namespace::std;
using namespace::chess;
int main()
{
   chess::Board b(chess::constants::STARTPOS);
   cout<<b.them(Color::BLACK)<<endl;
   
    
}

