.PHONY:all
all: myexe myload
myexe:myexe.c
	gcc -o $@ $^ -std=c99
myload:myload.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -rf myload myexe
