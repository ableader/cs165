CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		project1.o

LIBS =

TARGET =	project1

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
