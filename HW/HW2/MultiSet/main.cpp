#include <iostream>

#include "MultiSet.h"

int main()
{
	{
		std::cout << "Compilation Test #1" << std::endl;

		try
		{
			MultiSet a(7, 3);
			a.add(2);
			a.add(2);
			a.add(3);
			a.add(3);
			a.add(3);
			a.add(5);
			a.printNumbers();
			a.printBinary();

			MultiSet b(9, 4);
			b.add(2);
			b.add(2);
			b.add(2);
			b.add(3);
			b.add(4);
			b.add(4);
			b.add(5);
			b.add(5);
			b.add(9);
			b.printNumbers();

			b.writeToFile("Demo.dat");

			MultiSet w;
			w.readFromFile("Demo.dat");
			w.printNumbers();

			MultiSet c = getIntersection(a, b);
			MultiSet d = getDifference(a, b);
			MultiSet k = getComplement(a);

			c.printNumbers();
			d.printNumbers();
			k.printNumbers();
		}
		catch (const std::out_of_range& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
		}
		catch (const std::logic_error& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
		}
		catch (const std::runtime_error& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
		}
		catch (const std::exception& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
		}
		catch (...)
		{
			std::cout << "Error!" << std::endl;
		}

		std::cout << "-------------------------------------------" << std::endl;
	}
	{
		std::cout << "Compilation Test #2" << std::endl;

		try
		{
			MultiSet ms(0, 2);
			ms.add(0);
			//ms.add(167); // throws exception
			getComplement(ms).printNumbers();

			MultiSet ff(15, 3);
			ff = getUnion(ms, ff);
			ff.printNumbers();
			ff.add(3);
			ff.add(13);

			MultiSet bs(ff);
			bs.add(13);
			bs.add(4);
			bs = getUnion(getComplement(ms), getIntersection(bs, ff));
			bs.printNumbers();
		}
		catch (const std::out_of_range& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
		}
		catch (const std::logic_error& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
		}
		catch (const std::runtime_error& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
		}
		catch (const std::exception& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
		}
		catch (...)
		{
			std::cout << "Error!" << std::endl;
		}

		std::cout << "-------------------------------------------" << std::endl;
	}
	{
		std::cout << "Compilation Test #3" << std::endl;

		try
		{
			MultiSet ms(8, 8);
			ms.add(0);
			ms.add(8);
			ms.add(3);
			ms.add(3);
			ms.add(3);

			ms.printNumbers();
			ms.printBinary();

			ms.writeToFile("a.bin");

			MultiSet bs(3, 3);
			bs.readFromFile("a.bin");

			bs.printNumbers();
			bs.printBinary();

			MultiSet mms(6, 2);
			mms.add(5);
			mms.add(4);

			MultiSet intersect = getIntersection(bs, getComplement(mms));
			intersect.printNumbers();
		}
		catch (const std::out_of_range& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
		}
		catch (const std::logic_error& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
		}
		catch (const std::runtime_error& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
		}
		catch (const std::exception& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
		}
		catch (...)
		{
			std::cout << "Error!" << std::endl;
		}

		std::cout << "-------------------------------------------" << std::endl;
	}
	{
		std::cout << "Compilation Test #4" << std::endl;

		try
		{
			MultiSet m(20, 3);

			m.add(2);
			m.add(2);
			m.add(2);
			m.add(2);
			m.add(2);
			m.add(2);
			m.add(2);

			m.add(5);
			m.add(5);
			m.add(5);
			m.add(5);
			m.add(5);
			m.add(5);
			m.add(5);

			m.printBinary();
		}
		catch (const std::out_of_range& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
		}
		catch (const std::logic_error& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
		}
		catch (const std::runtime_error& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
		}
		catch (const std::exception& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
		}
		catch (...)
		{
			std::cout << "Error!" << std::endl;
		}

		std::cout << "-------------------------------------------" << std::endl;
	}

	return 0;
}