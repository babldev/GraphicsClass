CXX = g++
CXXFLAGS = -Wall -c $(DEBUG) -I .
LFLAGS = -Wall $(DEBUG) -I . -framework OpenGL -framework GLUT 

BUBBLE_GAME_OBJS = \
BubbleGame/Elements/BGBall.o \
BubbleGame/Elements/BGSkybox.o \
BubbleGame/Elements/BGPlatform.o \
BubbleGame/BubbleGame.o

GRAPHICS_LIB_OBJS = \
GraphicsLib/GLDrawable.o \
GraphicsLib/GLMovable.o \
GraphicsLib/GLWindow.o \
GraphicsLib/GLerror.o \
GraphicsLib/Math/Vector3d.o \
GraphicsLib/RGBpixmap/RGBpixmap.o

BubbleGame : main.o $(BUBBLE_GAME_OBJS) $(GRAPHICS_LIB_OBJS)
	$(CXX) $(LFLAGS) main.o $(BUBBLE_GAME_OBJS) $(GRAPHICS_LIB_OBJS) -o p2

.cpp.o :
	$(CXX) $(CXXFLAGS) $< -o $@

cleano:
	$(RM) main.o $(BUBBLE_GAME_OBJS) $(GRAPHICS_LIB_OBJS)
clean:
	$(RM) main.o $(BUBBLE_GAME_OBJS) $(GRAPHICS_LIB_OBJS) p2
