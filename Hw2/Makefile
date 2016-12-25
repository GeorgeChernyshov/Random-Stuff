all: main

main: ./bin/main.o ./bin/Board.o ./bin/BoardView.o
	g++ ./bin/main.o ./bin/Board.o ./bin/BoardView.o -o main

bin/main.o: src/main.cpp ./include/Board.h ./include/BoardView.h
	g++ -std=c++03 -Werror -Wall src/main.cpp -c -o ./bin/main.o -I ./include

bin/Board.o: src/Board.cpp ./include/Board.h
	g++ -std=c++03 -Werror -Wall src/Board.cpp -c -o ./bin/Board.o -I ./include

bin/BoardView.o: src/BoardView.cpp ./include/BoardView.h
	g++ -std=c++03 -Werror -Wall src/BoardView.cpp -c -o ./bin/BoardView.o -I ./include

board_test: board_test

board_test: ./bin/test.o ./bin/BoardTest.o ./bin/Test.o
	g++ ./bin/test.o ./bin/BoardTest.o ./bin/Test.o -o board_test

bin/test.o: test/test.cpp ./include/BoardTest.h
	g++ -std=c++03 -Werror -Wall ./test/test.cpp -c -o ./bin/test.o -I ./include

bin/Test.o: test/Test.cpp ./include/Test.h
	g++ -std=c++03 -Werror -Wall ./test/Test.cpp -c -o ./bin/Test.o -I ./include

bin/BoardTest.o: test/BoardTest.cpp ./include/Board.h ./include/BoardTest.h
	g++ -std=c++03 -Werror -Wall ./test/BoardTest.cpp -c -o ./bin/BoardTest.o -I ./include
	
clean:
	rm ./bin/*
