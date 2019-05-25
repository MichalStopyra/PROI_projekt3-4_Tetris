CC = g++

debug: CC+= -g

debug: output
	gdb output

compile: output
	./output

output: main.o Tetromino.o Node.o FifoQueue.o TheGame.o
	$(CC) main.o Tetromino.o Node.o FifoQueue.o TheGame.o -o output -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	$(CC) -c main.cpp -I /usr/include

Tetromino.o: Tetromino.cpp
	$(CC) -c Tetromino.cpp

Node.o: Node.cpp
	$(CC) -c Node.cpp

FifoQueue.o: FifoQueue.cpp
	$(CC) -c FifoQueue.cpp

TheGame.p: TheGame.cpp
	$(CC) -c TheGame.cpp

clean:
	rm *.o output


