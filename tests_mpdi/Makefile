# Commande de compilation et flags
CC=gcc -I../include
CFLAGS = -Wall -O3
LIBS = -lmpfi -lmpfr -lgmp -l:libmpdec.so.2 -lm
CXXFLAGS = -Wall -g -O0

# Exécutables
EXEC=mpdi_test 

# Sources et objets
SRCS_MPD= $(wildcard ../src_mpd/*.c)	
SRCS_MPDI= $(wildcard ../src_mpdi/*.c)
TESTS= $(wildcard ./*.c)
SRC_MPD= $(SRCS_MPD:../src_mpd/%=%)	
SRC_MPDI= $(SRCS_MPDI:../src_mpdi/%=%)
TEST= $(TESTS:./%=%)	
OBJ_MPD= $(SRC_MPD:.c=.o)
OBJ_MPDI= $(SRC_MPDI:.c=.o)	
OBJ_TEST= $(TEST:.c=.o)	
OBJS_MPD=$(SRC_MPD:%.c=%.o)
OBJS_MPDI=$(SRC_MPDI:%.c=%.o)	
OBJS_TEST=$(TEST:%.c=%.o)	
EXECS=$(EXEC:%=../bin/%)

# Règles de compilation
all: $(EXEC)

mpdi_test: $(OBJ_TEST) $(OBJ_MPD) $(OBJ_MPDI)
	$(CC) -o ../bin/$@ $(OBJS_TEST) $(OBJS_MPD) $(OBJS_MPDI) $(CFLAGS_MPD) $(LIBS)

%.o: ../src_mpd/%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LIBS)

%.o: ../src_mpdi/%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LIBS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LIBS)

# Suppression des fichiers temporaires
clean:
	rm -f *.o *~ src_mpdi/*~ *~ include/*~

# Clean et suppression des exécutables
mrproper: clean
	rm -f $(EXECS)

# Définition des cibles particulières
.PHONY: all, clean, mrproper
