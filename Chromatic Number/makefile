all: GraphColoring

GraphColoring: main.o coloringAlgorithms.o graphcommands.o iograph.o
	gcc main.o coloringAlgorithms.o graphcommands.o iograph.o -o GraphColoring 

main.o: main.c
	gcc -c main.c

coloringAlgorithms.o: coloringAlgorithms.c
	gcc -c coloringAlgorithms.c

graphcommands.o: graphcommands.c
	gcc -c graphcommands.c
	
iograph.o: iograph.c
	gcc -c iograph.c

clean:
	rm *o GraphColoring
