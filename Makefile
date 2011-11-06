# Project name
NAME		=	chip8

# Debug mode
DEBUG 		=	yes

# Source directory
SRCDIR 		=	src/

# Threads
LDFLAGS		+=	-lsfml-system -lsfml-graphics

# DIR
DEBUG_DIR 	=	bin/

RELEASE_DIR	=	bin/

# Misc cmd
MKDIR		=	mkdir -p

PRINTF		=	printf

RM		=	rm -rf

# Includes
LDINC		+= 	-I include

# Debug / Release
ifeq ($(DEBUG),yes)
	CFLAGS	+=  -g3 -ggdb
	NAME := $(DEBUG_DIR)/$(NAME)
	CC = g++

else
	NAME := $(RELEASE_DIR)/$(NAME)
	CFLAGS	+= -O3 -ffast-math -funroll-all-loops -funroll-loops
	CC = g++
endif

CFLAGS	+=	-W -Wall -pedantic $(LDINC)

SRC	=	main.cpp	\
		graphics.cpp	\
		events.cpp	\
		emulator.cpp	\
		op/op_0_7.cpp	\
		op/op_8_9.cpp	\
		op/op_A_E.cpp	\
		op/op_F.cpp

SRC 	:= 	$(addprefix $(SRCDIR),$(SRC))

OBJ	=    	$(SRC:.cpp=.o)

all:   		$(NAME)

$(NAME):  	$(OBJ)
		@$(PRINTF) "\033[01m[*] \033[34mLinking objects with flags : $(CFLAGS)\n\033[0m"
		@$(CC) $^ -o $(NAME) $(CFLAGS) $(LDFLAGS) $(LDINC)
		@$(PRINTF) "\033[01m-> \033[32mDone. No error found.\n\033[0m"

%.o: %.cpp
	        @$(CC) -c $< -o $@ $(CFLAGS) $(LDINC)
		@$(PRINTF) "\033[32mSuccessfully compiled\033[1;32m $@\033[0;32m ...\n\033[0m"

clean:
		@$(PRINTF) "\033[01m\033[31mCleaning objects...\n\033[0m"
		@$(RM) $(OBJ)

fclean: 	clean
		@$(PRINTF) "\033[01m\033[31mCleaning executable...\n\033[0m"
		@$(RM) $(NAME)

re:		dir fclean $(NAME)

ex:		$(NAME)
		$(NAME) lol.xml

rex:		dir fclean $(NAME)
		$(NAME)

dir:
		@$(MKDIR) $(DEBUG_DIR)
		@$(MKDIR) $(RELEASE_DIR)

norme:
		@$(PRINTF) "\033[01m\033[33mChecking norme...\n\033[0m"
		@/u/all/astek/public/norme -nocheat $(SRC)

info:
		@$(PRINTF) "\033[01mProject : $(NAME)\n\033[0m"
		@$(PRINTF) "\033[01mCompile flags : $(CFLAGS)\n\033[0m"
ifeq ($(DEBUG),yes)
		@$(PRINTF) "\033[01m\033[31mDebug mode\n\033[0m"
else
		@$(PRINTF) "\033[01m\033[32mRelease mode\n\033[0m"
endif

depend:
		@$(PRINTF) "\033[01m\033[33m Making dependences...\n\033[0m"
		@makedepend -- $(LDINC) -- -Y $(SRC) 2> /dev/null
		@$(PRINTF) "\033[01m\033[32m Success.\n\033[0m"

lib:		
		make dir -C libs/network/
		make dir -C libs/containers/
		make re -C libs/containers/
		make re -C libs/network/

.SUFFIXES:

.PHONY:		clean, fclean
# DO NOT DELETE

src/main.o: include/emulator.h include/graphics.h
src/graphics.o: include/graphics.h
src/sync.o: include/emulator.h include/graphics.h
src/emulator.o: include/emulator.h include/graphics.h
src/op/op_0_7.o: include/emulator.h include/graphics.h include/op.h
