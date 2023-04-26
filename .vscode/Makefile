NAME = game
INCFLAGS = -I ../include/
CFLAGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused
SRC_DIR = ../src
OBJ_DIR = ../obj

SOURCES = $(wildcard $(SRC_DIR)/*.cpp) ../main.cpp
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Default target
../$(NAME): $(OBJECTS)
	$(CC) $^ -o $@ $(LIBFLAGS) $(CFLAGS)

../debug/$(NAME)_debug: $(OBJECTS)
	mkdir  -p ../debug
	$(CC) $^ -o $@ $(LIBFLAGS) $(CFLAGS)

# Rule for compiling source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(INCFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: ../main.cpp
	$(CC) $(INCFLAGS) -c $< -o $@

##################################################
############## Windows x32 target ################
##################################################
windows_x32_release: CC = i686-w64-mingw32-g++
windows_x32_release: LIBFLAGS = -L ../include/SDL/x32/lib
windows_x32_release: INCFLAGS += -I ../include/SDL/x32/include
windows_x32_release: CFLAGS += -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -m32 `sdl2-config --static-libs` -static
windows_x32_release: ../$(NAME)
# Debug
windows_x32_debug: CC = i686-w64-mingw32-g++
windows_x32_debug: LIBFLAGS = -L ../include/SDL/x32/lib
windows_x32_debug: INCFLAGS += -I ../include/SDL/x32/include
windows_x32_debug: CFLAGS += -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -m32 `sdl2-config --static-libs` -static -g
windows_x32_debug: ../debug/$(NAME)_debug
windows_x32_debug: 
	xcopy "..\assets" "..\debug\assets" //e //y //q //A

##################################################
############## Windows x64 target ################
##################################################
windows_x64_release: CC = x86_64-w64-mingw32-g++
windows_x64_release: LIBFLAGS = -L ../include/SDL/x64/lib
windows_x64_release: INCFLAGS += -I ../include/SDL/x64/include
windows_x64_release: CFLAGS += -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -m64 `sdl2-config --static-libs` -static
windows_x64_release: ../$(NAME)
# Debug
windows_x64_debug: CC = x86_64-w64-mingw32-g++
windows_x64_debug: LIBFLAGS = -L ../include/SDL/x64/lib
windows_x64_debug: INCFLAGS += -I ../include/SDL/x64/include
windows_x64_debug: CFLAGS += -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -m64 `sdl2-config --static-libs` -static
windows_x64_debug: ../debug/$(NAME)_debug
windows_x64_debug: 
	xcopy "..\assets" "..\debug\assets" //e //y //q //A

##################################################
############### Linux x64 target #################
##################################################
linux_x64_release: CC = g++
linux_x64_release: CFLAGS += -lSDL2_image -m64 `sdl2-config --static-libs --cflags`
linux_x64_release: ../$(NAME)
# Debug
linux_x64_debug: CC = g++
linux_x64_debug: CFLAGS += -lSDL2_image -m64 `sdl2-config --static-libs --cflags` -g
linux_x64_debug: ../debug/$(NAME)_d
linux_x64_debug: cp -r ../assets ../debug/





# Clean up object files and executable
clean:
	rm -f $(OBJ_DIR)/*.o ../$(NAME) ../$(NAME)/debug