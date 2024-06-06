SRC=$(wildcard src/*.c)
TEMP=$(SRC:.c=.o)
OBJ=$(subst src,obj,$(TEMP))
INC=$(wildcard lib/*.h)

all : exe

debug :
	@echo $(SRC)
	@echo $(OBJ)
	@echo $(INC)

obj/%.o : src/%.c $(INC)
	mkdir -p obj
	gcc -c $< -o $@

exe : $(OBJ)
	gcc -fsanitize=address obj/main.o libhash.a -o $@

clean:
	rm -f obj/*.o
	rm -f *.a
	rm -f exe