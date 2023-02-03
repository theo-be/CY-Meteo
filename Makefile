
CC=gcc -Wall
OPTION= -lm
RM=rm -rf
SRC=$(wildcard src/*.c)
HEAD=$(wildcard head/*.h)
OBJ=$(SRC:.c=.o)
EXEC=bin/tri

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $^ -o $@ $(OPTION)

.PHONY : clean mrproper print

clean :
	$(RM) $(OBJ)

mrproper :
	$(RM) $(EXEC) $(OBJ)

print :
	@echo "SRC= $(SRC)"
	@echo "OBJ= $(OBJ)"