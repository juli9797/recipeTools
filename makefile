.PHONY: all
Name=recipeTools
src = src/main.cpp src/Recipe.hpp src/Serializer.hpp src/Debug.hpp src/Parser.hpp
main = src/main.cpp
all: $(Name) 

$(Name): $(src)
	g++ -std=c++20 $(main) -o $(Name) 
install: $(Name)
	cp $(Name) /bin/
run:
	./$(Name)
make clean:
	rm $(Name)
