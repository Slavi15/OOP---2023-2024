#include <iostream>
#include <fstream>

namespace RelationsNS
{
	struct Pair
	{
		int x, y;
	};

	struct Relation
	{
		Pair pairs[25];
		size_t currentSize = 0;
	};

	void addPairToRelation(const Pair& pair, Relation& relation)
	{
		relation.pairs[relation.currentSize] = pair;
		relation.currentSize++;
	}

	void writePairToFile(std::ofstream& ofs, const Pair& pair)
	{
		ofs << pair.x << ' ' << pair.y << ' ';
	}

	void readPairFromFile(std::ifstream& ifs, Pair& pair)
	{
		ifs >> pair.x >> pair.y;
	}

	void writeRelationToFile(const Relation& relations, const char* fileName)
	{
		if (!fileName)
			return;

		std::ofstream ofs(fileName);

		if (!ofs.is_open())
			return;

		ofs << relations.currentSize << ' ';

		for (size_t i = 0; i < relations.currentSize; i++)
			writePairToFile(ofs, relations.pairs[i]);

		ofs.close();
	}

	void readRelationFromFile(Relation& relations, const char* fileName)
	{
		if (!fileName)
			return;

		std::ifstream ifs(fileName);

		ifs >> relations.currentSize;

		if (!ifs.is_open())
			return;

		for (size_t i = 0; i < relations.currentSize; i++)
			readPairFromFile(ifs, relations.pairs[i]);

		ifs.close();
	}
}

int main()
{
	RelationsNS::Relation relations = { 0 };
	RelationsNS::writeRelationToFile(relations, "result.txt");
	RelationsNS::readRelationFromFile(relations, "result.txt");

	return 0;
}