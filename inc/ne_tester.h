#ifndef NE_TESTER_H
#define NE_TESTER_H 

#include <stddef.h> 
#include <stdio.h> 

typedef struct __NETester NETester;

typedef int (*NETester_Test)(NETester *);

struct __NETester {
    NETester_Test *tests;
};

/* A macro that makes printing the progress easy. */
#define NETester_progPrint(result,file) \
if (result) { \
    fprintf(file,"."); \
} else { \
    fprintf(file,"!"); \
}


static inline int NETester_doTests(NETester *t)
{
    int result = 1, numPassed = 0, numFailed = 0, numTestsRan = 0;
    NETester_Test *test = t->tests;
    while (*test) {
        numTestsRan++;
        if ((result = (result && (*test)(t)))) {
            printf("P"); numPassed++;
        } else {
            printf("F"); numFailed++;
        }
        printf("\n");
        test++;
    }
    printf("Number of tests run: %d\n\tPassed: %d\n\tFailed: %d\n",
            numTestsRan, numPassed, numFailed);
    return result;
}

#endif /* NE_TESTER_H */
