CC = g++

#SPACE RECOGNITION
null :=
space := ${null} ${null}
${space} := ${space}# ${ } is a space. Neat huh?
#END OFSPACE RECOGNITION

EXEC_NAME = $(notdir $(subst ${ },_,$(shell pwd)) )
RMV = rm -f *.o

ifneq ($(wildcard /usr/include/SFML),)
	SFML_DIR_PREFIX = /usr
else
		SFML_DIR_PREFIX = /usr/local
	endif
CCFLAGS += -D LINUX

ifeq ($(OS),Windows_NT)
	#WINDOWS BUILD OPTIONS
	ifneq ($(wildcard C:/include/SFML),)
		SFML_DIR_PREFIX = /usr
	else
		SFML_DIR_PREFIX = /usr/local
	endif
	RMV = cmd //C del *.o
	EXEC_NAME = $(notdir $(subst ${ },_,$(shell cd)) ).exe
endif

SFML_INCLUDE_DIR = $(SFML_DIR_PREFIX)/include/SFML
SFML_FLAGS = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS = $(SFML_FLAGS) -I$(SFML_INCLUDE_DIR) -Wall -O0

.PHONY : all clean # Target that arent a file

all : $(EXEC_NAME) clean

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o) # Considera i file .cpp ma che che hanno come suffisso .o

$(EXEC_NAME) : $(OBJ)
	@echo "** Building main executable, aka $(EXEC_NAME) ..."
	$(CC) -o $@ $(OBJ) $(CFLAGS)

%.o: %.cpp
	@echo "** Building obj files..."
	$(CC) -c $< -o $@

clean :
	@echo "** Removing object files..."
	$(RMV)
