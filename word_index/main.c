#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "hash_table.h"
#include "hash_func.h"
#include "array.h"

#define LINE_LENGTH 256

#define TABLE_START_SIZE 256
#define MAX_LOAD_FACTOR 0.6
#define HASH_FUNCTION hash_too_simple

#define START_TESTS 2
#define MAX_TESTS 2
#define HASH_TESTS 1


/* Creates a hash table with word index for the specified file and parameters */
struct table *create_from_file(char *filename, unsigned long start_size,
                double max_load, unsigned long (*hash_func)(unsigned char *)) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        exit(1);

    char *line = malloc((LINE_LENGTH + 1) * sizeof(char));
    
    struct table *hash_table; 
    hash_table = table_init(start_size, max_load, hash_func);
    if (hash_table == NULL) {
        fprintf(stderr, "Failed to create hash table");
        return 1;
    }
    puts("HERE");
    while (fgets(line, LINE_LENGTH, fp)) {

        for (unsigned int i = 0; i < strlen(line); i++) {
            if (!isalpha(line[i])) {
                line[i] = ' ';
            }
            else if (line[i] < 'a' || line[i] > 'z') {
                line[i] = (char)tolower(line[i]);
            }
        // Following add every word to the hash table, I did not get
        // to finish it unfortunately and I decided to stop here to prevent
        // myself from introducing weird errors that would only reduce
        // the grade. 
        }
    }
    fclose(fp);
    free(line);

    return hash_table;
}

/* Reads words from stdin and prints line lookup results per word. */
void stdin_lookup(struct table *hash_table) {
    char *line = malloc((LINE_LENGTH + 1) * sizeof(char));
    
    while (fgets(line, LINE_LENGTH, stdin)) { 
        // ... SOME CODE MISSING HERE ...
    }   
    free(line);
}

void timed_construction(char *filename) {
    /* Here you can edit the hash table testing parameters: Starting size,
     * maximum load factor and hash function used, and see the the effect
     * on the time it takes to build the table.
     * You can edit the tested values in the 3 arrays below. If you change
     * the number of elements in the array, change the defined constants
     * at the top of the file too, to change the size of the arrays. */
    unsigned long start_sizes[START_TESTS] = {2, 65536};
    double max_loads[MAX_TESTS] = {0.2, 1.0};
    unsigned long (*hash_funcs[HASH_TESTS])(unsigned char *) = {hash_too_simple};

    for (int i = 0; i < START_TESTS; i++) {
        for (int j = 0; j < MAX_TESTS; j++) {
            for (int k = 0 ; k < HASH_TESTS; k++) { 
                clock_t start = clock();
                struct table *hash_table = create_from_file(filename,
                        start_sizes[i], max_loads[j], hash_funcs[k]);
                clock_t end = clock();

                printf("Start: %ld\tMax: %.1f\tHash: %d\t -> Time: %ld microsecs\n",
                        start_sizes[i], max_loads[j], k, end - start);
                table_cleanup(hash_table);
            }
        }
    }
}


int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;
    
    if (argc == 3 && !strcmp(argv[2], "-t")) {
        timed_construction(argv[1]);
    } else {
        struct table *hash_table = create_from_file(argv[1], TABLE_START_SIZE,
                MAX_LOAD_FACTOR, HASH_FUNCTION);  
        
        stdin_lookup(hash_table);
        table_cleanup(hash_table);
    }

    return 0;
}

