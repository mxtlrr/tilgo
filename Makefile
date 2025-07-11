CC := g++
CFLAGS := -Iinclude -O2 -Wall -Wextra -g
LDFLAGS :=
TARGET := bin/tilgo.exe

override CPPFILES := $(wildcard src/*.cpp)
override OFILES := $(CPPFILES:.cpp=.o)
all: $(TARGET)


$(TARGET): $(OFILES)
	@-mkdir bin
	@$(CC) $(LDFLAGS) $(OFILES) -o $@

src/%.o: src/%.cpp
	@echo CXX $^
	@$(CC) $(CFLAGS) -c $^ -o $@ 

clean:
	@powershell -Command "del src/*.o ; rm -Recurse bin -Force"