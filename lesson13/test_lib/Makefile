#静态库使用
#libmymath.a:sub.o add.o
#	ar -rc $@ $^
#%.o:%.c
#	gcc -c $<
#.PHONY:clean
#clean:
#	rm -rf *.o libmymath.a output
#.PHONY:output
#output:
#	mkdir output
#	cp -rf *.h output 
#	cp -rf libmymath.a output



#动态库使用
libmymath.so:add.o sub.o
	gcc -shared -o $@ $^
%.o:%.c
	gcc -fPIC -c $<
.PHONY:clean
clean:
	rm -rf libmymath.so  
.PHONY:lib_move
lib_move:
	mkdir lib_move 
	cp *.h lib_move 
	cp libmymath.so lib_move
