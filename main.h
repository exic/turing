#ifndef _MAIN
#define _MAIN

#define RULESBUFFER 100
#define RULESINPUTBUFFER 12
#define INITINPUTBUFFER 2

void storeRule(char* line, int counter);
int followRule(char* inout);
void readRules(char* file);
void readInit(char* file);
int findFinalState();

void nomemoryaction();

#endif
