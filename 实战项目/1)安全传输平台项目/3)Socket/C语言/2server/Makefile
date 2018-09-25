SRC:=$(wildcard ./*.c)
OBJS:=$(patsubst %.c, %.o, $(SRC))
GCC:=gcc
INC:=./

TARGET:=server

all:$(TARGET)
$(TARGET):$(OBJS)
	$(GCC) $^ -I$(INC) -pthread  -o $@

%.o:%.c
	$(GCC) -c $< -o $@

.PHONY:clean
clean:
	$(RM) $(OBJS) $(TARGET)
