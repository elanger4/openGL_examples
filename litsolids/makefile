CXX := clang++
LDFLAGS := -lglut -lGL -lGLU
TARGET := a.out

$(TARGET): litsolids.o
	LD$(CXX) $(LDFLAGS) -o $@ $^

.PHONY clean:
	rm *.o *~ $(TARGET)
	
