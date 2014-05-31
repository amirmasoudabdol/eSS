
RM=rm -f
CC=gcc-4.8
# CFLAGS=-Wall -g -std=c99 -O2 
#-fopenmp -fsanitize=address -fno-omit-frame-pointer
CC=clang
CFLAGS=-Wall -g -std=c99 -O2
GSL_INCLUDES=-I/usr/local/include
GSL_LIBS=-L/usr/local/lib
GSL_FLAGS=-lgsl -lgslcblas -lm
# -O1 -fsanitize=address -fno-omit-frame-pointer
# -O2 -fsanitize=address -fno-omit-frame-pointer
OBJS:=$(patsubst %.c,%.o,$(wildcard *.c))
MAIN=_ess.o
all:$(MAIN)
$(MAIN):$(OBJS)
	$(CC) $(CFLAGS) $(GSL_INCLUDES) $(GSL_LIBS) $(OBJS) -o $(MAIN) $(GSL_FLAGS)
	# $(CC) $(MAIN) 
#	$(CC) $(CCFLAGS) $(SS_INCLUDES)  -c $<

%.o: %.c ss.h
	$(CC) $(CFLAGS) -c $<
clean:
	$(RM) $(OBJS)
