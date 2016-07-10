objs = main.o Student.o Element.o
CC = g++

out: $(objs)
	$(CC) -o out $(objs)

main.o: main.cpp
Student.o: Student.h
Element.o: Element.h

clean:
	rm *.o out
