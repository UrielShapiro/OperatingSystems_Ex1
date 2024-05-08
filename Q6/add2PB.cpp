#include <iostream>
#include <unistd.h>
#include <fcntl.h>

const char *PB_FILEPATH = "phonebook.txt";

bool add(std::string name, std::string num)
{
	// we will emulate the command:
	// echo $(name) , $(num) >> $(PB_FILEPATH)

	// fork to run `echo`
	if (fork() == 0)
	{
		dup2(open(PB_FILEPATH, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH), STDOUT_FILENO);
		execlp("echo", "echo", name.c_str(), ",", num.c_str(), (char *) NULL);	// execute the echo

	}
	return true;
}
// TODO: make this take command line arguments instead of stdin input
int main(void)
{
	std::string name, num;
	std::cout << "Enter name: ";
	std::getline(std::cin, name);
	std::cout << "Enter number: ";
	std::cin >> num;

	add(name, num);

	return 0;
}
