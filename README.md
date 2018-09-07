# Example of what volatile does in C

In the get_volatile() function volatile_gv is read twice.
But in gfgv the gv is never even read because the compiler
**knows** that gv will never change from a single threads
point of view. Thus it **knows** that "true" is to always
be returned, so it just returns a non-zero value, 1.
```c
$ make clean
rm *.o *.asm

$ cat fgv.c
int volatile volatile_gv;
int gv;

// with -O3 reads volatile_gv twice
int get_volatile_gv(void) {
  int x = volatile_gv;
  return x == volatile_gv;
}

// with -O3 optimizes not read gv at all and just returns 1 i.e. true
int gfgv(void) {
  int x = gv;
  return x == gv;
}

$ make
clang -c -O3 fgv.c -o fgv.o
objdump --source -d -M intel fgv.o > fgv.asm

$ cat fgv.asm

fgv.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <get_volatile_gv>:
   0:	8b 0d 00 00 00 00    	mov    ecx,DWORD PTR [rip+0x0]        # 6 <get_volatile_gv+0x6>
   6:	31 c0                	xor    eax,eax
   8:	3b 0d 00 00 00 00    	cmp    ecx,DWORD PTR [rip+0x0]        # e <get_volatile_gv+0xe>
   e:	0f 94 c0             	sete   al
  11:	c3                   	ret    
  12:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 nop WORD PTR cs:[rax+rax*1+0x0]
  19:	1f 84 00 00 00 00 00 

0000000000000020 <gfgv>:
  20:	b8 01 00 00 00       	mov    eax,0x1
  25:	c3                   	ret
```
