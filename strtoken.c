#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  Function to split a string into an array of words*/
char** splitString(const char* input, const char* delimiters, int* wordCount) 
{
    /*  Count the number of words in the string*/
    *wordCount = 0;
    const char* current = input;
    if (*current != '\0') {
        /*  Skip leading delimiters*/
        while (*current != '\0' && strchr(delimiters, *current) != NULL) 
        {
            current++;
        }
        /* Count the word*/
        if (*current != '\0') 
        {
            (*wordCount)++;
            /*  Skip the word*/
            while (*current != '\0' && strchr(delimiters, *current) == NULL) 
            {
                current++;
            }
        }
    }

    /*  Allocate memory for the array of words*/
    char** words = (char**)malloc(*wordCount * sizeof(char*));
    if (words == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    /*  Copy each word into the array*/
    current = input;
    int wordIndex = 0;
    if (*current != '\0') {
        /* Skip leading delimiters */
        while (*current != '\0' && strchr(delimiters, *current) != NULL) {
            current++;
        }
        /* Copy the word*/ 
        if (*current != '\0') {
            const char* start = current;
            /*  Find the end of the word*/
            while (*current != '\0' && strchr(delimiters, *current) == NULL) {
                current++;
            }
            /*  Calculate the length of the word */
            size_t wordLength = current - start;
            /*  Allocate memory for the word*/
            words[wordIndex] = (char*)malloc((wordLength + 1) * sizeof(char));
            if (words[wordIndex] == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }
            /*  Copy the word*/
            strncpy(words[wordIndex], start, wordLength);
            words[wordIndex][wordLength] = '\0'; /*  Null-terminate the word*/
            wordIndex++;
        }
    }

    return words;
}

/* Function to free memory allocated for words array */
void freeWords(char** words, int wordCount) {
    for (int i = 0; i < wordCount; i++) {
        free(words[i]);
    }
    free(words);
}

int main() {
    const char* inputString = "Ntuthuko Dhlamini";
    const char* delimiters = " ,.!";

    int wordCount;
    char** wordArray = splitString(inputString, delimiters, &wordCount);

    printf("Number of words: %d\n", wordCount);
    for (int i = 0; i < wordCount; i++) {
        printf("Word %d: %s\n", i + 1, wordArray[i]);
    }

    /* Free allocated memory */
    freeWords(wordArray, wordCount);

    return 0;
}

