GENERATES = prog prog-a prog-so liboutput_static.a liboutput.so README
CFLAGS = -fPIC
TRASH = *.o *.out

all:	liboutput_static.a liboutput.so prog prog-a prog-so test README

prog:	const.o fun.o prog.o
	cc const.o fun.o prog.o -o prog

prog-a:	prog.o liboutput_static.a
	cc $(CFLAGS) -L. prog.o -loutput_static -o prog-a

prog-so:	prog.o liboutput.so
	cc $(CFLAGS) -L. prog.o -loutput -o prog-so

liboutput_static.a:	fun.o const.o
	ar -rcs liboutput_static.a fun.o const.o

liboutput.so:	fun.o const.o
	cc -shared fun.o const.o -o liboutput.so

test:	test0 test1 test3

test0:	prog prog-a prog-so
	./prog > $@_outfile.out 2>&1
	./prog-a > $@_outfile-a.out 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so > $@_outfile-so.out 2>&1
	cmp $@_outfile.out $@_outfile-a.out
	cmp $@_outfile.out $@_outfile-so.out

test1:	prog prog-a prog-so
	./prog test > $@_outfile.out 2>&1
	./prog-a test > $@_outfile-a.out 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so test > $@_outfile-so.out 2>&1
	cmp $@_outfile.out $@_outfile-a.out
	cmp $@_outfile.out $@_outfile-so.out

test3:	prog prog-a prog-so
	./prog test1 test2 test3 > $@_outfile.out 2>&1
	./prog-a test1 test2 test3 > $@_outfile-a.out 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so test1 test2 test3 > $@_outfile-so.out 2>&1
	cmp $@_outfile.out $@_outfile-a.out
	cmp $@_outfile.out $@_outfile-so.out


fun.o:	fun.c
	cc $(CFLAGS) fun.c -c -o fun.o

prog.o:	prog.c
	cc $(CFlAGS) prog.c -c -o prog.o

const.o:	const.c
	cc $(CFLAGS) const.c -c -o const.o

README:	prog
	./prog 2> README

clean:
	rm -f $(TRASH)

distclean:	clean
	rm -rf $(GENERATES)
