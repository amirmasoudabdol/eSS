
RM=rm -f
# CC=gcc-4.8
# CFLAGS=-Wall -g -std=c99 -fopenmp -fsanitize=address -fno-omit-frame-pointer
CC=clang
CFLAGS=-Wall -g -std=c99 -O2 
# -O1 -fsanitize=address -fno-omit-frame-pointer
# -O2 -fsanitize=address -fno-omit-frame-pointer
OBJS:=$(patsubst %.c,%.o,$(wildcard *.c))
MAIN=_ess.o
all:$(MAIN)
$(MAIN):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(MAIN) -lm
#	$(CC) $(CCFLAGS) $(SS_INCLUDES)  -c $<

%.o: %.c ss.h
	$(CC) $(CFLAGS) -c $<
clean:
	$(RM) $(OBJS)
