OUTFILE = sfml-test

FILES_CPP  = $(shell find . -type f -name '*.cpp')
FILES_H    = $(shell find . -type f -name '*.hpp')
FILES_O    = $(foreach file, $(patsubst %.cpp, %.o, $(FILES_CPP)), obj/$(notdir $(file)))

COMPILE_FLAGS = -Wall

UNAME = $(shell uname)
ifeq ($(UNAME), Linux)
LINK_FLAGS = -Llib -lsfml-graphics -lsfml-system -lsfml-window
endif
ifeq ($(UNAME), Darwin)
LINK_FLAGS = -Llib -framework sfml-graphics -framework sfml-system -framework sfml-window
endif

.PHONY: all clean

all:	$(OUTFILE)

# The compilation stage. This outputs object files.
#$(FILES_O):	$(FILES_CPP) obj/.dirstamp
#	g++ -c $(FILES_CPP) $(COMPILE_FLAGS)

obj/%.o:	src/%.cpp src/%.hpp obj/.dirstamp
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
