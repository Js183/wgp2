CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS = -lreadline
TARGET = wgp2
SOURCES = main.c calculate.c stack.c transform.c
OBJECTS = $(SOURCES:.c=.o)
INCLUDES = -I.
all: $(TARGET)
$(TARGET): $(OBJECTS)
		$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJECTS) $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
clean:
	rm -f $(OBJECTS) $(TARGET)