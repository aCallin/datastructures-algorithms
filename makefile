CC = g++
EXE = a.exe

DIR_SRC += src
DIR_SRC += src/algorithms
DIR_SRC += src/data-structures
DIR_SRC += src/misc
SRC += $(wildcard $(addsuffix /*.cpp, $(DIR_SRC)))
DIR_INC += $(addprefix -I, $(DIR_SRC))

.PHONY: all
all:
	$(CC) $(DIR_INC) $(SRC) -o $(EXE)

.PHONY: run
run: all
	./$(EXE)

.PHONY: clean
clean:
	rm $(EXE)
