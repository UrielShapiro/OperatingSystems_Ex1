QS = Q1 Q2 Q3 Q4 Q5 Q6

all: $(foreach q, $(QS), $(q)_all)

clean: $(foreach q, $(QS), $(q)_clean)

%_all:
	-make -C $* all

%_clean:
	-make -C $* clean

.PHONY: $(QS)
