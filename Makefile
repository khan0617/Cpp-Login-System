CC := g++
TARGET := program
CFLAGS := -g -o

all: $(TARGET)

$(TARGET): main.cpp json.hpp user_database.h user_database.cpp
	$(CC) main.cpp $(CFLAGS) $@

clean:
	rm $(TARGET)