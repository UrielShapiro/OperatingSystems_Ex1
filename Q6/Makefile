CPP = g++
CPP_FLAGS = -Wall -Wextra

all: add2PB findPhone
add2PB: add2PB.cpp
	$(CPP) $(CPP_FLAGS) -o add2PB add2PB.cpp

findPhone: findPhone.cpp
	$(CPP) $(CPP_FLAGS) -o findPhone findPhone.cpp

clean:
	rm -f add2PB findPhone

clean_pb:
	rm -f phonebook.txt

.SUFFIXES:
.PHONY: all clean clean_pb
