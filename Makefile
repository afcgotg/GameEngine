NAME = game

CXX = g++
CXXFLAGS = -pedantic -Wall
INCFLAGS = -I ./include/ 

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

# Default target
$(NAME): $(OBJECTS)
	@echo -n Building...
	@$(CXX) $^ -o $@ $(INCFLAGS) $(LIBFLAGS)
	@echo Done.

$(DEB_DIR)/$(NAME)_debug: $(OBJECTS:$(OBJ_DIR)/%.o=$(DEBUG_OBJ_DIR)/%.o)
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
linux_x64_debug: $(DEB_DIR)/$(NAME)_debug
linux_x64_debug: 
	cp -r ./assets $(DEB_DIR)/assets

##################################################
################### EXTRAS #######################
##################################################
copy: 
	rsync -r --update ./assets $(DEB_DIR)

clean_windows:
	@echo -n Cleaning...
	@rm -f $(OBJ_DIR)/*.o $(DEBUG_OBJ_DIR)/*.o $(NAME).exe $(DEB_DIR)/*.exe $(DEB_DIR)/assets 2>/dev/null || :
	@echo Done.

clean_linux:
	@echo Cleaning...
	@rm -f $(OBJ_DIR)/*.o $(DEBUG_OBJ_DIR)/*.o $(NAME) $(DEB_DIR)/*.exe $(DEB_DIR)/assets 2>/dev/null || :
	@echo Done.