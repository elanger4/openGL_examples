CXX := clang++
LDFLAGS := -lglut -lGL -lGLU
TARGET := a.out

$(TARGET): simpleTriangle.o
	$(CXX) $(LDFLAGS) -o $@ $^

.PHONY clean:
	rm *.o *~ $(TARGET)
	
