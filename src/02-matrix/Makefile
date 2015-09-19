build :
		gcc -g app.c -o app

build_gprof :
		gcc -pg app.c -o app

assembler :
		gcc -S app.c -o app.s

assembler_d:
		gcc -S app.c -g -o app_d.s

assembler_pg:
		gcc -S app.c -pg -o app_pg.s

object :
		gcc -c app.c -o app.o

object_pg :
		gcc -c app.c -pg -o app_pg.o

.PHONY:clean
clean:
	rm -f *.s
	rm -f *.o
	rm -f app
	rm -f *.out
	rm -f callgrind.out.*
