SRC:=$(wildcard ./*.cpp)
OBJS:=$(patsubst %.cpp, %.o, $(SRC))
GCC:=g++
INC:=./

TARGET:=server

all:$(TARGET)
$(TARGET):$(OBJS)
	$(GCC) $^ -I$(INC) -pthread  -o $@

%.o:%.cpp
	$(GCC) -c $< -o $@

.PHONY:clean
clean:
	$(RM) $(OBJS) $(TARGET)
