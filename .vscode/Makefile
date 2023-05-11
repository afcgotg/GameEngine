NAME = game
INCFLAGS = -I ../include/
CFLAGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused
SRC_DIR = ../src
OBJ_DIR = ../obj
DEB_DIR = ../debug
DEBUG_OBJ_DIR = $(OBJ_DIR)/debug

SOURCES = $(wildcard $(SRC_DIR)/*.cpp) ../main.cpp
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Default target
../$(NAME): $(OBJECTS)
	mkdir  -p $(DEB_DIR)
	$(CC) $^ -o $@ $(LIBFLAGS) $(CFLAGS)

$(DEB_DIR)/$(NAME)_debug: $(OBJECTS:$(OBJ_DIR)/%.o=$(DEBUG_OBJ_DIR)/%.o)
	$(CC) $^ -o $@ $(LIBFLAGS) $(CFLAGS)

# Rule for compiling source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(INCFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: ../main.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(INCFLAGS) -c $< -o $@

$(DEBUG_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(DEBUG_OBJ_DIR)
	$(CC) $(INCFLAGS) -c $< -o $@ $(CFLAGS)

$(DEBUG_OBJ_DIR)/main.o: ../main.cpp
	mkdir -p $(DEBUG_OBJ_DIR)
	$(CC) $(INCFLAGS) -c $< -o $@ $(CFLAGS)

##################################################
#################### RELEASE #####################
##################################################

windows_x32_release: CC = i686-w64-mingw32-g++
windows_x32_release: LIBFLAGS = -L ../include/SDL/x32/lib
windows_x32_release: INCFLAGS += -I ../include/SDL/x32/include
windows_x32_release: CFLAGS += -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -m32 `sdl2-config --static-libs` -static
windows_x32_release: ../$(NAME)

windows_x64_release: CC = x86_64-w64-mingw32-g++
windows_x64_release: LIBFLAGS = -L ../include/SDL/x64/lib
windows_x64_release: INCFLAGS += -I ../include/SDL/x64/include
windows_x64_release: CFLAGS += -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -m64 `sdl2-config --static-libs` -static
windows_x64_release: ../$(NAME)

linux_x64_release: CC = g++
linux_x64_release: CFLAGS += -lSDL2_image -m64 `sdl2-config --static-libs --cflags`
linux_x64_release: ../$(NAME)

##################################################
##################### DEBUG ######################
##################################################

windows_x32_debug: CC = i686-w64-mingw32-g++
windows_x32_debug: LIBFLAGS = -L ../include/SDL/x32/lib
windows_x32_debug: INCFLAGS += -I ../include/SDL/x32/include
windows_x32_debug: CFLAGS += -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -m32 `sdl2-config --static-libs` -static -g
windows_x32_debug: $(DEB_DIR)/$(NAME)_debug
windows_x32_debug: 
	xcopy "..\assets" "..\debug\assets" //e //y //q //A

windows_x64_debug: CC = x86_64-w64-mingw32-g++
windows_x64_debug: LIBFLAGS = -L ../include/SDL/x64/lib
windows_x64_debug: INCFLAGS += -I ../include/SDL/x64/include
windows_x64_debug: CFLAGS += -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -m64 `sdl2-config --static-libs` -static -g
windows_x64_debug: $(DEB_DIR)/$(NAME)_debug
windows_x64_debug: 
	xcopy "..\assets" "..\debug\assets" //e //y //q //A

linux_x64_debug: CC = g++
linux_x64_debug: CFLAGS += -lSDL2_image -m64 `sdl2-config --static-libs --cflags`
linux_x64_debug: $(DEB_DIR)/$(NAME)_debug
linux_x64_debug: 
	cp -r ../assets ../debug/assets


##################################################

##################################################
copy: 
	rsync -r --update ../assets $(DEB_DIR)/assets

clean:
	rm -f $(OBJ_DIR)/*.o $(DEBUG_OBJ_DIR)/*.o ../$(NAME) $(DEB_DIR)/* 2>/dev/null || :