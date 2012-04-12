include Makefile.inc

OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
EXE = turing

all: $(EXE) $(OBJS)

$(EXE): $(OBJS)
#	gcc -o $(EXE) $(OBJS)
	gcc -fprofile-arcs -o $(EXE) $(OBJS)

run:
	./$(EXE) rules.txt init.txt
run-gdb: all
	gdb -batch -x gdbbatch --args turing rules.txt init.txt

coverage:
	gcov main.o tape.o

include Makefile.stdrules
