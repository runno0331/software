CC = gcc
CFLAGS = -Wall -g
LDLIBS = -lm
OBJS = func2.o func1.o optimize.o
TARGET = optimizer

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDLIBS)

.PHONY: tmpclean clean
tmpclean:
	rm -f *~
clean: tmpclean
	rm -f $(OBJS) $(TARGET)