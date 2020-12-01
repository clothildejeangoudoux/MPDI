# Commande de compilation et flags
CC=gcc -I../include
CFLAGS = -Wall -O0
LIBS = -l:libmpdec.so.2 -lm
CXXFLAGS = -Wall -g -O0

# Exécutables
EXEC=mpdecimal_test 

# Sources et objets
TESTS= $(wildcard ./*.c)
TEST= $(TESTS:./%=%)	
OBJ_TEST= $(TEST:.c=.o)	
OBJS_TEST=$(TEST:%.c=%.o)	
EXECS=$(EXEC:%=../bin/%)

# Règles de compilation
all: $(EXEC)

mpdecimal_test: $(OBJ_TEST)
	$(CC) -o ../bin/$@ $(OBJS_TEST) $(CFLAGS_MPD) $(LIBS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LIBS)


# Suppression des fichiers temporaires
clean:
	rm -f *.o *~

# Clean et suppression des exécutables
mrproper: clean
	rm -f $(EXECS)

# Définition des cibles particulières
.PHONY: all, clean, mrproper
