#include <iostream>

#include "StudentCollection.h"

int main()
{
    Student st1("Ivan", 16);
    Student st2("Maria", 16);

    StudentCollection students;
    students.addAtFirstFreeIndex(st1);
    students.addAtFirstFreeIndex(st2);

    students.remove(0);
    std::cout << students.getNumberInClass("Maria") << std::endl; //2

    Student st3("Pesho", 18);
    students.addAtFirstFreeIndex(st3);
    std::cout << students.getNumberInClass("Pesho") << std::endl; //1

    Student st4("Marto", 19);
    students.insert(st4, 0);
    std::cout << students.getNumberInClass("Marto") << std::endl; //1

	return 0;
}