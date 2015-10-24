all:	main.c exitfunc.c shellcode.c shellcode.s
	@gcc -g -m32 -z execstack -fno-stack-protector main.c -o main
	@gcc -g -m32 -z execstack -fno-stack-protector exitfunc.c -o exitfunc
	@gcc -g -m32 -z execstack -fno-stack-protector shellcode.c -o shellcode
	@gcc -g -m32 shellcode.s -o shellcodes

main: main.c
	@gcc -g -m32 -z execstack -fno-stack-protector main.c -o main

exit: exitfunc.c
	@gcc -g -m32 -z execstack -fno-stack-protector exitfunc.c -o exitfunc

shellcode: shellcode.c
	@gcc -g -m32 -z execstack -fno-stack-protector shellcode.c -o shellcode

shellcodes: shellcode.s
	@gcc -g -m32 shellcode.s -o shellcodes

clean:
	@rm -rf main exitfunc shellcode shellcodes
