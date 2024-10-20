#include <stdio.h>     
#include <stdbool.h>   
#include <ctype.h>     

#define BUF_SIZE 1024  


bool is_vowel(char c) {
    c = tolower(c);  
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int copy_non_vowels(int num_chars, char *in_buf, char *out_buf) {
    int i = 0;
    int out_index = 0;

    while (i < num_chars) {
        if (!is_vowel(in_buf[i])) {
            out_buf[out_index++] = in_buf[i];
        }
        i++;
    }

    return out_index; 
}

void disemvowel(FILE *inputFile, FILE *outputFile) {
    char in_buf[BUF_SIZE], out_buf[BUF_SIZE];
    size_t chars_read;

   
    while ((chars_read = fread(in_buf, 1, BUF_SIZE, inputFile)) > 0) {
        int non_vowels = copy_non_vowels(chars_read, in_buf, out_buf);

        size_t written = 0;
        while (written < non_vowels) {
            written += fwrite(out_buf + written, 1, non_vowels - written, outputFile);
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *inputFile = stdin;   
    FILE *outputFile = stdout; 

    if (argc > 1) {
        inputFile = fopen(argv[1], "r");  
        if (inputFile == NULL) {
            perror("Error opening input file");  
            return 1;
        }
    }
    if (argc > 2) {
        outputFile = fopen(argv[2], "w");  
        if (outputFile == NULL) {
            perror("Error opening output file");  
            fclose(inputFile);  
            return 1;
        }
    }
    disemvowel(inputFile, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
