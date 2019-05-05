SO = libagl.so

# All cpp files from src/
SOURCES = $(wildcard src/*.cpp)

SOURCES += glad/glad.cpp

# imgui sources for UI
SOURCES += imgui-master/imgui.cpp imgui-master/imgui_demo.cpp 
SOURCES += imgui-master/imgui_draw.cpp imgui-master/imgui_widgets.cpp
SOURCES += imgui-master/examples/imgui_impl_glfw.cpp 
SOURCES += imgui-master/examples/imgui_impl_opengl3.cpp

# The corresponding .o file for every .cpp file
OBJS = $(addprefix obj/, $(notdir $(SOURCES:.cpp=.o)))

LIBS = -lGL `pkg-config --static --libs glfw3`
INCLUDE_PATHS = -I include -I imgui-master -I imgui-master/examples -I glad -I stb
IMGUI_FLAGS = -DIMGUI_IMPL_OPENGL_LOADER_GLAD 
CXXFLAGS =  $(INCLUDE_PATHS) $(IMGUI_FLAGS) -fPIC `pkg-config --cflags glfw3`

obj/%.o:src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/%.o:imgui-master/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/%.o:imgui-master/examples/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/%.o:glad/glad/glad.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

$(SO): $(OBJS)
	$(CXX) -shared -o $(SO) $(OBJS) $(LIBS)
  
all: $(SO)
	@echo Build complete
  
LIB_LOCATION=/home/ati/repos/agl2.0/
test: all
	$(CXX) -L$(LIB_LOCATION) -Wl,-rpath=$(LIB_LOCATION) -Wall test/test.cpp -lagl $(INCLUDE_PATHS) -o test/test

clean:
	rm -f $(EXE) $(OBJS) $(SO)
