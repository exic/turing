include Makefile.inc

#OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
OBJS = main.o tape.o
STDOBJS = $(OBJS) goodmalloc.o
EXE = turing

all: $(EXE) $(STDOBJS)

$(EXE): $(STDOBJS)
#	gcc -o $(EXE) $(STDOBJS)
	gcc -fprofile-arcs -o $(EXE) $(STDOBJS)

run: all
	./$(EXE) rules.txt init.txt
run-gdb: all
	gdb -batch -x gdbbatch --args turing rules.txt init.txt

run-all: all badmalloc.o
	bash -c './$(EXE) rules6.7 <(echo "aabbcc")' || true
	./$(EXE) || true
	./$(EXE) rules6.7 notavailable || true
	./$(EXE) notavailable rules6.7 || true
	gcc -fprofile-arcs -o $(EXE) $(OBJS) badmalloc.o
	./$(EXE) rules.txt init.txt 0 || true
	./$(EXE) rules.txt init.txt 1 || true
	./$(EXE) rules.txt init.txt 2 || true
	./$(EXE) rules.txt init.txt 3 || true
	bash -c './$(EXE) gobackwardsrules.txt <(echo "--") 2' || true

coverage: run-all
	gcov -f main.o tape.o

include Makefile.stdrules
