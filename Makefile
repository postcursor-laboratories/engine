OUTFILE = sfml-test

FILES_CPP  = $(shell find . -type f -name '*.cpp')
FILES_H    = $(shell find . -type f -name '*.h')
FILES_O    = $(patsubst %.cpp, %.o, $(FILES_CPP))

TO_COMPILE = $(FILES_CPP) $(FILES_H)

GCC_COMPILE_FLAGS = -Wall
GCC_LINK_FLAGS = -Llib -lsfml-graphics -lsfml-system -lsfml-window

.PHONY: all clean

all:	$(OUTFILE)

# The compilation stage. This outputs object files.
$(FILES_O):	$(TO_COMPILE)
	-@mkdir obj
	@gcc -c $< -o obj/$(notdir $@) $(GCC_COMPILE_FLAGS)

# Here we link our object files to the libraries in GCC_LINK_FLAGS and create a binary
$(OUTFILE):	$(FILES_O)
	@gcc $(TO_COMPILE) -o $(OUTFILE) $(GCC_LINK_FLAGS)

run:	$(OUTFILE)
	@./$(OUTFILE)

clean:
	-@$(RM) $(OUTFILE)
	-@$(RM) -rf obj