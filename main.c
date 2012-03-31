#include <stdio.h>
#include <stdlib.h>

#include "tape.h"

#define RULESBUFFER 15
#define RULESINPUTBUFFER 12
#define INITINPUTBUFFER 2

void storeRule(char* line, int counter);
int followRule(char* inout);
void readRules(char* file);
void readInit(char* file);

char rules[RULESBUFFER][5];
int rulescount = 0;
char status = 'A';
struct tape *tape;

int isEndStatus(status) {
    if (status == 'F') {
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("USAGE: Turing.exe <RULES> <INIT>");
        return 1;
    }

    tape = (struct tape *) malloc(sizeof (struct tape));
    init(tape);

    readRules(argv[1]);
    readInit(argv[2]);

    print(tape);

    char rule[] = {"000"};

    int step = 0;
    while (1) {
        printf("Step %i\n", step++);
        rule[0] = status;
        rule[1] = read_char(tape);

        if (! followRule(rule)) {
            printf("No rule found to follow!");
            return 1;
        }

//        printf("\n");
//        printf("%c, %c, %c\n", rule[0], rule[1], rule[2]);

        write_char(tape, rule[0]);
        status = rule[1];
        printf("move: %c\n", rule[2]);
        move(tape, rule[2]);
        printf("pointer position: %i\n", get_position_index(tape));

        print(tape);
        if (isEndStatus(status)) {
            break;
        }
    }

    return 0;
}

void readRules(char* file) {
    FILE* f;
    char text[RULESINPUTBUFFER];
    int counter;

    f = fopen(file, "r");
    if (f == NULL) {
        printf("Rules INPUT failure (\"%s\")\n", file);
        return;
    } else {
        printf("Rules INPUT success (\"%s\")\n", file);
    }

    counter = 0;
    while (fgets(text, sizeof(text), f) != 0) {
        storeRule(text, counter++);
    }
    rulescount = counter;
}

void readInit(char* file) {
    FILE* f;
    char text[INITINPUTBUFFER];

    f = fopen(file, "r");
    if (f == NULL) {
        printf("Init INPUT failure (\"%s\")\n", file);
        return;
    } else {
        printf("Init INPUT success (\"%s\")\n", file);
    }

    int counter = 0;
    while (fgets(text, sizeof(text), f) != 0) {
        printf("got char: \"%c\"\n", text[0]);
        if (text[0] == '\n' || text[0] == '\r') {
            continue;
        }
        write_char(tape, text[0]);
        move(tape, '>');
        counter++;
    }
    int i;
    for (i = 0; i < counter; i++) {
        move(tape, '<');
    }
}

void storeRule(char* line, int counter) {
    rules[counter][0] = line[0];
    rules[counter][1] = line[2];
    rules[counter][2] = line[4];
    rules[counter][3] = line[6];
    rules[counter][4] = line[8];
}

int followRule(char* inout) {
    int i;
    for (i = 0; i < rulescount; i++) {
        if (rules[i][0] == inout[0] && rules[i][1] == inout[1]) {
            inout[0] = rules[i][2];
            inout[1] = rules[i][3];
            inout[2] = rules[i][4];
            return 1;
        }
    }
    return 0;
}

