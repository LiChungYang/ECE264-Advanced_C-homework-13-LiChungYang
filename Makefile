CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
GCC = gcc $(CFLAGS) 
EXEC = hw13
OBJS =  hw13.o tree.o scanner.o expressionTree.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

$(EXEC): $(OBJS) scanner.h tree.h expressionTree.h
	$(GCC) $(OBJS) -o $(EXEC) 

all: $(EXEC)
	$(GCC) $(OBJS) -o $(EXEC)

test: $(EXEC)
	mkdir -p output
	./$(EXEC) inputs/test1 output1
	./$(EXEC) inputs/test2 output2
	./$(EXEC) inputs/test3 output3
	./$(EXEC) inputs/test4 output4

memory: $(EXEC)
	mkdir -p moutput
	$(VALGRIND) --log-file=log1 ./$(EXEC) inputs/test1 moutput/output1
	$(VALGRIND) --log-file=log2 ./$(EXEC) inputs/test2 moutput/output2
	$(VALGRIND) --log-file=log3 ./$(EXEC) inputs/test3 moutput/output3
	$(VALGRIND) --log-file=log3 ./$(EXEC) inputs/test4 moutput/output4

%.o : %.c
	$(GCC) -c $< 

clean:
	/bin/rm -f *.o
	/bin/rm -f $(EXEC)
	/bin/rm -f id? first? last? log?


