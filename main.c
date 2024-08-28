#include <sodium/randombytes.h>
#include <stdio.h>
#include <string.h>
#include <sodium.h>
#include <unistd.h>
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
    int random_length;
    // while (random_length <= 3) random_length 
    for (int i = 0; i < 5; i++) {
        int random_character = randombytes_uniform(strlen(set));
        printf("%c", set[random_character]);
    }
}

int main (int argc, char **argv) {
    char a, arg, str[20];
    long line_counter, line_total, r;
    FILE *words;

    int index;
    int w_flag = 0; 
    int c;
    opterr = 0;

    char character_set[28] = "!@#$%^&*()_-+={}[]|~`<,>.?:;";
    char letter_set[26] = "abcdefghijklmnopqrstuvwxyz";

    while ((c = getopt (argc, argv, "wh")) != -1)
        switch(c) {
            case 'w':
                w_flag = 1;
                break;
            case 'h':
                printf("usage: spwdg [options]\n"
                        "-h                 shows this help text\n"
                        "-w                 generates passwords using words\n");
                return 0;
            case '?':
                if (optopt == 'c')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option '-%c'.\n", optopt);
                else
                    fprintf(stderr,"Unknown option character '\\x%x'.\n", optopt);
                return 1;
            default:
                abort();

        }

    if (sodium_init() < 0) return 1;    
    words = fopen("word_list.txt", "r");

    line_total = count_lines(words);
    fseek(words, 0, SEEK_SET); // Reset pointer to beginning of file

    char temp[2]; // Cannot copy c directly to str. needs a buffer
    temp[1] = '\0'; // Makes the array a string

    r = randombytes_uniform(line_total + 1); // Generates random line number to use for string

    while ((a = getc(words)) != EOF) {
        int i;
        temp[0] = a;
        if ((r == i) && (a != '\n')) { 
            strcat(str, temp); 
        }
        if (a == '\n') {
            i++;        }
    }

    randomize_case(str);
    generate_integers();
    if (w_flag == 1) {
        printf("%s", str);
    }
    else  {
        generate_characters(letter_set);
    }
    generate_characters(character_set);
    printf("\n");
    fclose(words);
}

