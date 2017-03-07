#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

private: 
	
	bool testingMinimax;
	Board board;
	Side myside;
	Side other;




public:
    Player(Side side);
    ~Player();
    int Heuristic(Side side, int x, int y);

    Move *doMove(Move *opponentsMove, int msLeft);

   
};

#endif
