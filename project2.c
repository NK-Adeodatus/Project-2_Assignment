#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 40

// ===============================
// Required Structure
// ===============================
typedef struct {
    char name[MAX_WORD_LEN];
    int count;
} wordStat;


// ===============================
// Function Prototypes
// ===============================
void count_words(char **words, int word_count);
void longest_word(char **words, int word_count);
void most_frequent(wordStat *stats, int stat_count);
void average_word_length(char **words, int word_count); // custom analysis


// ===============================
// MAIN PROGRAM
// ===============================
int main() {

    char *text = NULL;
    size_t size = 0;

    printf("Enter a paragraph:\n");

    // dynamic input
    getline(&text, &size, stdin);

    printf("\nText stored at memory address: %p\n", (void*)text);


    // ===============================
    // Split text into words
    // ===============================

    char **words = NULL;
    int word_count = 0;

    char *token = strtok(text, " ,.!?\n");

    while (token != NULL) {

        words = realloc(words, (word_count + 1) * sizeof(char*));

        words[word_count] = malloc(strlen(token) + 1);

        strcpy(words[word_count], token);

        word_count++;

        token = strtok(NULL, " ,.!?\n");
    }

    printf("Word array stored at memory address: %p\n", (void*)words);



    // ===============================
    // Build Word Statistics
    // ===============================

    wordStat *stats = NULL;
    int stat_count = 0;

    for (int i = 0; i < word_count; i++) {

        int found = 0;

        for (int j = 0; j < stat_count; j++) {

            if (strcmp(words[i], stats[j].name) == 0) {

                stats[j].count++;
                found = 1;
                break;

            }
        }

        if (!found) {

            stats = realloc(stats, (stat_count + 1) * sizeof(wordStat));

            strcpy(stats[stat_count].name, words[i]);
            stats[stat_count].count = 1;

            stat_count++;
        }
    }

    printf("Word statistics stored at memory address: %p\n", (void*)stats);



    // ===============================
    // Function Pointer Table
    // ===============================

    void (*analysis_functions[4])();

    analysis_functions[0] = (void (*)())count_words;
    analysis_functions[1] = (void (*)())longest_word;
    analysis_functions[2] = (void (*)())most_frequent;
    analysis_functions[3] = (void (*)())average_word_length;



    // ===============================
    // Run Analyses
    // ===============================

    printf("\n--- Analysis Results ---\n");

    analysis_functions[0](words, word_count);
    analysis_functions[1](words, word_count);
    analysis_functions[2](stats, stat_count);
    analysis_functions[3](words, word_count);



    // ===============================
    // Free Memory
    // ===============================

    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }

    free(words);
    free(stats);
    free(text);

    return 0;
}



// ===============================
// Count Words
// ===============================
void count_words(char **words, int word_count) {

    printf("Total number of words: %d\n", word_count);

}



// ===============================
// Longest Word
// ===============================
void longest_word(char **words, int word_count) {

    char *longest = words[0];

    for (int i = 1; i < word_count; i++) {

        if (strlen(words[i]) > strlen(longest)) {
            longest = words[i];
        }

    }

    printf("Longest word: %s\n", longest);

}



// ===============================
// Most Frequent Word
// ===============================
void most_frequent(wordStat *stats, int stat_count) {

    wordStat *max = &stats[0];

    for (int i = 1; i < stat_count; i++) {

        if (stats[i].count > max->count) {
            max = &stats[i];
        }

    }

    printf("Most frequent word: %s (%d times)\n", max->name, max->count);

}



// ===============================
// Custom Analysis: Average Word Length
// ===============================
void average_word_length(char **words, int word_count) {

    int total = 0;

    for (int i = 0; i < word_count; i++) {

        total += strlen(words[i]);

    }

    printf("Average word length: %.2f\n", (float)total / word_count);

}