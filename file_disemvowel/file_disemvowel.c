#include <stdio.h>     
#include <stdbool.h>   
#include <ctype.h>     

#define BUF_SIZE 1024  
//this function will check the characters with vowels
bool is_vowel(char c) {
    c = tolower(c);  // it will convers characters into lower to do comparison
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}
// this function will copy non vowel characters in_buf & out_buf
// the returns numbers of non vwoel charcters that been copeid
int copy_non_vowels(int num_chars, char *in_buf, char *out_buf) {
    int i = 0;// the input 
    int out_index = 0;// the output 
//this is a loop that will loop each character 
//in the input 
    while (i < num_chars) {// if its not a vowel we copy it to output 
        if (!is_vowel(in_buf[i])) {
            out_buf[out_index++] = in_buf[i];
        }
        i++;
    }// this moves to the next character of input

    return out_index; // this returns the number of non vowels that have been copied 
}
// the function reads the files output and input
void disemvowel(FILE *inputFile, FILE *outputFile) {
    char in_buf[BUF_SIZE], out_buf[BUF_SIZE];// the function reads the files output and input
    size_t chars_read;
    //the number of charcters in input
    //reading from the input file until completed
    while ((chars_read = fread(in_buf, 1, BUF_SIZE, inputFile)) > 0) {
        int non_vowels = copy_non_vowels(chars_read, in_buf, out_buf);
        //copies nonvowels from input buff through output buff
        size_t written = 0;
        while (written < non_vowels) {
            written += fwrite(out_buf + written, 1, non_vowels - written, outputFile);
            // will compine leftover characters to the output file
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *inputFile = stdin;   
    FILE *outputFile = stdout; 
    // once input file is give it reads it
    if (argc > 1) {
        inputFile = fopen(argv[1], "r");  // will open input file 
        if (inputFile == NULL) {
            perror("fail");   //if it doesn't open proberly then it fails 
            return 1;
        }
    }//once output file is given it reads it
    if (argc > 2) {
        outputFile = fopen(argv[2], "w");  
        if (outputFile == NULL) {
            perror("fail");  
            fclose(inputFile);  //will close the input before exiting
            return 1;
        }
    }
    disemvowel(inputFile, outputFile);
    // Code that processes the command line arguments
    // and sets up inputFile and outputFile.
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
