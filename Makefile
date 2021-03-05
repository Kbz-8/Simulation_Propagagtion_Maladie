########################### MAKEFILE ###########################

DEBUG = yes
CC = g++
ifeq ($(DEBUG),yes)
	CXXFLAGS = -std=c++14 -Wall -g
else
	CXXFLAGS = -std=c++14 -Wall
endif
LIBS = -lSDL2 -lGL -lGLEW -lSDL2_ttf # -lpthread -pthread

OBJ = obj/main.o obj/application.o obj/menu.o obj/entry.o obj/map.o obj/person.o obj/texts.o obj/indicevalidation.o obj/menupopup.o obj/gut.o obj/messagebox.o obj/input.o obj/buttonSDL.o obj/math.o obj/vec2.o obj/vec3.o obj/vec4.o obj/log.o obj/utils.o obj/text.o obj/shader.o obj/getpixelcolor.o obj/buttonGL.o
EXE = sim_Propagation # App name

all: $(EXE)

$(EXE):	$(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(LIBS)

ifeq ($(DEBUG),yes)
	@echo " "
	@echo " "
	@echo " "
	@echo "======================================================="
	@echo " "
	@echo "DEBUG: COMPILATION REUSSIE"
	@echo " "
	@echo "======================================================="
	@echo " "
	@echo " "
	@echo " "
else
	@echo " "
	@echo " "
	@echo " "
	@echo "======================================================="
	@echo " "
	@echo "RELEASE: COMPILATION REUSSIE"
	@echo " "
	@echo "======================================================="
	@echo " "
	@echo " "
	@echo " "
endif

obj/main.o: main.cpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/application.o: src/code/application.cpp src/code/application.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/menu.o: src/code/menu/menu.cpp src/code/menu/menu.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/entry.o: src/code/menu/entry/entry.cpp src/code/menu/entry/entry.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/map.o: src/code/map/map.cpp src/code/map/map.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/person.o: src/code/person/person.cpp src/code/person/person.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/texts.o: src/code/texts/texts.cpp src/code/texts/texts.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/indicevalidation.o: src/code/IndiceValidation/indicevalidation.cpp src/code/IndiceValidation/indicevalidation.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/menupopup.o: src/code/menu_pop_up/menupopup.cpp src/code/menu_pop_up/menupopup.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

####################################### GUT #######################################

obj/gut.o: includes/GUT/GUT.cpp includes/GUT/GUT.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/messagebox.o: includes/GUT/SDL2/messagebox/messagebox.cpp includes/GUT/SDL2/messagebox/messagebox.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/input.o: includes/GUT/SDL2/input/input.cpp includes/GUT/SDL2/input/input.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/buttonSDL.o: includes/GUT/SDL2/button/button.cpp includes/GUT/SDL2/button/button.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/math.o: includes/GUT/math/math.cpp includes/GUT/math/math.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/vec2.o: includes/GUT/math/Vec2/vec2.cpp includes/GUT/math/Vec2/vec2.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/vec3.o: includes/GUT/math/Vec3/Vec3.cpp includes/GUT/math/Vec3/Vec3.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/vec4.o: includes/GUT/math/Vec4/vec4.cpp includes/GUT/math/Vec4/vec4.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/log.o: includes/GUT/Log/log.cpp includes/GUT/Log/log.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/utils.o: includes/GUT/GL_old/utils.cpp includes/GUT/GL_old/utils.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/shader.o: includes/GUT/GL_old/shader/shader.cpp includes/GUT/GL_old/shader/shader.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/getpixelcolor.o: includes/GUT/GL_old/getPixelColor/getpixelcolor.cpp includes/GUT/GL_old/getPixelColor/getpixelcolor.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/buttonGL.o: includes/GUT/GL_old/button/button.cpp includes/GUT/GL_old/button/button.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

obj/text.o: includes/GUT/GL_old/text/text.cpp includes/GUT/GL_old/text/text.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS)

clean:
	rm  $(EXE)
