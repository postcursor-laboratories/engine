OUTFILE = sfml-test

FILES_CPP  = $(shell find . -type f -name '*.cpp')
FILES_H    = $(shell find . -type f -name '*.h')
FILES_O    = $(foreach file, $(patsubst %.cpp, %.o, $(FILES_CPP)), obj/$(notdir $(file)))

GCC_COMPILE_FLAGS = -Wall
GCC_LINK_FLAGS = -Llib -lsfml-graphics -lsfml-system -lsfml-window

.PHONY: all clean

all:	$(OUTFILE)

# The compilation stage. This outputs object files.
#$(FILES_O):	$(FILES_CPP) obj/.dirstamp
#	@gcc -c $(FILES_CPP) $(GCC_COMPILE_FLAGS)

obj/%.o:	src/%.cpp src/%.h obj/.dirstamp
	@gcc -c $< -o $@ $(GCC_COMPILE_FLAGS)

# Here we link our object files to the libraries in GCC_LINK_FLAGS and create a binary
$(OUTFILE):	$(FILES_O) obj/.dirstamp
	@gcc $(FILES_O) -o $(OUTFILE) $(GCC_LINK_FLAGS)

# For updating the temporary obj directory, which holds object files.
# See http://stackoverflow.com/questions/3477418/suppress-make-rule-error-output.
obj/.dirstamp:
	@mkdir -p obj
	@touch $@

run:	$(OUTFILE)
	@./$(OUTFILE)

clean:
	-@$(RM) $(OUTFILE)
	-@$(RM) -rf obj