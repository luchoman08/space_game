all: 
	g++ -Iinclude -c main.cpp src/*.cpp -std=c++11
	g++ -o game *.o -L/usr/lib/x86_64-linux-gnu -lsfml-graphics -lsfml-window -lsfml-system -std=c++11

clean:
	rm *.o game
