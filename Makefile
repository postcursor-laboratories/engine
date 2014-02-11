OUTFILE = game

.PHONY all run clean:

all:	$(OUTFILE)

$(OUTFILE):
	@gcc *.c *.h -o $(OUTFILE) -Wall

run:	$(OUTFILE)
	@./$(OUTFILE)

clean:
	-@rm $(OUTFILE)