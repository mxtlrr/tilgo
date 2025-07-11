CC := g++
CFLAGS := -Iinclude -O2 -Wall -Wextra -g -std=c++23
LDFLAGS := -shared
TARGET := bin/tilgo.dll

override CPPFILES := $(wildcard src/*.cpp)
override OFILES := $(CPPFILES:.cpp=.o)
all: $(TARGET)


$(TARGET): $(OFILES)
	@-mkdir bin
	@$(CC) -shared $(OFILES) -o $@
	
src/%.o: src/%.cpp
	@echo CXX $^
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@powershell -Command "del $(OFILES) ; rm -Recurse bin -Force"