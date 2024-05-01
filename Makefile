QS = Q1 Q2 Q3 Q4 Q5 Q6
QS_ALL = $(foreach q, $(QS), $(q)_all)
QS_CLEAN = $(foreach q, $(QS), $(q)_clean)

all: $(QS_ALL)
clean: $(QS_CLEAN)

$(QS_ALL):
	-make -C $(@:_all=) all

$(QS_CLEAN):
	-make -C $(@:_clean=) clean

.SUFFIXES:
.PHONY: all clean $(QS_ALL) $(QS_CLEAN)
