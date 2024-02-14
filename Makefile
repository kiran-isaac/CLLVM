CC=clang
CFLAGS=-Wall -Wextra -Werror -std=c++20 -pedantic -g

CPPFLAGS=-Iinclude
SRCS=$(wildcard src/*.cpp)
OBJS=$(patsubst src/%.cpp,build/%.o,$(SRCS))
BUILD = build

cllvm: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $(OBJS)

build/%.o: src/%.cpp
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:	
	rm -f cllvm
	rm -f $(OBJS)
	rm -rf $(BUILD)