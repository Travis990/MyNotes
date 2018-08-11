
#目标:依赖
#	命令
test: add.o sub.o mul.o div.o test.o
	gcc add.o sub.o mul.o div.o test.o -o test
add.o:add.c
	gcc -c add.c -o add.o
sub.o:sub.c
	gcc -c sub.c -o sub.o
mul.o:mul.c
	gcc -c mul.c -o mul.o
div.o:div.c
	gcc -c div.c -o div.o
test.o:test.c
	gcc -c test.c -o test.o

#目标
clean:
	rm -rf *.o test
