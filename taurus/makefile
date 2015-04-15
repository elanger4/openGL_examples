CXX := clang++
LDFLAGS := -lglut -lGL -lGLU
TARGET := a.out

$(TARGET): taurus.o
	LD$(CXX) $(LDFLAGS) -o $@ $^

.PHONY clean:
	rm *.o *~ $(TARGET)
	
