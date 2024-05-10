#include "Song.h"

Song::Song() = default;

const char* Song::getTitle() const
{
	return title;
}

const size_t Song::getDuration() const
{
	return duration;
}

const Song::Genre Song::getGenre() const
{
	return genre;
}

const size_t Song::getGenreNumber(char genre) const
{
	size_t result = 0;

	if (genre == 'r')
		result |= (int)Genre::Rock;
	if (genre == 'p')
		result |= (int)Genre::Pop;
	if (genre == 'h')
		result |= (int)Genre::HipHop;
	if (genre == 'e')
		result |= (int)Genre::EDM;
	if (genre == 'j')
		result |= (int)Genre::Jazz;

	return result;
}

const char* Song::getGenreText(const Genre genre) const
{
	switch (genre)
	{
	case Genre::Rock:
		return "Rock";
	case Genre::Pop:
		return "Pop";
	case Genre::PopRock:
		return "Pop & Rock";
	case Genre::HipHop:
		return "Hip-Hop";
	case Genre::PopHipHop:
		return "Pop & Hip-Hop";
	case Genre::EDM:
		return "EDM";
	case Genre::PopEDM:
		return "Pop & EDM";
	case Genre::RockEDM:
		return "Rock & EDM";
	case Genre::Jazz:
		return "Jazz";
	case Genre::PopJazz:
		return "Pop & Jazz";
	}

	return "Genre not defined in enum!";
}

const char* Song::getContent() const
{
	return content;
}

void Song::setTitle(const char* title)
{
	if (!title) return;

	if (strlen(title) <= MAX_SONG_NAME_LENGTH)
		strcpy(this->title, title);
}

void Song::setDuration(size_t hrs, size_t mins, size_t seconds)
{
	size_t duration = (hrs * 3600) + (mins * 60) + seconds;

	this->duration = duration;
}

void Song::setGenre(const char* genre)
{
	if (!genre) return;

	size_t result = 0;

	while (*genre)
	{
		switch (*genre)
		{
		case 'r':
			result |= (int)Genre::Rock;
			break;
		case 'p':
			result |= (int)Genre::Pop;
			break;
		case 'h':
			result |= (int)Genre::HipHop;
			break;
		case 'e':
			result |= (int)Genre::EDM;
			break;
		case 'j':
			result |= (int)Genre::Jazz;
			break;
		}

		genre++;
	}

	this->genre = (Genre)result;
}

void Song::setContent(const char* fileName)
{
	if (!fileName) return;

	std::ifstream ifs(fileName, std::ios::in | std::ios::binary);
	if (!ifs.is_open()) return;

	if (getFileSize(ifs) <= MAX_BYTES_LENGTH)
		ifs.read((char*)this->content, sizeof(this->content));

	ifs.close();
}

void Song::mix(const Song& newSong)
{
	size_t contentLength = getMin(strlen(content), strlen(newSong.getContent()));

	for (size_t i = 0; i < contentLength; i++)
		content[i] = (char)(content[i] ^ newSong.getContent()[i]);
}

void Song::addRhythm(size_t k)
{
	size_t contentLength = strlen(content);

	for (int i = contentLength - 1, bits = k - 1; i >= 0; i--)
		for (size_t j = 0; j < CHAR_BITS_LENGTH; j++)
		{
			if (bits == 0) content[i] |= (1 << j);
			bits = (bits + k - 1) % k;
		}
}

void Song::printSong() const
{
	std::cout << title << ", " << duration / 3600 << ":" << duration / 60 << ":" << duration % 60 << ", " << getGenreText(genre) << std::endl;
}