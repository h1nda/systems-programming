#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {

    if (mkdir("directory1", 0777) == -1) {
        perror("error creating directory");
    }

    if (chdir("directory1") == -1) {
        perror("error changing directiorn");
    }
 
    symlink("nonexitent.txt", "link.txt");
    unlink("link.txt");

    if (chdir("..") == -1) {
        perror("error changing directory to parent");
    }

    if (rmdir("directory1") == -1) {
        perror("error removing directiorn");
    }



    return 0;
}