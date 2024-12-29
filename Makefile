# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -std=c++17 -g

# Output executable name
OUTPUT = figgie

# Source files
SRCS = main.cc deck.cc order.cc orderbook.cc player.cc noisy.cc probability.cc EVtrader.cc

# Object files
OBJS = $(SRCS:.cc=.o)

# Header files
HEADERS = deck.h order.h orderbook.h player.h noisy.h probability.h EVtrader.h

# Default target
all: $(OUTPUT)

# Linking the executable
$(OUTPUT): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(OBJS)

# Compile each source file into an object file
%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(OUTPUT)

# Phony targets
.PHONY: all clean
