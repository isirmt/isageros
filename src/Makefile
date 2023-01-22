# $ make と実行
CC  = g++
CFLAGS	= -std=c++11 -ggdb -O0
TARGET  = main
SRCS	= $(wildcard *.cpp)
OBJS	= $(SRCS:.cpp=.o)
INCDIR  = -I./inc -I./lib
LIBDIR  = 
LIBS	= -lglut -lGLU -lGL

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBDIR) $(LIBS)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(INCDIR) -c $(SRCS)

all: clean $(OBJS) $(TARGET)
clean:
	-rm -f $(OBJS) $(TARGET) *.d