# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Source files
SRCS = $(wildcard *.cpp)
# Output directory
OUTDIR = output
# Object files go into output/
OBJS = $(patsubst %.cpp,$(OUTDIR)/%.o,$(SRCS))
# Executable name
TARGET = $(OUTDIR)/main

all: $(OUTDIR) $(TARGET)

# Build executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile object files
$(OUTDIR)/%.o: %.cpp | $(OUTDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create output folder if it doesn't exist
$(OUTDIR):
	mkdir -p $(OUTDIR)

run: all
	./$(TARGET)

clean:
	rm -rf $(OUTDIR)
