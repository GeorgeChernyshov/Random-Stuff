all: main

main: ./bin/main.o ./bin/Board.o ./bin/BoardView.o
	gcc ./bin/main.o ./bin/Board.o ./bin/BoardView.o -o main

bin/main.o: src/main.cpp ./include/Board.h ./include/BoardView.h
	gcc -std=c++03 -Werror -Wall src/main.cpp -c -o ./bin/main.o -I ./include

bin/Board.o: src/Board.cpp ./include/Board.h
	gcc -std=c++03 -Werror -Wall src/Board.cpp -c -o ./bin/Board.o -I ./include

bin/BoardView.o: src/BoardView.cpp ./include/BoardView.h
	gcc -std=c++03 -Werror -Wall src/BoardView.cpp -c -o ./bin/BoardView.o -I ./include
	
clean:
	rm ./bin/*
