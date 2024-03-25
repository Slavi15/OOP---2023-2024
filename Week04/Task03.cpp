#include <iostream>
#include <fstream>

#define MAX_TITLE_LENGTH 64
#define MAX_GAMES_COUNT 100
#define MAX_TEXT_LENGTH 1024

class Game
{
private:
	char title[MAX_TITLE_LENGTH + 1];
	double price = 0.0;
	bool isAvailable = false;

public:
	Game();
	Game(const char* title, double price, bool isAvailable);

	void setTitle(const char* title);
	void setPrice(double price);
	void setAvailability(bool isAvailable);

	const char* getTitle() const;
	const double getPrice() const;
	const bool getAvailabilty() const;

	const bool isFree() const;
	void print() const;
};

class GamePlatform
{
private:
	Game games[MAX_GAMES_COUNT];
	size_t currentGames = 0;

	void insertionSort(bool(*isLower)(const Game& game1, const Game& game2));

public:
	void addGame(const char* title, double price);
	void removeGame(const char* title);

	const Game& getGameByIndex(size_t index) const;
	const Game& getMostExpensiveGame();
	const Game& getCheapestGame();

	void readGame(std::ifstream& ifs, Game& game);
	void readFromFile(std::ifstream& ifs);
	void readFromFile(const char* fileName);

	void writeGame(std::ofstream& ofs, const Game& game);
	void writeToFile(std::ofstream& ofs);
	void writeToFile(const char* fileName);

	void printFreeGames() const;
	void printGames() const;
};

// Game Class
Game::Game() = default;

Game::Game(const char* title, double price, bool isAvailable)
{
	setTitle(title);
	setPrice(price);
	setAvailability(isAvailable);
}

void Game::setTitle(const char* title)
{
	if (!title) return;

	if (strlen(title) < MAX_TITLE_LENGTH)
		strcpy(this->title, title);
}

void Game::setPrice(double price)
{
	if (price >= 0)
		this->price = price;
}

void Game::setAvailability(bool isAvailable)
{
	this->isAvailable = isAvailable;
}

const char* Game::getTitle() const
{
	return title;
}

const double Game::getPrice() const
{
	return price;
}

const bool Game::getAvailabilty() const
{
	return isAvailable;
}

const bool Game::isFree() const
{
	return price <= 0.0;
}

void Game::print() const
{
	std::cout << "Title: " << title << " - " << "Price: " << price << " - " << "Availability: " << isAvailable << std::endl;
}
// Game Class

// GamePlatform Class
void GamePlatform::insertionSort(bool(*isLower)(const Game& game1, const Game& game2))
{
	for (size_t i = 0; i < currentGames - 1; i++)
	{
		size_t minIndex = i;

		for (size_t j = i + 1; j < currentGames; j++)
			if (isLower(games[j], games[minIndex]))
				minIndex = j;

		if (minIndex != i)
			std::swap(games[i], games[minIndex]);
	}
}

void GamePlatform::addGame(const char* title, double price)
{
	if (!title) return;

	if (currentGames < MAX_GAMES_COUNT)
	{
		games[currentGames].setTitle(title);
		games[currentGames].setPrice(price);
		games[currentGames].setAvailability(true);
	}

	currentGames++;
}

void GamePlatform::removeGame(const char* title)
{
	if (!title) return;

	for (size_t i = 0; i < currentGames; i++)
		if (strcmp(games[i].getTitle(), title) == 0)
		{
			std::swap(games[i], games[MAX_GAMES_COUNT - 1]);
			currentGames--;
			return;
		}
}

const Game& GamePlatform::getGameByIndex(size_t index) const
{
	return games[index];
}

const Game& GamePlatform::getMostExpensiveGame()
{
	insertionSort([](const Game& game1, const Game& game2) -> bool { return game1.getPrice() < game2.getPrice(); });
	return games[MAX_GAMES_COUNT - 1];
}

const Game& GamePlatform::getCheapestGame()
{
	insertionSort([](const Game& game1, const Game& game2) -> bool { return game1.getPrice() < game2.getPrice(); });
	return games[0];
}

void GamePlatform::readGame(std::ifstream& ifs, Game& game)
{
	char buff[MAX_TEXT_LENGTH + 1];

	ifs.getline(buff, MAX_TEXT_LENGTH + 1, ':');
	game.setTitle(buff);

	ifs.getline(buff, MAX_TEXT_LENGTH + 1, ':');
	game.setPrice(std::atof(buff));

	game.setAvailability(true);
}

void GamePlatform::readFromFile(std::ifstream& ifs)
{
	while (!ifs.eof())
		readGame(ifs, games[currentGames++]);
}

void GamePlatform::readFromFile(const char* fileName)
{
	if (!fileName) return;

	std::ifstream ifs(fileName, std::ios::in);
	if (!ifs.is_open()) return;

	return readFromFile(ifs);
}

void GamePlatform::writeGame(std::ofstream& ofs, const Game& game)
{
	ofs << game.getTitle() << ":" << game.getPrice() << " " << std::endl;
}

void GamePlatform::writeToFile(std::ofstream& ofs)
{
	for (size_t i = 0; i < currentGames; i++)
		writeGame(ofs, games[i]);
}

void GamePlatform::writeToFile(const char* fileName)
{
	if (!fileName) return;

	std::ofstream ofs(fileName, std::ios::out);
	if (!ofs.is_open()) return;

	return writeToFile(ofs);
}

void GamePlatform::printFreeGames() const
{
	for (size_t i = 0; i < currentGames; i++)
		if (games[i].isFree()) games[i].print();
}

void GamePlatform::printGames() const
{
	for (size_t i = 0; i < currentGames; i++)
		games[i].print();
}
// GamePlatform Class

int main()
{
	return 0;
}