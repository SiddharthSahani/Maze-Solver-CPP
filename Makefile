
CXXFLAGS = 
INCLUDES = -I . -I external/raylib/include
LDFLAGS  = -L external/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm


pathfinding: main.cpp
	g++ -o pathfinding.exe main.cpp $(CXXFLAGS) $(INCLUDES) $(LDFLAGS)


clean:
	rm pathfinding.exe
