SRC=$(wildcard src/*.c)
TEMP=$(SRC:.c=.o)
build=$(subst src,build,$(TEMP))
INC=$(wildcard lib/*.h)
STATIC=$(filter-out build/main.o, $(build))
DOX=$(`ls`)

all : exe

debug :
	@echo $(SRC)
	@echo $(build)
	@echo $(INC)

build/%.o : src/%.c $(INC)
	mkdir -p build
	gcc -c $< -o $@

exe : $(build)	
	gcc -o bin/exe $(SRC)
	gcc cmd/grep.c -o bin/grep
	gcc cmd/ls.c -o bin/ls
	gcc cmd/cat.c -o bin/cat
	gcc cmd/grep2.c -o bin/grep2

clean:
	rm -f build/*.o
	rm -f bin/*