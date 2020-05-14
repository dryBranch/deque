prj = libdeque.a
CC = gcc
item = main deque
objs = $(item:%=%.o)

test : $(objs)
	gcc $(objs) -o test -Wall && ./$@

target : deque.c deque.h
	gcc deque.c -c -o deque.o
	ar rcs $(prj) deque.o

deque.o : deque.c

main.o : main.c

.PHONE: clean run

clean:
	@echo '========begin======'
	rm -f $(prj) $(objs) test
	@echo '=========end======='

run:
	./$(prj)
