NAME = game

CXX = g++
CXXFLAGS = -pedantic -Wall
INCFLAGS = -I ./include/ -I ./tinyxml2/include/

SRC_DIR = ./src
DEB_DIR = ./debug

OBJ_DIR = ./obj
objdir:
	mkdir -p $(OBJ_DIR)

DEBUG_OBJ_DIR = $(OBJ_DIR)/debug
debdir:
	mkdir -p $(DEBUG_OBJ_DIR)

SOURCES = $(wildcard $(SRC_DIR)/*.cpp) $(SRC_DIR)/main.cpp
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

TINYXML2_OBJ = tinyxml2/obj/tinyxml2.o
TINYXML2_OBJ_DEB = tinyxml2/obj/debug/tinyxml2.o

# Default target
$(NAME): $(OBJECTS) $(TINYXML2_OBJ)
	@echo -n Building...
	@$(CXX) $^ -o $@  $(INCFLAGS) $(LIBFLAGS)
	@echo Done.

$(DEB_DIR)/$(NAME)_debug: $(OBJECTS:$(OBJ_DIR)/%.o=$(DEBUG_OBJ_DIR)/%.o) $(TINYXML2_OBJ_DEB)
	@echo -n Building...
	@$(CXX) $^ -o $@ $(INCFLAGS) $(LIBFLAGS) 
	@echo Done.

# Rule for compiling source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "> $(notdir $<)" | sed -e 's/^> src/>/g'
	@$(CXX) $(INCFLAGS) -c $< -o $@ $(CXXFLAGS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	@echo "> $(notdir $<)" | sed -e 's/^> src/>/g'
	@$(CXX) -c $(INCFLAGS) $< -o $@ $(CXXFLAGS)

$(DEBUG_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "> $(notdir $<)" | sed -e 's/^> src/>/g'
	@$(CXX) -c $(INCFLAGS) $< -o $@ $(CXXFLAGS)

$(DEBUG_OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	@echo "> $(notdir $<)" | sed -e 's/^> src/>/g'
	@$(CXX) -c $(INCFLAGS) $< -o $@ $(CXXFLAGS)

##################################################
#################### RELEASE #####################
##################################################

windows_x64_release: LIBFLAGS = `./SDL2/bin/sdl2-config --libs --cflags`
windows_x64_release: ./$(NAME)

linux_x64_release:	LIBFLAGS = -lSDL2_image `sdl2-config --libs --cflags`
linux_x64_release: ./$(NAME)

##################################################
##################### DEBUG ######################
##################################################

windows_x64_debug: LIBFLAGS = `./SDL2/bin/sdl2-config --libs --cflags` -g
windows_x64_debug: CXXFLAGS += -g
windows_x64_debug: $(DEB_DIR)/$(NAME)_debug
windows_x64_debug: 
	xcopy ".\assets" ".\debug\assets" //e //y //q //A

linux_x64_debug: CXXFLAGS += -g 
linux_x64_debug: LIBFLAGS = -lSDL2_image `sdl2-config --libs --cflags`
linux_x64_debug: $(DEB_DIR)/$(NAME)_debug
linux_x64_debug: 
	cp -r ./assets $(DEB_DIR)/assets


##################################################
################## tinyxml2 ######################
##################################################

tinyxml2/obj/tinyxml2.o:
	@mkdir tinyxml2/obj
	@echo "> $(notdir tinyxml2.cpp)" | sed -e 's/^> src/>/g'
	@$(CXX) -I tinyxml2/include/ -c tinyxml2/src/tinyxml2.cpp -o tinyxml2/obj/tinyxml2.o $(CXXFLAGS)

tinyxml2/obj/debug/tinyxml2.o:
	@mkdir tinyxml2/obj/debug
	@echo "> $(notdir tinyxml2.cpp)" | sed -e 's/^> src/>/g'
	@$(CXX) -I tinyxml2/include/ -c tinyxml2/src/tinyxml2.cpp -o tinyxml2/obj/debug/tinyxml2.o $(CXXFLAGS)

##################################################
################### EXTRAS #######################
##################################################
copy: 
	@echo -n Copiying assets folder...
	@rsync -r --update ./assets $(DEB_DIR)
	@echo Done.

clean_windows:
	@echo -n Cleaning...
	@rm -f $(OBJ_DIR)/*.o $(DEBUG_OBJ_DIR)/*.o $(NAME).exe $(DEB_DIR)/*.exe $(DEB_DIR)/assets 2>/dev/null || :
	@echo Done.

clean_linux:
	@echo -n Cleaning...
	@rm -f $(OBJ_DIR)/*.o $(DEBUG_OBJ_DIR)/*.o $(NAME) $(DEB_DIR)/*.exe $(DEB_DIR)/assets 2>/dev/null || :
	@echo Done.