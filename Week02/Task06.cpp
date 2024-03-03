#include <iostream>
#include <fstream>

namespace UsersNS
{
	struct User
	{
		char name[128 + 1];
		char email[128 + 1];
		char password[128 + 1];
	};

	struct System
	{
		User users[100];
		size_t currentCount = 0;
	};

	bool userExists(const System& system, const char* email, const char* pass)
	{
		if (!email) return false;

		for (size_t i = 0; i < system.currentCount; i++)
			if (strcmp(system.users[i].email, email) == 0 &&
				strcmp(system.users[i].password, pass) == 0)
				return true;

		return false;
	}

	void readUser(std::ifstream& ifs, User& user)
	{
		ifs.getline(user.name, 128, ' ');
		ifs >> user.email >> user.password;
		ifs.ignore();
	}

	void writeUser(std::ofstream& ofs, const User& user)
	{
		ofs << user.name << ' ' << user.email << ' ' << user.password << std::endl;
	}

	void readSystem(const char* fileName, System& system)
	{
		if (!fileName) return;

		std::ifstream ifs(fileName);
		if (!ifs.is_open()) return;

		ifs >> system.currentCount;
		ifs.ignore();

		for (size_t i = 0; i < system.currentCount; i++)
			readUser(ifs, system.users[i]);

		ifs.close();
	}

	void writeSystem(const char* fileName, const System& system)
	{
		if (!fileName) return;

		std::ofstream ofs(fileName);
		if (!ofs.is_open()) return;

		ofs << system.currentCount << std::endl;

		for (size_t i = 0; i < system.currentCount; i++)
			writeUser(ofs, system.users[i]);

		ofs.close();
	}

	void registerUser(System& system)
	{
		if (system.currentCount > 100) return;

		User user;

		std::cout << "Enter name: ";
		std::cin.getline(user.name, 128);
		std::cout << "Enter email: ";
		std::cin >> user.email;
		std::cout << "Enter password: ";
		std::cin >> user.password;

		system.users[system.currentCount] = user;
		system.currentCount++;

		std::cout << "Registration successful" << std::endl;
	}

	void loginUser(System& system)
	{
		readSystem("result.txt", system);

		User user;

		std::cout << "Enter email: ";
		std::cin >> user.email;
		std::cout << "Enter password: ";
		std::cin >> user.password;

		if (userExists(system, user.email, user.password))
			std::cout << "Login successful" << std::endl;
	}
}

int main()
{

	return 0;
}