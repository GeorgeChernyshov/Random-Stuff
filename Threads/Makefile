INCLUDE=include/
CFLAGS=-I$(INCLUDE) -std=c99 -Wall -Wextra
OBJS := bin/main.o bin/linkedlist.o bin/queue.o bin/squeue.o bin/wsqueue.o bin/thread_pool.o bin/pqsort.o

all: main

main: $(OBJS)
	gcc -pthread $(OBJS) -o pqsort

-include $(OBJS:.o=.d)

bin/%.o: src/%.c
	mkdir -p bin
	gcc -c $(CFLAGS) src/$*.c -o bin/$*.o
	gcc -MM $(CFLAGS) src/$*.c > bin/$*.d
	@mv -f bin/$*.d bin/$*.d.tmp
	@sed -e 's|.*:|$*.o:|' < bin/$*.d.tmp > bin/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < bin/$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> bin/$*.d
	@rm -f bin/$*.d.tmp

clean:
	rm -rf main bin/*.o bin/*.d *.d bin/
