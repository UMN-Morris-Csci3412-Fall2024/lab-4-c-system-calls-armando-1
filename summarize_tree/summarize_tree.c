#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <limits.h>  

static int num_dirs = 0;
static int num_regular = 0;

bool is_dir(const char *path) {
  
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        fprintf(stderr, "Error accessing %s: %s\n", path, strerror(errno));
        return false;
    }
    return S_ISDIR(path_stat.st_mode);

      /*
   * Use the stat() function (try "man 2 stat") to determine if the file
   * referenced by path is a directory or not.  Call stat, and then use
   * S_ISDIR to see if the file is a directory. Make sure you check the
   * return value from stat() in case there is a problem, e.g., maybe the
   * the file doesn't actually exist.
   */
}
/* 
 * I needed this because the multiple recursion means there's no way to
 * order them so that the definitions all precede the cause.
 */

void process_path(const char *path);

void process_directory(const char *path) {
   
    DIR *dir = opendir(path);
    if (!dir) {
        fprintf(stderr, "Could not open directory %s: %s\n", path, strerror(errno));
        return;
    }

    num_dirs++;  

    for (struct dirent *entry = readdir(dir); entry != NULL; entry = readdir(dir)) {

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        process_path(full_path);
        
    }

    closedir(dir);  
}
  /*
   * Update the number of directories seen, use opendir() to open the
   * directory, and then use readdir() to loop through the entries
   * and process them. You have to be careful not to process the
   * "." and ".." directory entries, or you'll end up spinning in
   * (infinite) loops. Also make sure you closedir() when you're done.
   *
   * You'll also want to use chdir() to move into this new directory,
   * with a matching call to chdir() to move back out of it when you're
   * done.
   */


void process_file(const char *path) {
    num_regular++;

   /*
   * Update the number of regular files.
   * This is as simple as it seems. :-)
   */   
}

void process_path(const char *path) {

    if (is_dir(path)) {
        process_directory(path);
    } else {
        process_file(path);
    }
}

int main(int argc, char *argv[]) {
 // Ensure an argument was provided.
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        fprintf(stderr, "       where <path> is the file or root of the tree you want to summarize.\n");
        return 1;
    }

    num_dirs = 0;
    num_regular = 0;

    process_path(argv[1]);

    printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_regular);

    return 0;
}

