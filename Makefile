fgv.asm: fgv.o
	objdump --source -d -M intel fgv.o > fgv.asm

fgv.o: fgv.c
	clang -c -O3 fgv.c -o fgv.o

clean:
	rm *.o *.asm
