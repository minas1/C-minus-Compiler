SWITCHES = -g
CC = gcc

../cmc: cmc.c cminus.fl cminus.y util.o symbol.o symboltable.o strvec.o intvec.o three-code-helper.o
	bison -d cminus.y
	flex cminus.fl
	$(CC) lex.yy.c util.o symbol.o symboltable.o strvec.o intvec.o three-code-helper.o cminus.tab.c cmc.c -o ../cmc -lfl $(SWITCHES)

util.o: util.c util.h
	$(CC) util.c -c $(SWITCHES)

symbol.o: symbol.c symbol.h
	$(CC) symbol.c -c $(SWITCHES)

symboltable.o: symboltable.c symboltable.h
	$(CC) symboltable.c -c $(SWITCHES)

strvec.o: strvec.c strvec.h
	$(CC) strvec.c -c $(SWITCHES)
	
intvec.o: intvec.c intvec.h
	$(CC) intvec.c -c $(SWITCHES)

three-code-helper.o: three-code-helper.c three-code-helper.h
	$(CC) three-code-helper.c -c $(SWITCHES)

clean:
	rm --force ../cmc *.o
