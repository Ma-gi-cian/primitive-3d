build:
	g++ -Wall -std=c++17 ./src/main.cpp -lSDL2  -o	primitive-3d

run:
	./primitive-3d

clean:
	rm primitive-3d
