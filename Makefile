make_all: LC4.o ObjectFiles.o trace

LC4.o : LC4.h LC4.c
	clang -c LC4.c

ObjectFiles.o : ObjectFiles.h ObjectFiles.c
	clang -c ObjectFiles.c

trace : trace.c LC4.c LC4.h ObjectFiles.c ObjectFiles.h
	clang -o trace trace.c LC4.c ObjectFiles.c

clean : trace LC4.o ObjectFiles.o trace.o
	rm trace LC4.o ObjectFiles.o trace.o
