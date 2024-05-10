#pragma once
#pragma warning (disable: 4996)

#include <iostream>
#include <cstring>
#include <fstream>

#define CHAR_BITS_LENGTH 4
#define MAX_SONG_NAME_LENGTH 64
#define MAX_BYTES_LENGTH 256
#define getMin(a, b) a < b ? a : b

inline size_t getFileSize(std::ifstream& ifs)
{
	size_t currentPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	size_t size = ifs.tellg();
	ifs.seekg(currentPos);

	return size;
}

class Song
{
private:
	enum class Genre : char
	{
		Rock = 1 << 0,
		Pop = 1 << 1,
		PopRock,
		HipHop = 1 << 2,
		PopHipHop = (int)Pop | (int)HipHop,
		EDM = 1 << 3,
		RockEDM = (int)Rock | (int)EDM,
		PopEDM = (int)Pop | (int)EDM,
		Jazz = 1 << 4,
		PopJazz = (int)Pop | (int)Jazz,
		UNDEFINED = 1 << 5
	};

	char title[MAX_SONG_NAME_LENGTH + 1] = { '\0' };
	size_t duration = 0;
	Genre genre = Genre::UNDEFINED;
	char content[MAX_BYTES_LENGTH + 1] = { '\0' };

public:
	Song();

	const char* getTitle() const;
	const char* getContent() const;
	const size_t getDuration() const;
	const Genre getGenre() const;
	const char* getGenreText(const Genre genre) const;
	const size_t getGenreNumber(char genre) const;

	void setTitle(const char* title);
	void setDuration(size_t hrs, size_t mins, size_t seconds);
	void setGenre(const char* genre);
	void setContent(const char* fileName);

	void mix(const Song& newSong);
	void addRhythm(size_t k);

	void printSong() const;
};