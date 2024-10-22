#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <sys/stat.h>


static int num_dirs = 0;
static int num_regular = 0;

static int callback(const char *fpath, const struct stat *sb, int typeflag) {

    int flags[2] = {FTW_D, FTW_F};         
    int *counters[2] = {&num_dirs, &num_regular};  
    // will loop over the two possible of dictory & file
    for (int i = 0; i < 2; i++) {
        if (typeflag == flags[i]) {
            (*counters[i])++;  //if the type matches then increment it
            break;  
        }
    }

    return 0;  
}

#define MAX_FTW_DEPTH 16

int main(int argc, char **argv) {
    for (int i = 0; i < 1; i++) {
        // checks if there is one argument
        if (argc != 2) {
            fprintf(stderr, "Usage: %s <path>\n", argv[0]);
            fprintf(stderr, "       where <path> is the file or root of the tree you want to summarize.\n");
            return 1;
            //will exit the argument
        }

        // will check if the directory fails or not
        if (ftw(argv[1], callback, MAX_FTW_DEPTH) != 0) {
            return 1;
        }
    }

    printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_regular);

    return 0;
}
