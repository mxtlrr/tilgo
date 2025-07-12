CC := g++
CFLAGS := -Iinclude -Iimgui/backends -Iimgui -Imisc/cpp/ -O2 -Wall -Wextra -g -std=c++23
LDFLAGS := -ldwmapi -ld3d11 -ld3dcompiler -luser32 -lgdi32
TARGET := bin/flux.exe

override CPPFILES := $(wildcard src/*.cpp) $(wildcard src/gui/*.cpp) \
									imgui/backends/imgui_impl_dx11.cpp \
									imgui/backends/imgui_impl_win32.cpp \
									$(wildcard imgui/imgui*.cpp)

override OFILES := $(CPPFILES:.cpp=.o)

all: flux

flux:
	@-mkdir bin
	@echo Compiling...
	@$(CC) $(CPPFILES) $(CFLAGS) $(LDFLAGS) -o $(TARGET)
	@echo Done!

clean:
	@powershell -Command "del src/*.o ; rm -Recurse bin -Force"