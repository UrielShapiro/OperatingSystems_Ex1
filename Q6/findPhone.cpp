#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

const char *PB_FILEPATH = "phonebook.txt";

bool print_number(std::string name)
{
	// we will emulate the command:
	// grep $(name) < $(PB_FILEPATH) | cut -d, -f2 | xargs
	int pipe_grep_to_cut[2], pipe_cut_to_xargs[2];
	pipe(pipe_grep_to_cut);
	if (fork() == 0)
	{
		close(pipe_grep_to_cut[0]);
		dup2(open(PB_FILEPATH, O_RDONLY), STDIN_FILENO);
		dup2(pipe_grep_to_cut[1], STDOUT_FILENO);
		execlp("grep", "grep", name.c_str(), (char *) NULL);
	}
	
	pipe(pipe_cut_to_xargs);
	if (fork() == 0)
	{
		close(pipe_grep_to_cut[1]);
		close(pipe_cut_to_xargs[0]);
		dup2(pipe_grep_to_cut[0], STDIN_FILENO);
		dup2(pipe_cut_to_xargs[1], STDOUT_FILENO);
		execlp("cut", "cut", "-d,", "-f2", (char *) NULL);
	}
	int xargs_pid;
	close(pipe_grep_to_cut[0]);
	close(pipe_grep_to_cut[1]);
	if ((xargs_pid = fork()) == 0)
	{
		close(pipe_cut_to_xargs[1]);
		dup2(pipe_cut_to_xargs[0], STDIN_FILENO);
		execlp("xargs", "xargs", (char *) NULL);
		exit(0);
	}
	close(pipe_cut_to_xargs[0]);
	close(pipe_cut_to_xargs[1]);
	waitpid(xargs_pid, NULL, 0);
	return true;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "ERROR: Not enough arguments" << std::endl;
		std::cerr << "USAGE: " << argv[0] << " <name>" << std::endl;
		return 1;
	}

	std::string name(argv[1]);
	std::cout << name << "'s phone number is: " << std::flush;
	print_number(name);
	return 0;
}
