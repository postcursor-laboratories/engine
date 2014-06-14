OUTFILE = sfml-test

FILES_CPP  = $(shell find src -type f -name '*.cpp')
FILES_H    = $(shell find src -type f -name '*.hpp')
FILES_O    = $(foreach file, $(FILES_CPP), $(patsubst src/%, obj/%, $(patsubst %.cpp, %.o, $(file))))
#FILES_O    = $(foreach file, $(patsubst %.cpp, %.o, $(FILES_CPP)), obj/$(notdir $(file)))

COMPILE_FLAGS = -Wall -std=c++11

# Set up linker flags
ifeq ($(shell uname), Linux)
ifeq ($(shell uname -m), x86)
LINK_FLAGS = -Llib/linux-i386 -lsfml-graphics -lsfml-system -lsfml-window
endif
ifeq ($(shell uname -m), x86_64)
LINK_FLAGS = -Llib/linux-amd64 -lsfml-graphics -lsfml-system -lsfml-window
endif
endif
ifeq ($(shell uname), Darwin)
LINK_FLAGS = -Llib/darwin-universal -framework sfml-graphics -framework sfml-system -framework sfml-window
endif

.PHONY: all clean

all:	$(OUTFILE)

# The compilation stage. This outputs object files.
#$(FILES_O):	$(FILES_CPP) obj/.dirstamp
#	g++ -c $(FILES_CPP) $(COMPILE_FLAGS)

obj/%.o:	src/%.cpp src/%.hpp obj/.dirstamp
	-mkdir -p $(dir $@)
	g++ -c $< -o $@ $(COMPILE_FLAGS)

# Here we link our object files to the libraries in LINK_FLAGS and create a binary
$(OUTFILE):	$(FILES_O) obj/.dirstamp
	g++ $(FILES_O) -o $(OUTFILE) $(LINK_FLAGS)

# For updating the temporary obj directory, which holds object files.
# See http://stackoverflow.com/questions/3477418/suppress-make-rule-error-output.
obj/.dirstamp:
	mkdir -p obj
	touch $@

run:	$(OUTFILE)
	./$(OUTFILE)

clean:
	-$(RM) $(OUTFILE)
	-$(RM) -rf obj
