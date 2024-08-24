#include <sodium/randombytes.h>
#include <stdio.h>
#include <string.h>
#include <sodium.h>
#include <ctype.h> //To Upper


long count_lines(FILE *File) { 
    char c;
    long line_counter = 0;
    while ((c = getc(File)) != EOF) {
        if (c == '\n') {
            line_counter++;
        }
    }
    return(line_counter);
}

void randomize_case(char *a) { // Accepts a string as input
    for (int i = 0; i < strlen(a); i++) {
        int coin = randombytes_uniform(2); // Decide if the current character will be capitalized or lowercase
        if (coin == 1) {
            a[i] = toupper(a[i]);
        }
    }
}

void generate_integers(void) {
    int length = 5; // TO-DO: Make random eventually
    for (int i=0; i<length; i++) {
        int random = randombytes_uniform(length);
        printf("%d", random);
    }
}

void generate_characters(char *set) {
    for (int i = 0; i < 5; i++) {
        int random_character = randombytes_uniform(strlen(set));
        printf("%c", set[random_character]);
    }
}

int main (int argc, char **argv) {
    char c, arg, str[20];
    FILE *words;
    long line_counter, line_total, r;

    char character_set[28] = "!@#$%^&*()_-+={}[]|~`<,>.?:;";
    char letter_set[26] = "abcdefghijklmnopqrstuvwxyz";

    if (sodium_init() < 0) return 1;    
    words = fopen("word_list.txt", "r");

    line_total = count_lines(words);
    fseek(words, 0, SEEK_SET); // Reset pointer to beginning of file

    char temp[2]; // Cannot copy c directly to str. needs a buffer
    temp[1] = '\0'; // Makes the array a string

    r = randombytes_uniform(line_total + 1); // Generates random line number to use for string
                                             
    while ((c = getc(words)) != EOF) {
        int i;
        temp[0] = c;
        if ((r == i) && (c != '\n')) { 
            strcat(str, temp); 
        }
        if (c == '\n') {
            i++;        }
    }

    randomize_case(str);
    generate_integers();
    printf("%s", str);
    generate_characters(character_set);

    printf("\n");
    fseek(words, 0, SEEK_SET); // Reset pointer to beginning of file //
    fclose(words);
}

