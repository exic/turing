#ifndef _TAPE
#define _TAPE

#define TAPELEN 5
#define TAPEMAXINDEX (TAPELEN-1)

struct tape {
    struct tape *prev;
    char* t;
    int current_index;
    struct tape *next;
};

void init(struct tape *tape);
void print(struct tape *tape);

char read_char(struct tape *tape);
void move(struct tape *tape, char direction);
void write_char(struct tape *tape, char c);

int get_position_index(struct tape *tape);

#endif
