SOURCES = $(wildcard hevadea/*.c)
OBJECTS = $(SOURCES:.c=.o)

CC = gcc

LDFLAGS = -lraylib -lm
CFLAGS = -O3 -MD \
		 -I. \
		 -Wall \
		 -Wextra \
		 -Werror
		 # -fsanitize=address \
		 # -fsanitize=undefined

hevadea.out: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: test clean

test: hevadea.out
	./hevadea.out

clean:
	rm -f $(OBJECTS) $(SOURCES:.c=.d) hevadea.out

-include $(SOURCES:.c=.d)
