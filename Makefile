CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJS = admin.o Attendence.o course.o Faculty.o main.o student.o

all: portal

portal: $(OBJS)
	$(CC) $(CFLAGS) -o portal $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q *.o *.txt portal
