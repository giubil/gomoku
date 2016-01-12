CXX		= g++

NAME	= gomoku

RM		= rm -rf
MKDIR	= mkdir -p

CXXFLAGS	+= -I./$(INC_PATH)
CXXFLAGS	+= -Wall -Wextra -W -std=c++14
# LDFLAGS		= -ldl -pthread
# LDFLAGS		+= -L./lib
# LDFLAGS		+= -Wl,--rpath=./lib

LDFLAGS_GRAPHIC	= -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

SRC_PATH	= src
SRC				= main.cpp \
						map.cpp \
						referee.cpp \
						multiPlayers.cpp \
						menu.cpp \
						gameClassInterface.cpp

OBJ_PATH	= obj
OBJ		= $(SRC:%.cpp=$(OBJ_PATH)/%.o)

INC_PATH	= inc
INC		= map.hh \
				referee.hh \
				gameClassInterface.hh \
				multiPlayers.hh \
				menu.hh

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
