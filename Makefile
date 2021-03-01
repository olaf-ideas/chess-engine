CC := g++
FLAGS := -O3 -std=c++17 -g -Wall -Wextra -pedantic-errors -Wfatal-errors 
#-fsanitize=address -fsanitize=undefined -g
SFML := lib/SFML-2.5.1
SFML_FLAGS := -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
TARGET := chess-engine

SRCS := $(wildcard src/*.cpp)

OBJ := $(addprefix obj/, $(notdir $(patsubst %.cpp,%.o,$(SRCS))))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(FLAGS) -L$(SFML)/lib $(SFML_FLAGS) -o $@

obj/%.o: src/%.cpp src/%.hpp
	$(CC) $(FLAGS) -c -I$(SFML)/include $< -o $(addprefix obj/, $(notdir $(patsubst %.cpp,%.o,$<)))

obj/%.o: src/%.cpp
	$(CC) $(FLAGS) -c -I$(SFML)/include $< -o $(addprefix obj/, $(notdir $(patsubst %.cpp,%.o,$<)))

clean:
	rm -rf $(TARGET) $(OBJ)
	
.PHONY: all clean
