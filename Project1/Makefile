CXX = g++
CXXFLAGS = -Wall -c $(DEBUG) -I .
LFLAGS = -Wall $(DEBUG) -I . -framework OpenGL -framework GLUT 

BUBBLE_GAME_OBJS = \
ShooterGame/Elements/SGBall.o \
ShooterGame/Elements/SGBullet.o \
ShooterGame/Elements/SGCannon.o \
ShooterGame/ShooterGame.o

GRAPHICS_LIB_OBJS = \
GraphicsLib/Geometry/Geometry.o \
GraphicsLib/Geometry/Circle.o \
GraphicsLib/Geometry/Rectangle.o \
GraphicsLib/GLDrawable.o \
GraphicsLib/GLMovable.o \
GraphicsLib/GLWindow.o \
GraphicsLib/Math/Vector2d.o

GRAPHICS_LIB_DIRS = 

BubbleGame : main.o $(BUBBLE_GAME_OBJS) $(GRAPHICS_LIB_OBJS)
	$(CXX) $(LFLAGS) main.o $(BUBBLE_GAME_OBJS) $(GRAPHICS_LIB_OBJS) -o p1 

.cpp.o :
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	$(RM) $(BUBBLE_GAME_OBJS) $(GRAPHICS_LIB_OBJS) p1
