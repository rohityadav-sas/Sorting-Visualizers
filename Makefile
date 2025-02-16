SOURCES = ./src/main.cpp ./src/insertion_sort.cpp ./src/selection_sort.cpp ./src/quick_sort.cpp ./src/merge_sort.cpp

OBJECTS = $(SOURCES:.cpp=.o)

INCLUDE_DIRS = include/

LIB_DIRS = lib/

CXXFLAGS = -g -O1 -Wall -Wno-missing-braces -I $(INCLUDE_DIRS)
LDFLAGS = -L $(LIB_DIRS) -lraylib -lopengl32 -lgdi32 -lwinmm
REMOVE_TERMINAL_FLAGS = -Wl,-subsystem,windows

TARGET = ./build/visualizer.exe


default: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJECTS)
	g++ $^ -o $@ $(LDFLAGS) $(REMOVE_TERMINAL_FLAGS)

%.o: %.cpp
	g++ $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)