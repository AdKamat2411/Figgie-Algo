# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -std=c++17 -g
CXXFLAGS += -I./Mechanics -I./Agents

# Output executable name
OUTPUT = figgie

# Source files
SRCS = main.cc Mechanics/deck.cc Mechanics/order.cc Mechanics/orderbook.cc Mechanics/player.cc Agents/noisy.cc Agents/probability.cc Agents/EVtrader.cc Agents/bottomFeeder.cc

# Object files
OBJS = $(SRCS:.cc=.o)

# Header files
HEADERS = Mechanics/deck.h Mechanics/order.h Mechanics/orderbook.h Mechanics/player.h Agents/noisy.h Agents/probability.h Agents/EVtrader.h Agents/bottomFeeder.h

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
