#include "tape.h"
#include <stdio.h>
#include <stdlib.h>

void init(struct tape *tape) {
    tape->prev = NULL;
    tape->next = NULL;

    tape->current_index = 0;
    tape->t = (char *) malloc((TAPELEN+1) * sizeof (char));; // TODO: +1 for NULL termination - correct?
    int i;
    for (i = 0; i < TAPELEN; i++) {
        tape->t[i] = '-';
    }
    tape->t[TAPELEN] = '\0';
};

int get_position_index(struct tape *current) {
    int position = 0;
    while (current->prev) {
        current = current->prev;
    }
    while (current->current_index == -1) {
        current = current->next;
        position += TAPELEN;
    }
    position += current->current_index;
    return position;
}

void print(struct tape *tape) {
    struct tape *current;
    current = tape;
    while (current->prev) {
        current = current->prev;
    }

    printf("tape:     ");

    printf("%s", current->t);
    while (current->next) {
        current = current->next;
        printf("%s", current->t);
    }
    printf("\n");

    printf("position: ");
    int i;
    for (i = 0; i < get_position_index(tape); i++) {
        printf(" ");
    }
    printf("|\n");
}

struct tape* get_active_block(struct tape *tape) {
    struct tape *current = tape;
    while (current->prev) {
        current = current->prev;
    }
    while (current->current_index == -1) {
        current = current->next;
    }
    return current;
}

char read_char(struct tape *tape) {
    struct tape *current = get_active_block(tape);
    return current->t[current->current_index];
}

void write_char(struct tape *tape, char c) {
    struct tape *current = get_active_block(tape);
    current->t[current->current_index] = c;
}

void move(struct tape *tape, char c) {
    struct tape *current = get_active_block(tape);
//    printf("current index: %i ", current->current_index);
    if (c == '>') {
        if (current->current_index == TAPEMAXINDEX) {
            if (!current->next) {
                current->current_index = -1;
                struct tape *extension = (struct tape *) malloc(sizeof (struct tape));
                init(extension);
                extension->prev = current;
                current->next = extension;
            } else {
                current = current->next;
                current->current_index = 0;
            }
        } else {
            current->current_index += 1;
        }
    } else if (c == '<') {
        if (current->current_index == 0) {
            if (!current->prev) {
                struct tape *extension = (struct tape *) malloc(sizeof (struct tape));
                init(extension);
                current->prev = extension;
                extension->next = current;
                extension->current_index = TAPEMAXINDEX;
            } else {
//                printf("doingit\n");
                current->current_index = -1;
                current->prev->current_index = TAPEMAXINDEX;
            }
        } else {
//            printf("reducing by 1\n");
            current->current_index -= 1;
        }
    }
}
