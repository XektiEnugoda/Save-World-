# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -IInclude

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source and output
SRC = Src/main.cpp Src/Player.cpp Src/Star.cpp Src/Cutscene.cpp
OUT = game

# Build target
all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(SFML_LIBS)

# Clean target
clean:
	rm -f $(OUT)
