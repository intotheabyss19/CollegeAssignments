/*
14. Input any word up to 10 alphabets and display the number of different alphabets appearing in the 
word e.g. McGraw-Hill (Input), a = 1, c = 1, g = 1, h = 1, i = 1, l = 2, m = 1, r = 1, w = 1 (Output) 
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int childP(int fd[]) {
    char str[11];
    printf("Enter a word: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0;

    int count[26] = {0};
    for(int i = 0; i < strlen(str); i++) {
        char c = tolower(str[i]);
        if(c >= 'a' && c <= 'z')
            count[c - 'a']++;
    }

    write(fd[1], count, sizeof(count));
    close(fd[1]);
}

int parentP(int fd[]) {
    int count[26];
    close(fd[1]);

    read(fd[0], count, sizeof(count));

    for(int i = 0; i < 26; i++)
        if(count[i] > 0)
            printf("%c = %d\n", i + 'a', count[i]);

    close(fd[0]);
}

int main() {
    int i, n, fd[2];
    pid_t pid;

    pipe(fd);

    if((pid = fork()) == -1) {
        perror("fork");
        exit(1);
    }
    else if(pid == 0)
        childP(fd);
    else
        parentP(fd);

    return 0;
}