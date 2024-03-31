#include <iostream>
#include <fstream>

#define MAX_PASSWORD_LENGTH 1024
#define PROBLEMS_COUNT 20

class Problem
{
private:
	char* problemText = nullptr;
	char correctAnswer;
	double points = 0.0;
	char password[MAX_PASSWORD_LENGTH + 1];

public:
	Problem(const char* problemText, char correctAnswer, double points, const char* password);

	const char* getProblemText() const;
	const char getCorrectAnswer() const;
	const double getPoints() const;

	void setProblemText(const char* problemText);
	void setCorrectAnswer(char correctAnswer);
	void setPoints(double points);
	void setPassword(const char* password);

	void createProblem(const char* problemText, char correctAnswer, double points, const char* password);
	void editProblem(const char* newContent, const char* password);
	void editCorrectAnswer(char newAnswer, const char* password);
	void editPoints(double points, const char* password);
};

class Exam
{
private:
	Problem problems[PROBLEMS_COUNT];

public:
	void readFromFile(std::ifstream& ifs);
	void readFromFile(const char* fileName);

	void writeToFile(std::ofstream& ofs);
	void writeToFile(const char* fileName);

	const double getExamPoints() const;
};

Problem::Problem(const char* problemText, char correctAnswer, double points, const char* password)
{
	setProblemText(problemText);
	setCorrectAnswer(correctAnswer);
	setPoints(points);
	setPassword(password);
}

void Problem::setProblemText(const char* problemText)
{
	if (!problemText) return;

	delete[] this->problemText;
	this->problemText = new char[strlen(problemText) + 1];
	strcpy(this->problemText, problemText);
}

void Problem::setCorrectAnswer(char correctAnswer)
{
	this->correctAnswer = correctAnswer;
}

void Problem::setPoints(double points)
{
	if (points >= 0)
		this->points = points;
}

void Problem::setPassword(const char* password)
{
	if (!password) return;

	strcpy(this->password, password);
}

const char* Problem::getProblemText() const
{
	return problemText;
}

const char Problem::getCorrectAnswer() const
{
	return correctAnswer;
}

const double Problem::getPoints() const
{
	return points;
}

void Problem::createProblem(const char* problemText, char correctAnswer, double points, const char* password)
{
	if (!problemText || !password) return;

	if (strcmp(this->password, password) == 0)
	{
		setProblemText(problemText);
		setCorrectAnswer(correctAnswer);
		setPoints(points);
	}
}

void Problem::editProblem(const char* newContent, const char* password)
{
	if (!newContent || !password) return;

	if (strcmp(this->password, password) == 0)
		setProblemText(newContent);
}

void Problem::editCorrectAnswer(char newAnswer, const char* password)
{
	if (!password) return;

	if (strcmp(this->password, password) == 0)
		setCorrectAnswer(newAnswer);
}

void Problem::editPoints(double points, const char* password)
{
	if (!password) return;

	if (strcmp(this->password, password) == 0)
		setPoints(points);
}

void Exam::readFromFile(std::ifstream& ifs)
{
	ifs.read((char*)problems, sizeof(problems));
}

void Exam::readFromFile(const char* fileName)
{
	if (!fileName) return;

	std::ifstream ifs(fileName, std::ios::in | std::ios::binary);
	if (!ifs.is_open()) return;

	return readFromFile(ifs);
}

void Exam::writeToFile(std::ofstream& ofs)
{
	ofs.write((const char*)problems, sizeof(problems));
}

void Exam::writeToFile(const char* fileName)
{
	if (!fileName) return;

	std::ofstream ofs(fileName, std::ios::out | std::ios::binary);
	if (!ofs.is_open()) return;

	return writeToFile(ofs);
}

const double Exam::getExamPoints() const
{
	double points = 0;

	for (size_t i = 0; i < PROBLEMS_COUNT; i++)
		points += problems[i].getPoints();

	return points;
}

int main()
{
	return 0;
}