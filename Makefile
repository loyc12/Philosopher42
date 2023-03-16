#------------------------------------------------------------------------------#
#                                   COLOURS                                    #
#------------------------------------------------------------------------------#

DEF_COLOR = \033[0;39m
NC		= \e[0;39m
MAGENTA	= \033[0;95m
LMAGENTA = \e[95m
RED		= \033[0;91m
LRED	= \e[91m
YELLOW	= \033[0;93m
LYELLOW	= \e[93
GREEN	= \033[0;92m
LGREEN	= \e[92m
CYAN	= \033[0;96m
LCYAN	= \e[96m
BLUE	= \033[0;94m
GRAY	= \033[0;90m
WHITE	= \033[0;97m
#------------------------------------------------------------------------------#
#                                   GENERICS                                   #
#------------------------------------------------------------------------------#

# Special variables
DEFAULT_GOAL: all
.DELETE_ON_ERROR: $(NAME)
.PHONY: all ldirs bonus clean fclean clear fclear re run rerun leaks releaks display testerror test1 test2 test3 test200

#------------------------------------------------------------------------------#
#                                    FLAGS                                     #
#------------------------------------------------------------------------------#

# Set to @ to disable enable echoing cmd calls:
HIDE = @

# Use "XFLAGS=..." to set extra compilation flags, such as:
# -g					for debug mode
# -fsanitize=thread		to see race conditions

#------------------------------------------------------------------------------#
#                                  VARIABLES                                   #
#------------------------------------------------------------------------------#

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra $(XFLAGS)
RM		=	rm -rf
MD		=	mkdir -p
INCLUDE =	-I include

# Program and directory names
NAME	=	philo
SRCDIR	=	src/
OBJDIR	=	bin/
TSTDIR	=	tests/

# File names (including their subdirectory if needed)
FILES	=	main \
			acters \
			killers \
			checkers \
			utilities \
			initializers \

# Libraries (.a files) to include for compilation
LIBFT	=
LIBRL	=

SRCS	=	$(addprefix $(SRCDIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJDIR), $(addsuffix .o, $(FILES)))

# Default command to call when using make run or make leaks
CMD		=	./philo 200 520 200 200 8
#------------------------------------------------------------------------------#
#                                   TARGETS                                    #
#------------------------------------------------------------------------------#

all: ldirs $(NAME)

# Creates the object directories and subdirectories
ldirs:
	$(HIDE) $(MD) $(OBJDIR)

$(NAME): $(OBJS)
	$(HIDE) $(START)
	$(HIDE) $(CC) $(MODE) $(CFLAGS) $(INCLUDE) $(LIBFT) -o $@ $^ $(LIBRL)
	@echo "$(GREEN)Files compiled$(DEF_COLOR)"

$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	$(HIDE) $(CC) $(MODE) $(CFLAGS) -c $< -o $@ $(INCLUDE)

# Removes objects
clear: clean
clean:
	$(HIDE) $(RM) $(OBJS)
	$(HIDE) $(RM) $(NAME).dSYM
	@echo "$(MAGENTA)Object files cleaned$(DEF_COLOR)"

# Removes object dir and executable
fclear: fclean
fclean: clean
	$(HIDE) $(RM) $(OBJDIR)
	@echo "$(MAGENTA)Object directory cleaned$(DEF_COLOR)"
	$(HIDE) $(RM) $(NAME)
	@echo "$(RED)Executable cleaned$(DEF_COLOR)"

# Removes object dir and executable and remakes everything
re: fclean all
	@echo "$(CYAN)Cleaned and rebuilt everything!$(DEF_COLOR)"

# Runs the program
rerun: re run
run: all
	$(HIDE) $(CMD)

# Runs the program with valgrind
releaks: re leaks
leaks: all
	@echo "$(RED)Checking leaks...$(DEF_COLOR)"
	$(HIDE) valgrind --show-leak-kinds=all --trace-children=yes --leak-check=full --track-fds=yes --suppressions=include/supp $(CMD)

# Display start screen
display:
	$(HIDE) $(START)

testerror:
	./philo 201 500 200 200 8

	./philo 00 500 200 2000 8
	./philo 02 000 200 200 08
	./philo 02 200 000 200 08
	./philo 02 200 200 000 08
	./philo 02 200 200 200 00

	./philo -1 500 200 200 08
	./philo 02 -01 200 200 08
	./philo 02 200 -01 200 08
	./philo 02 200 200 -01 08
	./philo 02 200 200 200 -1

test1:
	./philo 1 210 200 200 8
	./philo 1 210 060 200 8
	./philo 1 210 200 060 8

	./philo 1 190 200 200 8
	./philo 1 190 200 060 8

	./philo 1 060 200 200 8
	./philo 1 060 060 060 8

test2:
	./philo 2 410 200 200 8
	./philo 2 410 060 200 8
	./philo 2 410 200 060 8

	./philo 2 390 200 200 8
	./philo 2 390 200 060 8

	./philo 2 060 200 200 8
	./philo 2 060 060 060 8

test3:
	./philo 3 610 200 200 8
	./philo 3 610 060 200 8
	./philo 3 610 200 060 8

	./philo 3 590 200 200 8
	./philo 3 590 200 060 8

	./philo 3 060 200 200 8
	./philo 3 060 060 060 8

test200: re
	./philo 200 500 200 200 8
	./philo 200 500 060 200 8
	./philo 200 500 200 060 8

	./philo 200 390 200 200 8
	./philo 200 390 200 060 8

	./philo 200 060 200 200 8
	./philo 200 060 060 060 8

testall: re test200 test3 test2 test1 testerror
