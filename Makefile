SRCS = ca_mu.tab.c lex.yy.c ca_reports.c

all: $(SRCS)
	cc $(SRCS) -o camu

lex.yy.c: ca_mu.l
	flex ca_mu.l

ca_mu.tab.c: ca_mu.y
	bison -d ca_mu.y

clean:
	rm -rf *.o *.out ca_mu.tab.c ca_mu.tab.h lex.yy.c
