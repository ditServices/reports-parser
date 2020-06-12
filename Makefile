SRCS = ca_mu.tab.c lex.yy.c ca_reports.c grids.c
HARU = /usr/local/lib/libhpdfs.a
LDFLAGS = -lz -lm
UNAME := $(shell uname)

all: $(SRCS)
	cc $(SRCS) $(HARU) $(LDFLAGS) -o build/careports

lex.yy.c: ca_mu.l
	flex ca_mu.l

ifeq ($(UNAME), Linux)
ca_mu.tab.c: ca_mu.y
	bison -d ca_mu.y
endif

ifeq ($(UNAME), Darwin)
ca_mu.tab.c: ca_mu.y
	usr/local/Cellar/bison/3.6.3/bin/bison -d ca_mu.y
endif

clean:
	rm -rf *.o *.out ca_mu.tab.c ca_mu.tab.h lex.yy.c build/camu

install:
	cp build/careports /usr/local/bin
