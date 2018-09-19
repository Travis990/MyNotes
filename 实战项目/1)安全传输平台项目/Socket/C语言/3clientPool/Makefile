SRC:=$(wildcard ./*.c)
OBJS:=$(patsubst %.c, %.o, $(SRC))
GCC:=gcc
INC:=./

TARGET:=client

all:$(TARGET)
$(TARGET):$(OBJS)
	$(GCC) $^ -I$(INC) -o $@

%.o:%.c
	$(GCC) -c $< -o $@

.PHONY:clean
clean:
	$(RM) $(OBJS) $(TARGET)
