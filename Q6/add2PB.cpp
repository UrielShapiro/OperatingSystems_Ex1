#include <cassert>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

const char *PB_FILEPATH = "phonebook.txt";

bool add(std::string name, std::string num)
{
	// we will emulate the command:
	// echo $(name) , $(num) | tee --append $(PB_FILEPATH) > /dev/null
	// this will write the entry, append it into the phonebook, and throw the output of `tee` to the black hole

	int pipe_echo_to_tee[2];	// create a pipe to put between `echo` and `tee`
	pipe(pipe_echo_to_tee);
	
	// fork to run `echo`
	if (fork() == 0)
	{
		dup2(pipe_echo_to_tee[1], STDOUT_FILENO);	// set the output of echo to go into the pipe's write-end
		execlp("echo", "echo", name.c_str(), ",", num.c_str(), (char *) NULL);	// execute the echo

	}
	
	// fork to run `tee`
	if (fork() == 0)
	{
		dup2(pipe_echo_to_tee[0], STDIN_FILENO);	// set the read-end of the pipe as the input of tee
		dup2(open("/dev/null", O_WRONLY), STDOUT_FILENO);	// set the output of tee to /dev/null to throw away
		execlp("tee", "tee", "--append", PB_FILEPATH, (char *) NULL);	// execute tee
	}
	return true;
}

int main()
{
	std::string name, num;
	std::cout << "Enter name: ";
	std::getline(std::cin, name);
	std::cout << "Enter number: ";
	std::cin >> num;

	add(name, num);

	return 0;
}
