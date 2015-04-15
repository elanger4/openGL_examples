CXX := clang++
LDFLAGS := -lglut -lGL -lGLU
TARGET := a.out

$(TARGET): roboticArm.o
	LD$(CXX) $(LDFLAGS) -o $@ $^

.PHONY clean:
	rm *.o *~ $(TARGET)
	
