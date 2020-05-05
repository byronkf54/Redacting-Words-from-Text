#include <stdio.h>
#include <stdlib.h>

// character pointer array stores words to redact
char *words[8];


// ALTERNATIVE to strlen method
int string_length(const char *str) {
    int n = 0;
    while (str[n] != '\0') {
        n++;
    }
    return n;
}


// ALTERNATIVE to strcpy method
char *copy_string(char *destination, char *source)
{
    char *start = destination;

    while(*source != '\0') {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0';
    return start;
}


// ALTERNATIVE to tolower method
char to_lower_case(char c) {
    //'A' <= c <= 'Z'
    if(c >= 'A' && c <= 'Z')
    {
        c = c + 32;
    }
    return c;
}


// replaces word with asterisks
void remove_word(char* word) {
    for (int i = 0; i < string_length(word); i++) {
        printf("*");
    }
}


// function to scan word and check if in words to redact
int check_string(char* word) {
    int x = 0;

    // loop through first letter of word passed in against first letter of each word in WORDS
    for (int i = 0; i < sizeof(words)/8; i++) {
        char c = to_lower_case(word[0]);
        while (c == to_lower_case(words[i][x])) {
            x++;
            c = to_lower_case(word[x]);
            if (x == string_length(words[i])-1) {
                return 1;
            }
        }
        x = 0;
    }
    return 0;
}


// procedure reads body of text from file and checks it against words to redact
void read_strings_from_file() {

    char *fileline = "./debate.txt";
    FILE *fp = fopen(fileline, "r");

    // checks if file exists
    if (!fp) {
        printf("\nCan't open file\n");
        return;
    }
    char *word = "";
    char c;
    while (!feof(fp)) {
        c = fgetc(fp);
        char *str2 = NULL;
        // checks if character is a space or end of line
        if (c < 65 && string_length(word) > 0) {
            if (check_string(word)) {
                remove_word(word);
            }
            else {
                printf("%s", word);
            }
            printf("%c", c);
            word = "";
            free(str2);
        }
        // add character to string
        else {
            int len = 0;
            if (string_length(word) > 0) {
                len = string_length(word);
            }
            str2 = malloc(len + 2);
            copy_string(str2, word);
            str2[len] = c;
            str2[len + 1] = '\0';
            word = str2;
        }
    }
    fclose(fp);
}


// procedure reads words to redact from file and stores them in character pointer array
void read_words_from_file() {
    char *fileline = "./redact.txt";
    FILE *fp = fopen(fileline, "r");

    // checks if file exists
    if (!fp) {
        printf("\nCan't open file\n");
        return;
    }
    // reads contents of file until end of file
    char* word = "";
    char c;
    int i = 0;
    while (!feof(fp)) {
        c = fgetc(fp);
        char *str2 = NULL;
        // checks if character is a space or end of line
        if (c == '\n' || c == '\0' || c == ' ' || (int) c < 0) {
            words[i] = word;
            i++;
            word = "";
            free(str2);
        }
            // add character to string
        else {
            int len = 0;
            if (string_length(word) > 0) {
                len = string_length(word);
            }
            str2 = malloc(len + 2);
            copy_string(str2, word);
            str2[len] = c;
            str2[len + 1] = '\0';
            word = str2;
        }
    }
    fclose(fp);
}


int main() {
    read_words_from_file();
    read_strings_from_file();
    return 0;
}
