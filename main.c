#include <stdio.h>
#include <stdlib.h>

#include "tape.h"

#define RULESBUFFER 100
#define RULESINPUTBUFFER 12
#define INITINPUTBUFFER 2

void storeRule(char* line, int counter);
int followRule(char* inout);
void readRules(char* file);
void readInit(char* file);
int findFinalState();

char rules[RULESBUFFER][5];
int rulescount = 0;
char status;
char finalstatus;
struct tape *tape;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("USAGE: Turing.exe <RULES> <INIT>");
        return 1;
    }

    tape = (struct tape *) malloc(sizeof (struct tape));
    if (!tape) {
        printf("Oh gawd, no memarey?!");
        exit(1);
    }
    init(tape);
    readRules(argv[1]);
    readInit(argv[2]);
    finalstatus = (char)findFinalState();

    // Start status is status of first line
    status = rules[0][0];

    int step = 0;
    printf("\n######### Step %i #########\n\n", step++);
    print(tape);

    char rule[] = {"000"};

    while (status != finalstatus) {
        printf("\n######### Step %i #########\n\n", step++);

        rule[0] = status;
        rule[1] = read_char(tape);

        if (! followRule(rule)) {
            printf("No rule found to follow!");
            return 1;
        }

        write_char(tape, rule[0]);
        status = rule[1];
        move(tape, rule[2]);

        print(tape);
    }

    printf("\nReached end status :-)\n");

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

int findFinalState() {
    int i, j;
    int array1[26];
    int array2[26];
    int position1 = 0;
    int position2 = 0;

    for (i = 0; i < 26; i++) {
        array1[i] = 0;
        array2[i] = 0;
    }

    for (i = 0; i < rulescount; i++) {
        for (j = 0; j < 26; j++){
            if (array1[j] == rules[i][3]) {
                break;
            } else if (array1[j] == 0) {
                array1[position1] = rules[i][3];
                position1++;
                break;
            }
        }
    }

    for (i = 0; i < rulescount; i++) {
        for (j = 0; j < 26; j++){
            if (array2[j] == rules[i][0]) {
                break;
            } else if (array2[j] == 0) {
                array2[position2] = rules[i][0];
                position2++;
                break;
            }
        }
    }

    for (j = 0; j < 26; j++) {
        for (i = 0; i < 26; i++) {
            if (array1[j] == array2[i])
                break;
            if (i == 25)
                return array1[j];
        }
    }

    return 0;
}

