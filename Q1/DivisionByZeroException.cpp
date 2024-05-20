int main() {
	// make gcc ignore the blatant error
#pragma GCC diagnostic ignored "-Wdiv-by-zero"
	// force the compiler to divide by zero to calculate the return value
    return 1/0;
}
