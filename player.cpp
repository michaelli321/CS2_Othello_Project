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

/* Should this check moves, or possible moves? Checking moves would have to allocate memory for the move first. */



// int Player::Heuristic(Side side, int x, int y)
// {
//     Board copy = board.copy();
//     Move * Move2 = new Move(x, y);
//     copy.doMove(Move2, side);

// /* Simple board position score. */

//     int score = (copy.countBlack() - copy.countWhite()) - (board.countBlack() - board.countWhite())

// // Big upgrade if you get a corner spot.

//     if ((x == 0 || x == 7) && (y == 0 || y == 7))
//     {
//         score *= 3;
//     }

// // Downgrade for setting opponent up for 

//     else if ((x == 1) && (y != 0 && y != 7))
//     {
//         for (int i = -1; i <= 1; i++)
//         {
//             Move * TheirMove = new Move(0, y + i);
//             if (copy.checkMove(TheirMove, other))
//             {
//                 score *= -3;
//                 delete TheirMove;
//                 break;
//             }

//             delete TheirMove;
//         }
//     }

//     else if ((x == 6) && (y != 0 && y != 7))
//     {
//         for (int i = -1; i <= 1; i++)
//         {
//             Move * TheirMove = new Move(7, y + i);
//             if (copy.checkMove(TheirMove, other))
//             {
//                 score *= -3;
//                 delete TheirMove;
//                 break;
//             }

//             delete TheirMove;
//         }
//     }

//     if ((y == 1) && (x != 0 && x != 7))
//     {
//         for (int i = -1; i <= 1; i++)
//         {
//             Move * TheirMove = new Move(x + 1, 0);
//             if (copy.checkMove(TheirMove, other))
//             {
//                 score *= -3;
//                 delete TheirMove;
//                 break;
//             }

//             delete TheirMove;
//         }
//     }

//     if ((y == 6) && (x != 0 && x != 7))
//     {
//         for (int i = -1; i <= 1; i++)
//         {
//             Move * TheirMove = new Move(x + 1, 0);
//             if (copy.checkMove(TheirMove, other))
//             {
//                 score *= -3;
//                 delete TheirMove;
//                 break;
//             }

//             delete TheirMove;
//         }
//     }

//     delete Move2;
//     return score;


// }




vector<Move*> Player::getPossibleMoves(Side side){
    vector<Move*> listMoves;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            Move *newMove = new Move(i, j);
            if (board -> checkMove(newMove, side)){
                listMoves.push_back(newMove);
            }
        }
    }

    return listMoves;
}

int Player::calcScore(Move * possibleMove){

	Board * copyBoard = board -> copy();

	int score;

	copyBoard -> doMove(possibleMove, myside);
	if (myside == BLACK){
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

	return score;
	
}

Move *Player::doMove(Move *opponentsMove, int msLeft) {
    

    board -> doMove(opponentsMove, other);

    vector<Move*> listMoves = this -> getPossibleMoves(this->myside);

    if ((listMoves.size() == 0) || (msLeft == 0)){
        return nullptr;
    }

    Move *highmove = listMoves[0];
    int highScore = this -> calcScore(highmove);

    for (unsigned int i = 1; i < listMoves.size(); i++){
    	int tempScore = this -> calcScore(listMoves[i]);
    	if (tempScore > highScore){
    		highScore = tempScore;
    		highmove = listMoves[i];
    	}
    }

    board -> doMove(highmove, myside);

    return highmove;

}

    
    /*
    board.doMove(*opponentsMove, other);
    Move * Move1 = nullptr;
    Board copy = board.copy();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (copy.get(other, i, j))
            {
                for (int dx = -1; dx <= 1; dx++)
                {
                    for (int dy = -1; dy <= 1; dy++)
                    {
                        if (dy == 0 && dx == 0) continue;
                        if (copy.checkMove(mySide, i + dx, j + dy))
                        {
                            Move1 = new Move(i + dx, j + dy);
                            board.doMove(Move1, mySide);
                            return Move1;
                        }
                    }
                }
            }
        }
            
    }
    return nullptr;
    */