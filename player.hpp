#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <vector>
#include <tuple>

using namespace std;

class Player {

private: 
	
	bool testingMinimax;
	Board * board;
	Side myside;
	Side other;


public:
    Player(Side side);
    ~Player();
    //int Heuristic(Side side, int x, int y);
    vector<Move*> getPossibleMoves(Side side, Board * board);
    int calcScore(Move * possibleMove, Side side, Board * board_);

    Move *doMove(Move *opponentsMove, int msLeft);
    Move *GetBestMove(vector<Move*> listMoves, Side side, Board * board_);
    Move *Minimax(vector<Move*> listMoves, Side side, Board * board);
    Move *MiniMinimax(vector<Move*> listMoves);

   
};

#endif
