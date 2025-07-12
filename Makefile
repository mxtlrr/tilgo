CC := g++
CFLAGS := -Iinclude -O2 -Wall -Wextra -g -std=c++23
LDFLAGS := 
TARGET := bin/flux.exe

override CPPFILES := $(wildcard src/*.cpp)
override OFILES := $(CPPFILES:.cpp=.o)
all: $(TARGET)

$(TARGET): $(OFILES)
	@-mkdir bin
	@$(CC) $(OFILES) -o $@
	
src/%.o: src/%.cpp
	@echo CXX $^
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@powershell -Command "del src/*.o ; rm -Recurse bin -Force"