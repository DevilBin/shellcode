/*************************************************************************
	> File Name: main.c
	> Author: DevilBin 
	> Mail: whu.evil.binary@gmail.com 
	> Created Time: Sat 24 Oct 2015 12:39:23 PM CST
 ************************************************************************/

#include <stdio.h> 
#include <stdlib.h>

int main() {
    char *name[2];
    name[0] = "/usr/bin/python";
    name[1] = NULL;
    execve(name[0], name, NULL);
    return 0;
}
