
CXXFLAGS = 
INCLUDES = -I . -I external/raylib/include
LDFLAGS  = -L external/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm


maze-solver: main.cpp
	g++ -o maze-solver.exe main.cpp $(CXXFLAGS) $(INCLUDES) $(LDFLAGS)


clean:
	rm maze-solver.exe
