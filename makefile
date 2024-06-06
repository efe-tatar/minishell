SRC=$(wildcard src/*.c)
TEMP=$(SRC:.c=.o)
OBJ=$(subst src,build,$(TEMP))
INC=$(wildcard inc/*.h)

all : exe

debug:
	@echo $(SRC)
	@echo $(OBJ)
	@echo $(INC)

build/%.o : $(SRC) $(INC)
	gcc -c $< -o $@

exe: $(OBJ)
	echo hello
	gcc -fsanitize=address $< -o bin/$@

clean:
	rm -f build/*.o
	rm -f bin/exe