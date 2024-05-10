#include <iostream>
#include <cmath>

#include "ModifiableIntegersFunction.h"

int main()
{
	// Every scope block should be debugged separately or all of them in Release
	{
		std::cout << "Compilation Test #1" << std::endl;

		try
		{
			ModifiableIntegersFunction m1([](int16_t x) -> int16_t { return x; });
			ModifiableIntegersFunction m2([](int16_t x) -> int16_t { return x + 10; });
			ModifiableIntegersFunction m3([](int16_t x) -> int16_t { return x * x; });
			ModifiableIntegersFunction m4([](int16_t x) -> int16_t { return exp(x); });
			ModifiableIntegersFunction m5([](int16_t x) -> int16_t { return x; });

			std::cout << (m1 < m2) << std::endl;
			std::cout << (m1 > m3) << std::endl;
			std::cout << (m3 == m4) << std::endl;
			std::cout << (m1 != m2) << std::endl;
			std::cout << (m2 >= m1) << std::endl;
			std::cout << (m1 <= m5) << std::endl;
			std::cout << (m1 > m5) << std::endl;
			std::cout << (m1 == m5) << std::endl;
			std::cout << (m1 == m2) << std::endl;
			std::cout << (m1 < m5) << std::endl;
		}
		catch (const std::invalid_argument& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::out_of_range& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::runtime_error& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::exception& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (...)
		{
			std::cout << "Error!";
		}

		std::cout << "----------------------------------------------" << std::endl;
	}
	{
		std::cout << "Compilation Test #2" << std::endl;

		try
		{
			ModifiableIntegersFunction m([](int16_t x) -> int16_t { return exp(x); });
			ModifiableIntegersFunction m2([](int16_t x) -> int16_t { return log(x); });
			ModifiableIntegersFunction m3([](int16_t x) -> int16_t { return x * x * x; });
			ModifiableIntegersFunction m4([](int16_t x) -> int16_t { return tan(x); });

			m.draw(0, 0);
			m2.draw(0, 0);
			m3.draw(0, 0);
			m4.draw(0, 0);
		}
		catch (const std::invalid_argument& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::out_of_range& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::runtime_error& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::exception& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (...)
		{
			std::cout << "Error!";
		}

		std::cout << "----------------------------------------------" << std::endl;
	}
	{
		std::cout << "Compilation Test #3" << std::endl;

		try
		{
			ModifiableIntegersFunction m([](int16_t x) -> int16_t { return x; });
			ModifiableIntegersFunction m2([](int16_t x) -> int16_t { return x + 42; });
			ModifiableIntegersFunction m3([](int16_t x) -> int16_t { return x * x; });

			std::cout << (m || m2) << std::endl;
			std::cout << (m || m3) << std::endl;
		}
		catch (const std::invalid_argument& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::out_of_range& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::runtime_error& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::exception& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (...)
		{
			std::cout << "Error!";
		}

		std::cout << "----------------------------------------------" << std::endl;
	}
	{
		std::cout << "Compilation Test #4" << std::endl;

		try
		{
			ModifiableIntegersFunction m([](int16_t x) -> int16_t { return x; });
			ModifiableIntegersFunction m2([](int16_t x) -> int16_t { return x; });
			ModifiableIntegersFunction m3([](int16_t x) -> int16_t { return 4 * x; });

			m.disablePoint(1);
			m += m2;
			m.draw(0, 0);

			ModifiableIntegersFunction m5([](int16_t x) -> int16_t { return 2 * x; });
			m5.draw(0, 0);

			m3 -= m2;
			m3.draw(0, 0);

			ModifiableIntegersFunction m4([](int16_t x) -> int16_t { return 3 * x; });
			m4.draw(0, 0);

			//(m3 - m5).draw(0, 0);
		}
		catch (const std::invalid_argument& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::out_of_range& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::runtime_error& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::exception& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (...)
		{
			std::cout << "Error!";
		}

		std::cout << "----------------------------------------------" << std::endl;
	}
	{
		std::cout << "Compilation Test #5" << std::endl;

		try
		{
			ModifiableIntegersFunction m([](int16_t x) -> int16_t { return x; });

			std::cout << m.isInjection() << std::endl;
			std::cout << m.isSurjection() << std::endl;

			ModifiableIntegersFunction m2([](int16_t x) -> int16_t { return sqrt(x); });

			std::cout << m2.isInjection() << std::endl;
			std::cout << m2.isSurjection() << std::endl;

			ModifiableIntegersFunction m3([](int16_t x) -> int16_t { return x / 2; });

			std::cout << m3.isInjection() << std::endl;
			std::cout << m3.isSurjection() << std::endl;
		}
		catch (const std::invalid_argument& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::out_of_range& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::runtime_error& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::exception& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (...)
		{
			std::cout << "Error!";
		}

		std::cout << "----------------------------------------------" << std::endl;
	}
	{
		std::cout << "Compilation Test #6" << std::endl;

		try
		{
			ModifiableIntegersFunction m([](int16_t x) -> int16_t { return x; });
			ModifiableIntegersFunction m2([](int16_t x) -> int16_t { return x * 2; });

			m.draw(0, 0);

			m.writeToFile("m6.dat");
			m2.readFromFile("m6.dat");

			m2.draw(0, 0);
		}
		catch (const std::invalid_argument& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::out_of_range& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::runtime_error& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::exception& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (...)
		{
			std::cout << "Error!";
		}

		std::cout << "----------------------------------------------" << std::endl;
	}
	{
		std::cout << "Compilation Test #7" << std::endl;

		try
		{
			ModifiableIntegersFunction m([](int16_t x) -> int16_t { return x; });
			ModifiableIntegersFunction m2([](int16_t x) -> int16_t { return x + 1; });
			ModifiableIntegersFunction m3([](int16_t x) -> int16_t { return x + 3; });

			(m2 ^ 2).draw(0, 0);

			m.operator()([](int16_t x) -> int16_t { return x + 1; });
			m.draw(0, 0);

			m3.operator()([](int16_t x) -> int16_t { return x * x; }).draw(0, 0);
		}
		catch (const std::invalid_argument& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::out_of_range& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::runtime_error& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::exception& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (...)
		{
			std::cout << "Error!";
		}

		std::cout << "----------------------------------------------" << std::endl;
	}
	{
		std::cout << "Compilation Test #8" << std::endl;

		try
		{
			ModifiableIntegersFunction m([](int16_t x) -> int16_t { return x; });
			ModifiableIntegersFunction m3([](int16_t x) -> int16_t { return x * x; });

			(~m).draw(0, 0);
			(~m3).draw(0, 0);
		}
		catch (const std::invalid_argument& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::out_of_range& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::runtime_error& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (const std::exception& exc)
		{
			std::cout << "Error: " << exc.what();
		}
		catch (...)
		{
			std::cout << "Error!";
		}

		std::cout << "----------------------------------------------" << std::endl;
	}

	return 0;
}