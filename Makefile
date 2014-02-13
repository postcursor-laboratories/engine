OUTFILE = sfml-test

FILES_CPP  = $(shell find . -type f -name '*.cpp')
FILES_H    = $(shell find . -type f -name '*.h')
FILES_O    = $(patsubst %.cpp, %.o, $(FILES_CPP))

TO_COMPILE = $(FILES_CPP) $(FILES_H)

GCC_COMPILE_FLAGS = -Wall
GCC_LINK_FLAGS = -lsfml-graphics -lsfml-system -lsfml-window

.PHONY: all clean

all:	$(OUTFILE)

$(OUTFILE):	$(FILES_O)
	@gcc $(TO_COMPILE) -o $(OUTFILE) $(GCC_LINK_FLAGS)

$(FILES_O):	$(TO_COMPILE)
	@gcc -c $< -o $@ $(GCC_COMPILE_FLAGS)

run:	$(OUTFILE)
	@./$(OUTFILE)

clean:
	-@rm $(OUTFILE)