run: balance.o
	g++ balance.o -o run

balance.o: balance.cpp
	g++ -c balance.cpp

clean:
	rm *.o run
