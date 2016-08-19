objs = utils.o main.o Student.o Element.o transform.o CSVReader.o CSVVectorContainer.o CSVMapContainer.o
CC = g++

out: $(objs)
	$(CC) -o out $(objs)

utils.o: utils.cpp
main.o: main.cpp utils.cpp
Student.o: Student.h utils.cpp
Element.o: Element.h
transform.o: transform.h utils.cpp CSVVectorContainer.o CSVMapContainer.o
CSVReader.o: CSVReader/CSVReader.h
	$(CC) -c CSVReader/CSVReader.cpp
CSVVectorContainer.o: CSVReader/CSVContainerAdapter.h CSVReader/CSVVectorContainer.h
	$(CC) -c CSVReader/CSVVectorContainer.cpp
CSVMapContainer.o: CSVReader/CSVContainerAdapter.h CSVReader/CSVMapContainer.h
	$(CC) -c CSVReader/CSVMapContainer.cpp

clean:
	rm *.o out results/*