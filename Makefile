EXEC=bfsk
SRC=main.c
CFLAGS=-W -Wall
LDFLAGS=-lm
DATA=data.raw

# Compiling targets

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) -o $(EXEC) $(LDFLAGS) $(CFLAGS) $(SRC)

# Audio-related targets

$(DATA): $(EXEC)
	./$(EXEC) < main.c > $(DATA)

play: $(DATA)
	play -r 8000 -e signed -b 8 $(DATA)

# Cleaning

clean:
	rm -f $(DATA)

mrproper: clean
	rm -f $(EXEC)
