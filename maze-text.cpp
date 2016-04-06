/*
Maze Game -

Jamie Johnson
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "ConsoleColor.h"
#include "Player.h"

void loadMenu();
void loadMap(char choice, Player &player, int &game);
void playGame(std::vector<std::vector<std::string> > &maze, Player &player, int &game);
void printMaze(std::vector<std::vector<std::string> > maze, std::string message = " ");
bool checkWin(std::vector<std::vector<std::string> > maze, Player &player, int &game);
char winScreen(std::vector<std::vector<std::string> > maze);
void farewell();

int main(){

	loadMenu();

	return 0;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
//
//  Loads the Game Menu.
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
void loadMenu(){

	char choice = ' ';
	char symbol = 'X';
	Player player;
	int game = 0;

	do{
		system("cls");
		std::cout << blue;
		std::cout << " __  __                 __  __                    " << std::endl;
		std::cout << "|  \\/  |               |  \\/  |                   " << std::endl;
		std::cout << "| \\  / | __ _ _______  | \\  / | ___ _ __  _   _   " << std::endl;
		std::cout << "| |\\/| || _` |_  / _ | | |\\/| || _ | '_ \\| | | |  " << std::endl;
		std::cout << "| |  | | (_| |/ |  __| | |  | || __| | | | |_| |  " << std::endl;
		std::cout << "|_|  |_||__,_/___\\___| |_|  |_||___|_| |_|\\__,_|  " << std::endl;
		std::cout << yellow;
		std::cout << " ______ ______ ______ ______ ______ ______ ______ " << std::endl;
		std::cout << "|______|______|______|______|______|______|______|\n\n" << std::endl;
		std::cout << green;

		std::cout << "Please choose one:\n\n";

		std::cout << "<A> for Map 1.\t";
		player.is1Win() ? std::cout << red << "<COMPLETED>\n" << green : std::cout << std::endl;
		std::cout << "<B> for Map 2.\t";
		player.is2Win() ? std::cout << red << "<COMPLETED>\n" << green : std::cout << std::endl;
		std::cout << "<C> for Map 3.\t";
		player.is3Win() ? std::cout << red << "<COMPLETED>\n" << green : std::cout << std::endl;

		std::cout << "\nPress <S> to change the symbol that represents you.\n\n"
			<< "Press <X> to quit at any time\n";
		std::cin >> choice;
		if (toupper(choice) == 'A' || toupper(choice) == 'B' || toupper(choice) == 'C'){
			loadMap(choice, player, game);
		}
		else if (toupper(choice) == 'S'){
			std::cout << "\nWhat character would you like?\n";
			std::cin >> symbol;
			player.setS(symbol);
		}
	} while (toupper(choice) != 'X');
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
//
//  Loads the easy Maze into memory
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
void loadMap(char choice, Player &player, int &game){

	std::ifstream inputFile;

	if (toupper(choice) == 'A'){
		inputFile.open("maze1.txt");
		game = 1;
	}
	else if (toupper(choice) == 'B'){
		inputFile.open("maze2.txt");
		game = 2;
	}
	else{
		inputFile.open("maze3.txt");
		game = 3;
	}
	if (!inputFile){
		std::cout << "Error opening maze file.  Terminating Program.\n";
		exit(EXIT_FAILURE);
	}
	std::string buffer;
	int row = 0;
	int column = 0;
	player.setX(1);
	player.setY(1);

	std::vector<std::vector <std::string> > maze(21, std::vector<std::string>(21, " "));

	while (std::getline(inputFile, buffer)){

		for (unsigned i = 0; i < buffer.size();)
			if (buffer[i] == '+'){
				maze[column][row] = '+';
				buffer.erase(0, 1);
				row++;
			}
			else if (buffer[i] == '|'){
				maze[column][row] = '|';
				buffer.erase(0, 1);
				row++;
			}
			else if (buffer[i] == '-'){
				maze[column][row] = "---";
				row++;
				buffer.erase(0, 3);
			}
			else{
				if (row % 2 == 1){
					maze[column][row] = "   ";
					row++;
					buffer.erase(0, 3);
				}
				else{
					maze[column][row] = " ";
					row++;
					buffer.erase(0, 1);
				}
			}
			column++;
			row = 0;
			std::cout << std::endl;
	}
	maze[19][19] = " $ ";
	inputFile.close();
	playGame(maze, player, game);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
//
//  The Maze Game Mechanics
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
void playGame(std::vector<std::vector<std::string> > &maze, Player &player, int &game){

	char choice = ' ';
	int moveChoice = 0;
	std::string pipe = "|", dashes = "---", message = " ";

	enum direction { UP = 56, DOWN = 50, LEFT = 52, RIGHT = 54 };

	maze[player.getX()][player.getY()] = player.getS();

	printMaze(maze);

	do{
		message = " ";
		std::cin >> choice;
		moveChoice = static_cast<int>(choice);
		switch (moveChoice){
		case UP:
			message = "Trying to go up...";
			if (maze[(player.getX() - 1)][player.getY()] != dashes){
				maze[player.getX()][player.getY()] = "   ";
				player.changeX(-2);
				maze[player.getX()][player.getY()] = player.getS();
				message.append("and is successful!\n");
			}
			else
				message.append("NOPE!\n");
			break;
		case DOWN:
			message = "Trying to go down...";
			if (maze[(player.getX()) + 1][player.getY()] != dashes){
				maze[player.getX()][player.getY()] = "   ";
				player.changeX(2);
				maze[player.getX()][player.getY()] = player.getS();
				message.append("and is successful!\n");
			}
			else
				message.append("NOPE!\n");
			break;
		case RIGHT:
			message = "Trying to go right...";
			if (maze[(player.getX())][player.getY() + 1] != pipe){
				maze[player.getX()][player.getY()] = "   ";
				player.changeY(2);
				maze[player.getX()][player.getY()] = player.getS();
				message.append("and is successful!\n");
			}
			else
				message.append("NOPE!\n");
			break;
		case LEFT:
			message = "Trying to go left...";
			if (maze[(player.getX())][player.getY() - 1] != pipe){
				maze[player.getX()][player.getY()] = "   ";
				player.changeY(-2);
				maze[player.getX()][player.getY()] = player.getS();
				message.append("and is successful!\n");
			}
			else
				message.append("NOPE!\n");
			break;
		default:
			break;
		}
		checkWin(maze, player, game) ? choice = winScreen(maze) : printMaze(maze, message);

	} while (toupper(choice) != 'X');
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
//
//  Prints the Maze and the player
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
void printMaze(std::vector<std::vector<std::string> > maze, std::string message){

	system("cls");

	std::cout << "Use NumKeyPad to Move.\n\n"
		<< "Up = 8, Left = 4, Right = 6, Down = 2\n"
		<< "Press <X> to quit at any time.\n\n";

	for (unsigned i = 0; i < maze.size(); i++){
		for (unsigned j = 0; j < maze[i].size(); j++)
			std::cout << maze[i][j];
		std::cout << std::endl;
	}
	std::cout << std::endl << message << std::endl;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
//
//  Checks to see if the player is in the final position.
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
bool checkWin(std::vector<std::vector<std::string> > maze, Player &player, int &game){
	if (player.getX() == maze.size() - 2 && player.getY() == maze.size() - 2){
		if (game == 1)
			player.g1Win();
		else if (game == 2)
			player.g2Win();
		else if (game == 3)
			player.g3Win();
		return true;
	}
	else
		return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
//
//  Win Screen
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
char winScreen(std::vector<std::vector<std::string> > maze){

	char choice = ' ';

	system("cls");
	std::cout << "Use NumKeyPad to Move.\n\n"
		<< "Up = 8, Left = 4, Right = 6, Down = 2\n"
		<< "Press <X> to quit at any time.\n\n";

	for (unsigned i = 0; i < maze.size(); i++){
		for (unsigned j = 0; j < maze[i].size(); j++)
			std::cout << maze[i][j];
		std::cout << std::endl;
	}
	std::cout << red;
	std::cout << " __ __  ___  __ __      __    __ ____ ____  __ __ __" << std::endl;
	std::cout << "|  |  |/   \\|  |  |    |  |__|  |    |    \\|  |  |  |" << std::endl;
	std::cout << "|  |  |     |  |  |    |  |  |  ||  ||  _  |  |  |  |" << std::endl;
	std::cout << "|  ~  |  O  |  |  |    |  |  |  ||  ||  |  |__|__|__|" << std::endl;
	std::cout << "|___, |     |  :  |    |  `  '  ||  ||  |  |__ __ __ " << std::endl;
	std::cout << "|     |     |     |     \\      / |  ||  |  |  |  |  |" << std::endl;
	std::cout << "|____/ \\___/ \\__,_|      \\_/\\_/ |____|__|__|__|__|__|" << std::endl;
	std::cout << green;	
	std::cout << "\tPress any key to return to main menu..." << std::endl;
	std::cin >> choice;
	choice = 'X';
	return choice;
}

