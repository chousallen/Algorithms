# Compiler
CXX = g++

# Compiler flags
CXXFLAGS_OPT = -O3
CXXFLAGS_DBG = -O0 -g -Wall

# Source files
SRCS = ./src/main.cpp ./src/directed_graph.cpp ./src/undirected_graph.cpp ./src/disjoint_set.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = ./bin/cb

# Default target
all: opt

# Optimization mode
opt: CXXFLAGS = $(CXXFLAGS_OPT)
opt: $(EXEC)

# Debug mode
dbg: CXXFLAGS = $(CXXFLAGS_DBG)
dbg: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(EXEC)