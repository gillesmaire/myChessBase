#include <fstream>
#include <memory>
#include <string>
#include <iostream>

#include "../../src/chess.hpp"

using namespace chess;

class MyVisitor : public pgn::Visitor {
   public:
    int i=0;	   
    void header(std::string_view key, std::string_view value) {}

    void move(std::string_view move, std::string_view comment) {}

    void startPgn() {
	    std::cout<<"png no : "<<i++<<std::endl;
    }
    void startMoves() {}
    void endPgn() {}
};

int main(int argc, char const *argv[]) {
    const auto file  = "./caissa.pgn";
    auto file_stream = std::ifstream(file);

    auto vis = std::make_unique<MyVisitor>();

    pgn::StreamParser parser(file_stream);
    parser.readGames(*vis);

    return 0;
}
