#include <iostream>
#include <fstream>
#include <sstream>

namespace ObjectsArrayNS
{
	struct Person
	{
		char* name = nullptr;
		unsigned int age = 0;
	};

	struct People
	{
		Person* people = nullptr;
		size_t currentSize = 0;
	};

	Person initPerson(const char* name, unsigned int age)
	{
		Person person;

		person.name = new char[strlen(name) + 1];
		strcpy(person.name, name);

		person.age = age;

		return person;
	}

	void readPerson(std::ifstream& ifs, Person& person)
	{
		size_t nameLen = 0;
		ifs.read((char*)&nameLen, sizeof(nameLen));

		person.name = new char[nameLen + 1];
		ifs.read((char*)person.name, nameLen + 1);
		ifs.read((char*)&person.age, sizeof(person.age));
	}

	People readFromFile(std::ifstream& ifs)
	{
		People people;

		ifs.read((char*)&people.currentSize, sizeof(people.currentSize));

		people.people = new Person[people.currentSize];

		for (size_t i = 0; i < people.currentSize; i++)
			readPerson(ifs, people.people[i]);

		return people;
	}

	People readFromFile(const char* fileName)
	{
		if (!fileName) return People{};

		std::ifstream ifs(fileName, std::ios::in | std::ios::binary);
		if (!ifs.is_open()) return People{};

		return readFromFile(ifs);
	}

	void writePerson(std::ofstream& ofs, const Person& person)
	{
		size_t nameLen = strlen(person.name);
		ofs.write((const char*)&nameLen, sizeof(nameLen));

		ofs.write((const char*)person.name, nameLen + 1);
		ofs.write((const char*)&person.age, sizeof(person.age));
	}

	void writeToFile(std::ofstream& ofs, const People& people)
	{
		ofs.write((const char*)&people.currentSize, sizeof(people.currentSize));

		for (size_t i = 0; i < people.currentSize; i++)
			writePerson(ofs, people.people[i]);
	}

	void writeToFile(const char* fileName, const People& people)
	{
		if (!fileName) return;

		std::ofstream ofs(fileName, std::ios::out | std::ios::binary);
		if (!ofs.is_open()) return;

		return writeToFile(ofs, people);
	}

	void freePeople(People& people)
	{
		for (size_t i = 0; i < people.currentSize; i++)
		{
			delete[] people.people[i].name;
			people.people[i].name = nullptr;
		}

		delete[] people.people;
		people.people = nullptr;
		people.currentSize = 0;
	}

	void printPeople(const People& people)
	{
		for (size_t i = 0; i < people.currentSize; i++)
			std::cout << "Name: " << people.people[i].name << ' ' << "Age: " << people.people[i].age << std::endl;
	}
}

int main()
{
	// Writing to File
	{
		ObjectsArrayNS::People people;
		people.currentSize = 2;
		people.people = new ObjectsArrayNS::Person[people.currentSize];
		people.people[0] = ObjectsArrayNS::initPerson("Angel", 28);
		people.people[1] = ObjectsArrayNS::initPerson("Ivan", 20);

		ObjectsArrayNS::writeToFile("result.txt", people);

		ObjectsArrayNS::freePeople(people);
	}

	// Reading from File
	{
		ObjectsArrayNS::People people = ObjectsArrayNS::readFromFile("result.txt");
		ObjectsArrayNS::printPeople(people);
		ObjectsArrayNS::freePeople(people);
	}

	return 0;
}