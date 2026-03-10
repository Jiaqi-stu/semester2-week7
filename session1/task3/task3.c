/* Task 3: assertions and conditional logging */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "logging.h"


int* get_values(int argc, char* argv[])
{
    LOG_FMT("get_values(): argc=%d\n", argc);

    int value;
    int* values = NULL;

    if (argc > 1) {
        values = calloc(argc - 1, sizeof(int));
        for (int i = 0; i < argc - 1; ++i) {
            value = atoi(argv[i + 1]);
            LOG_FMT("get_values(): arg \"%s\" -> %d\n", argv[i + 1], value);
            values[i] = value;
        }    
    }

    LOG_FMT("get_values(): returning %p\n", values);

    return values;
}


long sum_values(int data[], int n)
{
    assert(data != NULL);
    assert(n > 0);

    long result = 0L;

    for (int i = 0; i < n; ++i) {
        result += data[i];
        LOG_FMT("sum_values(): i=%d, sum=%ld\n", i, result);
    }

    return result;
}


int main(int argc, char* argv[])
{
    int* data = NULL;
    int num_values = 0;

    data = get_values(argc, argv);
    //num_values = argc - 1;

    LOG_FMT("main(): data at %p\n", data);
    LOG_FMT("main(): num_values=%d\n", num_values);

    long sum = sum_values(data, num_values);

    LOG_MSG("main(): calculation complete\n");

    free(data);

    LOG_MSG("main(): freed allocated storage\n");

    printf("Sum of values = %ld\n", sum);

    return 0;
}
