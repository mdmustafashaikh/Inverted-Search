a.out: main.o common.o create.o display.o save.o search.o update.o
	gcc main.o common.o create.o display.o save.o search.o update.o -o a.out

main.o: main.c
	gcc -c main.c

common.o: common.c
	gcc -c common.c

create.o: create.c
	gcc -c create.c

display.o: display.c
	gcc -c display.c

save.o: save.c
	gcc -c save.c

search.o: search.c
	gcc -c search.c

update.o: update.c
	gcc -c update.c

clean:
	rm -f *.o a.out