#include <iostream>
#include <fstream>
#include <sstream>

namespace CONSTANTS
{
	const unsigned int MAX_NAME_LENGTH = 25;
}

namespace JobsNS
{
	struct Job
	{
		char name[CONSTANTS::MAX_NAME_LENGTH + 1];
		size_t codersCount;
		size_t paidDaysCount;
		long long money;
	};

	unsigned int myStrLen(const char* str)
	{
		if (!str) return 0;

		unsigned int res = 0;
		while (*str)
		{
			res++;
			str++;
		}

		return res;
	}

	Job readJob(std::ifstream& ifs)
	{
		Job job;

		ifs.read((char*)&job.name, sizeof(char) * myStrLen(job.name));
		ifs.read((char*)&job.codersCount, sizeof(size_t));
		ifs.read((char*)&job.paidDaysCount, sizeof(size_t));
		ifs.read((char*)&job.money, sizeof(long long));

		return job;
	}

	Job writeJob(std::ofstream& ofs)
	{
		Job job;

		std::cin.ignore();
		std::cin.getline(job.name, CONSTANTS::MAX_NAME_LENGTH + 1);
		std::cin >> job.codersCount >> job.paidDaysCount >> job.money;

		ofs.write((const char*)&job, sizeof(Job));

		return job;
	}

	void writeJobs(const char* fileName)
	{
		if (!fileName) return;

		std::ofstream ofs(fileName, std::ios::out | std::ios::ate | std::ios::binary);
		if (!ofs.is_open()) return;

		size_t N;
		std::cin >> N;

		for (size_t i = 0; i < N; i++)
			writeJob(ofs);
	}

	void filterOffers(std::ifstream& ifs, long long minSalary)
	{
		while (!ifs.eof())
		{
			Job job = readJob(ifs);

			if (job.money >= minSalary)
				std::cout << "Name: " << job.name << std::endl <<
				"Programmers: " << job.codersCount << std::endl <<
				"Paid Days: " << job.paidDaysCount << std::endl <<
				"Salary: " << job.money << std::endl;
		}
	}

	void filterOffers(const char* filePath, long long minSalary)
	{
		if (!filePath) return;

		std::ifstream ifs(filePath, std::ios::in | std::ios::binary);
		if (!ifs.is_open()) return;

		return filterOffers(ifs, minSalary);
	}

	bool existOffer(std::ifstream& ifs, const char* name)
	{
		if (!name) return false;

		while (!ifs.eof())
		{
			Job job = readJob(ifs);

			if (strcmp(job.name, name) == 0)
				return true;
		}

		return false;
	}

	bool existOffer(const char* filePath, const char* name)
	{
		if (!filePath || !name) return false;

		std::ifstream ifs(filePath, std::ios::in | std::ios::binary);
		if (!ifs.is_open()) return false;

		return existOffer(ifs, name);
	}

	void perfectOffer(std::ifstream& ifs, std::ofstream& ofs, int maxCoworkers, int minVacancyDays, int minSalary)
	{
		while (!ifs.eof())
		{
			Job job = readJob(ifs);

			if (job.codersCount <= maxCoworkers && job.paidDaysCount <= minVacancyDays && job.money <= minSalary)
				ofs.write((const char*)&job, sizeof(Job));
		}
	}

	void perfectOffer(const char* filePath, int maxCoworkers, int minVacancyDays, int minSalary)
	{
		if (!filePath) return;

		std::ifstream ifs(filePath, std::ios::in | std::ios::binary);
		std::ofstream ofs(filePath, std::ios::out | std::ios::binary);
		if (!ofs.is_open() && !ifs.is_open()) return;

		return perfectOffer(ifs, ofs, maxCoworkers, minVacancyDays, minSalary);
	}
}

int main()
{


	return 0;
}