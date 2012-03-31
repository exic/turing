CXX = gcc
CXXFLAGS = -g -Wall # -fprofile-arcs -ftest-coverage

AR = ar
ARFLAGS =
RANLIB = ranlib

OBJS = $(patsubst %.c, %.o, $(wildcard *.c))

# vim: set filetype=make : #
