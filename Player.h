#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player{
private:
	int xPos;
	int yPos;
	std::string symbol;
	bool game1;
	bool game2;
	bool game3;

public:
	Player(int tempX = 1, int tempY = 1){
		xPos = tempX;
		yPos = tempY;
		symbol = " X ";
		game1 = false;
		game2 = false;
		game3 = false;
	}
	int getX() const {	return xPos; 	}
	int getY() const {	return yPos; 	}
	std::string getS() const	{ return symbol; }
	void changeX(int tempX) { xPos += tempX; }
	void changeY(int tempY) { yPos += tempY; }
	void setX(char tempX) { xPos = tempX; }
	void setY(char tempY) { yPos = tempY; }
	void g1Win() { game1 = true; }
	void g2Win() { game2 = true; }
	void g3Win() { game3 = true; }
	bool is1Win() const { return game1; }
	bool is2Win() const { return game2; }
	bool is3Win() const { return game3; }	
	void setS(char tempS){
		symbol = tempS;
		symbol.insert(0, " ");
		symbol.append(" ");
	}
};
#endif // PLAYER_H