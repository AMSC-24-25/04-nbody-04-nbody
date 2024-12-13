# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -O3 -std=c++20 -march=native

# Target executable name
TARGET = nbody

# Source files
SOURCES = main.cpp
HEADERS = nbody.hpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compiling source files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run target
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -g -DDEBUG -fsanitize=address,undefined
debug: LDFLAGS += -fsanitize=address,undefined
debug: clean all

# Performance build
perf: CXXFLAGS += -DNDEBUG -ffast-math
perf: clean all

# Help target
help:
	@echo "Available targets:"
	@echo "  all    : Build the executable (default)"
	@echo "  clean  : Remove object files and executable"
	@echo "  run    : Build and run the program"
	@echo "  debug  : Build with debug flags and sanitizers"
	@echo "  perf   : Build with maximum performance optimizations"
	@echo "  help   : Show this help message"
