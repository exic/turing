include Makefile.inc

OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
EXE = turing

all: $(EXE) $(OBJS)
#	gcc -fprofile-arcs -o $(EXE) $(OBJS)

$(EXE): $(OBJS)
	gcc -o $(EXE) $(OBJS)

run: all
	gdb -batch -x gdbbatch turing

include Makefile.stdrules
