objs = main.o Student.o Element.o transform.o CSVReader.o
CC = g++

out: $(objs)
	$(CC) -o out $(objs)

main.o: main.cpp
Student.o: Student.h
Element.o: Element.h
transform.o: transform.h
CSVReader.o: CSVReader.h

clean:
	rm *.o out results/*