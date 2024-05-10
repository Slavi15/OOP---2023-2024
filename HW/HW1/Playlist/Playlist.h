#pragma once
#include "Song.h"

#include <algorithm>

#define MAX_SONGS_COUNT 30
#define isDigit(ch) ch >= '0' && ch <= '9'

class Playlist
{
private:
	Song songs[MAX_SONGS_COUNT];
	size_t currentSize = 0;

	void selectionSort(bool(*isLower)(const Song& song1, const Song& song2));

public:
	Playlist();

	const size_t getCurrentSize() const;
	const Song& getSong(size_t index) const;

	void setCurrentSize(size_t currentSize);

	void add(const char* title, size_t hrs, size_t mins, size_t secs, const char* genre, const char* fileName);
	void find(const char* title) const;
	void findGenre(char genre);

	void sortByName();
	void sortByDuration();

	void modify(const char* title, size_t bits);

	void mix(const char* title1, const char* title2);

	void save(std::ofstream& ofs, const char* title) const;
	void save(const char* title, const char* fileName) const;

	void print() const;
};