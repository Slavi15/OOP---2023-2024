#include "Playlist.h"

Playlist::Playlist() = default;

const size_t Playlist::getCurrentSize() const
{
	return currentSize;
}

const Song& Playlist::getSong(size_t index) const
{
	return songs[index - 1];
}

void Playlist::setCurrentSize(size_t currentSize)
{
	this->currentSize = currentSize;
}

void Playlist::add(const char* title, size_t hrs, size_t mins, size_t secs, const char* genre, const char* fileName)
{
	if (!title || !genre || !fileName) return;

	songs[currentSize].setTitle(title);
	songs[currentSize].setDuration(hrs, mins, secs);
	songs[currentSize].setGenre(genre);
	songs[currentSize].setContent(fileName);

	currentSize++;
}

void Playlist::find(const char* title) const
{
	if (!title) return;

	for (size_t i = 0; i < currentSize; i++)
		if (strcmp(songs[i].getTitle(), title) == 0)
			songs[i].printSong();
}

void Playlist::findGenre(char genre)
{
	for (size_t i = 0; i < currentSize; i++)
		if (((int)songs[i].getGenre() | songs[i].getGenreNumber(genre)) == (int)songs[i].getGenre())
			songs[i].printSong();
}

void Playlist::selectionSort(bool(*isLower)(const Song& song1, const Song& song2))
{
	for (size_t i = 0; i < currentSize - 1; i++)
	{
		size_t minIndex = i;

		for (size_t j = i + 1; j < currentSize; j++)
			if (isLower(songs[j], songs[minIndex]))
				minIndex = j;

		if (minIndex != i)
			std::swap(songs[i], songs[minIndex]);
	}
}

void Playlist::sortByName()
{
	return selectionSort([](const Song& song1, const Song& song2) -> bool { return strcmp(song1.getTitle(), song2.getTitle()) < 0; });
}

void Playlist::sortByDuration()
{
	return selectionSort([](const Song& song1, const Song& song2) -> bool { return song1.getDuration() < song2.getDuration(); });
}

void Playlist::modify(const char* title, size_t bits)
{
	if (!title) return;

	for (size_t i = 0; i < currentSize; i++)
		if (strcmp(songs[i].getTitle(), title) == 0)
			songs[i].addRhythm(bits);
}

void Playlist::mix(const char* title1, const char* title2)
{
	if (!title1 || !title2) return;

	size_t indexOne = 0, indexTwo = 0;

	for (size_t i = 0; i < currentSize; i++)
		if (strcmp(songs[i].getTitle(), title1) == 0)
			indexOne = i;
		else if (strcmp(songs[i].getTitle(), title2) == 0)
			indexTwo = i;

	return songs[indexOne].mix(songs[indexTwo]);
}

void Playlist::save(std::ofstream& ofs, const char* title) const
{
	if (!title) return;

	for (size_t i = 0; i < currentSize; i++)
		if (strcmp(songs[i].getTitle(), title) == 0)
		{
			ofs.write((const char*)songs[i].getContent(), sizeof(songs[i].getContent()));
			return;
		}
}

void Playlist::save(const char* title, const char* fileName) const
{
	if (!title || !fileName) return;

	std::ofstream ofs(fileName, std::ios::out | std::ios::binary);
	if (!ofs.is_open()) return;

	return save(ofs, title);
}

void Playlist::print() const
{
	for (size_t i = 0; i < currentSize; i++)
		songs[i].printSong();
}