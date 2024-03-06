#include <iostream>
#include <fstream>
#include <sstream>

namespace CONSTANTS
{
	const unsigned int MAX_NAME_LENGTH = 50;
	const unsigned int MAX_PHONE_LENGTH = 20;
	const unsigned int MAX_ADDRESS_LENGTH = 100;
}

namespace ShippingNS
{
	enum class PizzaType { Margarita, Kaltzone, Burrata };
	enum class PizzaSize { S, M, L };

	struct Pizza
	{
		PizzaType pizzaType;
		PizzaSize pizzaSize;
		double price;
	};

	struct Delivery
	{
		char name[CONSTANTS::MAX_NAME_LENGTH + 1];
		char phoneNumber[CONSTANTS::MAX_PHONE_LENGTH + 1];
		char address[CONSTANTS::MAX_ADDRESS_LENGTH + 1];
		double price;
		Pizza pizza[20];
		size_t pizzaCount;
	};

	struct Deliveries
	{
		Delivery deliveries[20];
		size_t currentCount = 0;
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

	void readPizza(std::ifstream& ifs, Pizza& pizza)
	{
		ifs.read((char*)&pizza, sizeof(pizza));
	}

	void readDelivery(std::ifstream& ifs, Delivery& delivery)
	{
		ifs.read((char*)&delivery.name, myStrLen(delivery.name) * sizeof(char));
		ifs.read((char*)&delivery.phoneNumber, myStrLen(delivery.phoneNumber) * sizeof(char));
		ifs.read((char*)&delivery.address, myStrLen(delivery.address) * sizeof(char));
		ifs.read((char*)&delivery.price, sizeof(double));

		ifs >> delivery.pizzaCount;

		for (size_t i = 0; i < delivery.pizzaCount; i++)
			readPizza(ifs, delivery.pizza[i]);
	}

	Deliveries readFromFile(std::ifstream& ifs)
	{
		Deliveries deliveries;

		while (!ifs.eof())
			readDelivery(ifs, deliveries.deliveries[deliveries.currentCount++]);

		return deliveries;
	}

	Deliveries readFromFile(const char* fileName)
	{
		if (!fileName) return;

		std::ifstream ifs(fileName, std::ios::in | std::ios::binary);
		if (!ifs.is_open()) return;

		return readFromFile(ifs);
	}

	void sortDeliveries(Deliveries& deliveries, bool(*isLower)(const Delivery& d1, const Delivery& d2))
	{
		for (size_t i = 0; i < deliveries.currentCount - 1; i++)
		{
			size_t minIndex = i;

			for (size_t j = i + 1; j < deliveries.currentCount; j++)
				if (isLower(deliveries.deliveries[j], deliveries.deliveries[minIndex]))
					minIndex = j;

			if (minIndex != i)
				std::swap(deliveries.deliveries[minIndex], deliveries.deliveries[i]);
		}
	}

	void sortByAddress(Deliveries& deliveries)
	{
		return sortDeliveries(deliveries, [](const Delivery& d1, const Delivery& d2) { return strcmp(d1.address, d2.address) < 0; });
	}

	void writeToFile(const char* fileName, Deliveries& deliveries)
	{
		if (!fileName) return;

		std::ofstream ofs(fileName, std::ios::out | std::ios::binary);
		if (!ofs.is_open()) return;

		sortByAddress(deliveries);

		ofs.write((const char*)&deliveries, sizeof(deliveries));
	}
}

int main()
{


	return 0;
}