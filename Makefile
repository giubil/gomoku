CXX		= g++

NAME	= gomoku

RM		= rm -rf
MKDIR	= mkdir -p

CXXFLAGS	+= -I./$(INC_PATH)
CXXFLAGS	+= -Wall -Wextra -W -std=c++14 -O3 -flto
LDFLAGS     =  -pthread
LDFLAGS     =  -O3 -flto

# LDFLAGS		= -ldl -pthread
# LDFLAGS		+= -L./lib
# LDFLAGS		+= -Wl,--rpath=./lib

LDFLAGS_GRAPHIC	= -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

SRC_PATH	= src
SRC				=   main.cpp \
                    Map.cpp \
					Referee.cpp \
					Menu.cpp \
					AGame.cpp \
					Game.cpp \
                    APlayer.cpp \
					Player.cpp \
					AI.cpp \
					Node.cpp \
					State.cpp

OBJ_PATH	= obj
OBJ		= $(SRC:%.cpp=$(OBJ_PATH)/%.o)

INC_PATH	= inc
INC         =   Map.hh \
				Referee.hh \
				AGame.hh \
				Game.hh \
				Menu.hh \
				APlayer.hh \
				Player.hh \
				AI.hh \
				Node.hh \
				State.hpp

DEP		= $(patsubst %,$(INC_PATH)/%,$(INC))

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(DEP)
	@$(MKDIR) $(OBJ_PATH)
	$(CXX) $(CXXFLAGS) -c $< -o $@

##
## Compile
##

$(NAME): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) $(LDFLAGS_GRAPHIC) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re fclean clean all
