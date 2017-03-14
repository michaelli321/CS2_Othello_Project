#include "player.hpp"



/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    board = new Board();
    myside = side;
    if (myside == BLACK)
    {
        other = WHITE;
    } else if (myside == WHITE){
    	other = BLACK;
    }


}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */

vector<Move*> Player::getPossibleMoves(Side side, Board * board){
    vector<Move*> listMoves;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            Move *newMove = new Move(i, j);
            if (board -> checkMove(newMove, side)){
                listMoves.push_back(newMove);
            }
            else {
            	delete newMove;
            }
        }
    }

    return listMoves;
}

int Player::calcScore(Move * possibleMove, Side side, Board * board_){

	Board * copyBoard = board_ -> copy();

	int score;

	copyBoard -> doMove(possibleMove, side);
	if (side == BLACK){
		score = (copyBoard -> countBlack()) - (copyBoard -> countWhite());
	} else {
		score = (copyBoard -> countWhite()) - (copyBoard -> countBlack());
	}

	if ((possibleMove -> getX() == 0) && (possibleMove -> getY() == 0)){
		score *= 3;
	} else if ((possibleMove-> getX() == 7) && (possibleMove -> getY() == 0)){
		score *= 3;
	} else if ((possibleMove -> getX() == 0) && (possibleMove -> getY() == 7)){
		score *= 3;
	} else if ((possibleMove -> getX() == 7) && (possibleMove -> getY() == 0)){
		score *= 3;
	} else if ((possibleMove -> getX() == 1) && (possibleMove-> getY() == 0)){
		score *= -1;
	} else if ((possibleMove -> getX() == 6) && (possibleMove -> getY() == 0)){
		score *= -1;
	} else if ((possibleMove -> getX() == 0) && (possibleMove -> getY() == 1)){
		score *= -1;
	} else if ((possibleMove -> getX() == 7) && (possibleMove -> getY() == 1)){
		score *= -1;
	} else if ((possibleMove -> getX() == 0) && (possibleMove -> getY() == 6)){
		score *= -1;
	} else if ((possibleMove -> getX() == 7) && (possibleMove -> getY() == 6)){
		score *= -1;
	} else if ((possibleMove -> getX() == 1) && (possibleMove -> getY() == 7)){
		score *= -1;
	} else if ((possibleMove -> getX() == 6) && (possibleMove -> getY () == 7)){
		score *= -1;
	} else if ((possibleMove -> getX() == 1) && (possibleMove -> getY() == 1)){
		score *= -3;
	} else if ((possibleMove -> getX() == 6) && (possibleMove -> getY() == 1)){
		score *= -3;
	} else if ((possibleMove -> getX() == 1) && (possibleMove -> getY() == 6)){
		score *= -3;
	} else if ((possibleMove -> getX() == 6) && (possibleMove -> getY() == 6)){
		score *= -3;
	} else if ((possibleMove -> getX() == 0) && (possibleMove -> getY() == 2)){
		score *= 1.25;
	} else if ((possibleMove -> getX() == 0) && (possibleMove -> getY() == 3)){
		score *= 1.25;
	} else if ((possibleMove -> getX() == 0) && (possibleMove -> getY() == 4)){
		score *= 1.25;
	} else if ((possibleMove -> getX() == 0) && (possibleMove -> getY() == 5)){
		score *= 1.25;
	} else if ((possibleMove -> getX() == 2) && (possibleMove -> getY() == 0)){
		score *= 1.25;
	} else if ((possibleMove -> getX() == 3) && (possibleMove -> getY() == 0)){
		score *= 1.25;
	} else if ((possibleMove -> getX() == 4) && (possibleMove -> getY() == 0)){
		score *= 1.25;
	} else if ((possibleMove -> getX() == 5) && (possibleMove -> getY() == 0)){
		score *= 1.25;
	} else if ((possibleMove -> getX() == 7) && (possibleMove -> getY() == 2)){
		score *= 1.25;
	} else if ((possibleMove -> getX() == 7) && (possibleMove -> getY() == 3)){
		score *= 1.25;
	} else if ((possibleMove -> getX() == 7) && (possibleMove -> getY() == 4)){
		score *= 1.25;
	} else if ((possibleMove -> getX() == 7) && (possibleMove -> getY() == 5)){
		score *= 1.25;
	} else if ((possibleMove -> getX() == 7) && (possibleMove -> getY() == 2)){
		score *= 1.25;
	} else if ((possibleMove -> getX() == 2) && (possibleMove -> getY() == 7)){
		score *= 1.25;
	} else if ((possibleMove -> getX() == 3) && (possibleMove -> getY() == 7)){
		score *= 1.25;
	} else if ((possibleMove -> getX() == 4) && (possibleMove -> getY() == 7)){
		score *= 1.25;
	} else if ((possibleMove -> getX() == 5) && (possibleMove -> getY() == 7)){
		score *= 1.25;
	}
	delete copyBoard;
	return score;
	
}

Move *Player::doMove(Move *opponentsMove, int msLeft) {
    

    board -> doMove(opponentsMove, other);

    vector<Move*> listMoves = this -> getPossibleMoves(this->myside, this->board);

    if ((listMoves.size() == 0) || (msLeft == 0)){
        return nullptr;
    }

    Move *finalmove = Minimax(listMoves, myside, board);

    board -> doMove(finalmove, myside);

    return finalmove;

}

Move *Player::GetBestMove(vector<Move*> listMoves, Side side, Board * board_)
{
	Move *highmove = listMoves[0];
	int highScore = calcScore(highmove, side, board_);

	for (unsigned int i = 1; i < listMoves.size(); i++)
	{
		int tempScore = calcScore(listMoves[i], side, board_);
    	if (tempScore > highScore){
    		highScore = tempScore;
    		highmove = listMoves[i];
    	}
	}

	return highmove;

}

Move *Player::Minimax(vector<Move*> listMoves, Side side, Board * board_)
{
	Side other_side;
	int tempScore = 10000;
	if (side == myside)
	{
		other_side = other;
	}
	else
	{
		other_side = myside;
	}
	Move * bestMove;
	for (unsigned int i = 0; i < listMoves.size(); i++)
	{

		Board * copyBoard = board_ -> copy();
		copyBoard -> doMove(listMoves[i], side);
		vector<Move*> theirMoves = this -> getPossibleMoves(this->other, copyBoard);
		if (theirMoves.size() == 0)
		{
			return listMoves[i];
		}
		if (calcScore(GetBestMove(theirMoves, other_side, copyBoard), other_side, copyBoard) < tempScore)
		{
			tempScore = calcScore(GetBestMove(theirMoves, other_side, copyBoard), other_side, copyBoard);
			bestMove = listMoves[i];
		}
		delete copyBoard;
	}
	return bestMove;
}

Move *Player::MiniMinimax(vector<Move*> listMoves)
{
	int tempScore = 10000;
	Move * bestMove;
	for (unsigned int i = 0; i < listMoves.size(); i++)
	{

		Board * copyBoard = board -> copy();
		copyBoard -> doMove(listMoves[i], myside);
		vector<Move*> theirMoves = getPossibleMoves(this->other, copyBoard);
		if (theirMoves.size() == 0)
		{
			return listMoves[i];
		}
		if (calcScore(Minimax(theirMoves, other, copyBoard), other, copyBoard) < tempScore)
		{
			tempScore = calcScore(Minimax(theirMoves, other, copyBoard), other, copyBoard);
			bestMove = listMoves[i];
		}
		delete copyBoard;
	}
	return bestMove;
}