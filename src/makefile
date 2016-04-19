AIS=$(wildcard *_ai.c)
AISO=$(AIS:.c=.o)
CFLAGS = -std=c11 -rdynamic -g -D_GNU_SOURCE -Wall -Wextra

all: runner combine_ais
	gcc -o connect4 runner.o ais.o

runner: connect4.c connect4.h
	gcc -c connect4.c -o runner.o ${CFLAGS}

.c.o:
	@echo CC -c $< ${CFLAGS}
	@${CC} -c $< ${CFLAGS}
	objcopy --localize-symbol=setup $(<:.c=.o)
	objcopy --localize-symbol=make_move $(<:.c=.o)

combine_ais $(AIS):

combine_ais: $(AISO)
	ld -r $+ -o ais.o

clean:
	rm *.o connect4
