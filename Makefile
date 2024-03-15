NAME		=		matrix

#	DIR

SRC_DIR		=		src/

INC_DIR		=		src/

BUILD_DIR	=		.build/

#	FILES

SRC			=		main.cpp	\
					matrix.cpp	\
					vector.cpp	\
					tests/test.cpp \
					tests/test_constraints.cpp \
					tests/test_basic_arithmetic.cpp \
					tests/test_linear_combination.cpp \

OBJ			=		$(addprefix $(BUILD_DIR), $(SRC:.cpp=.o))

DEPS		=		$(addprefix $(BUILD_DIR), $(SRC:.cpp=.d))

#	FLAGS

CFLAGS		=		-Wall -Werror -Wextra -std=c++20 -g3

IFLAGS		=		-I $(INC_DIR)

DFLAGS		=		-MMD -MP

#	RULES

.PHONY:				all
all:				$(NAME)

.PHONY:				clean
clean:
					$(RM) $(OBJ) $(DEPS)

.PHONY:				fclean
fclean:
					$(RM) $(OBJ) $(DEPS) $(NAME)

.PHONY:				re
re:					fclean
					$(MAKE)

#	EXECUTABLES

-include			$(DEPS)

$(NAME):			$(OBJ)
					$(CXX) $(CFLAGS) $(DFLAGS) $(IFLAGS) $^ -o $@

#	OBJECTS FILES

$(BUILD_DIR)%.o:	$(SRC_DIR)%.cpp
					mkdir -p $(shell dirname $@)
					$(CXX) $(CFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@