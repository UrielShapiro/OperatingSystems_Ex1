// an infinitely recursive function, will fill the stack
int infinite_recursion() {
    return infinite_recursion();
}

int main() {
	// call the function to cause a stack overflow
    infinite_recursion();
    return 0;
}
