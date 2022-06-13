main: main.o setting.o AdminAction.o UserAction.o
	gcc -o a main.c setting.o AdminAction.o UserAction.o

main.o: main.c basic.h setting.h AdminAction.h UserAction.h
	gcc -c main.c

setting.o: setting.c setting.h basic.h
	gcc -c setting.c

AdminAction.o: AdminAction.c AdminAction.h basic.h setting.h
	gcc -c AdminAction.c

UserAction.o: UserAction.c UserAction.h basic.h
	gcc -c UserAction.c

clean:
	rm *.o