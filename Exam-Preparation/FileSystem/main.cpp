#include <iostream>

#include "FileSystem.h"

int main()
{
	FileSystem fs;

	fs.getFile("root")->print();

	fs.createTextFile("root/file.txt", "samplecontent");
	fs.createTextFile("root/dir1/dir2/random", "randomcontent");
	fs.createTextFile("root/dir1/dir2/random2", "randomcontent");

	fs.getFile("root")->print();

	return 0;
}