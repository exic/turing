#include <stdio.h>

#include "tape.h"

int main() {
    struct tape *tape = (struct tape *) malloc(sizeof (struct tape));
    init(tape);
    write_char(tape, '1');
    print(tape);

    int i;
    for (i = 0; i < 5; i++) {
        move(tape, '>');
        print(tape);
    }
    write_char(tape, '2');
    print(tape);
    for (i = 0; i < 5; i++) {
        move(tape, '>');
        print(tape);
    }
    write_char(tape, '3');
    print(tape);
    move(tape, '>');
    print(tape);
    printf("############## now going backwards\n");
    for (i = 0; i < 7; i++) {
        move(tape, '<');
        print(tape);
    }
    move(tape, '>');
    move(tape, '>');
    write_char(tape, 'x');
    print(tape);
    move(tape, '<');
    move(tape, '<');
    write_char(tape, 'y');
    move(tape, '<');
    move(tape, '<');
    print(tape);
    move(tape, '<');
    move(tape, '<');
    print(tape);

    return 0;
}
