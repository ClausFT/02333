CC ?= gcc


CCWARNINGS ?= -W -pedantic -Werror -Wall -std=gnu99 -fno-strict-aliasing -fno-common -Wno-unused-parameter
CCOPT ?= -fstrict-aliasing -fstrict-overflow 

CFLAGS ?= $(CCWARNINGS) $(CCOPT)

SOURCES:=check_mm.c mm.c memory_setup.c
OBJECTS:=$(SOURCES:.c=.o)

EXECUTABLE:=run_tests

.PHONY: all clean debugger check 

.PHONY: debug
debug: CFLAGS += -O0 -ggdb3
debug: $(EXECUTABLE)

.PHONY: release
release: CFLAGS += -O3
release: $(EXECUTABLE)

all: debug

%.o: %.c mm.h
	echo CC $< && $(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	echo LD $@ && $(CC) $(CFLAGS) $(OBJECTS) -o $@ -lcheck

clean:
	rm -rf *o *~ $(EXECUTABLE) $(EXECUTABLE).dSYM

debugger: $(EXECUTABLE)
	gdb ./$(EXECUTABLE)

check: $(EXECUTABLE)
	./$(EXECUTABLE)


