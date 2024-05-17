NAME = pipex
CC =	cc 
CFLAGS = -Wall -Wextra -Werror 

SOURCE = mandatory/error.c mandatory/ft_free.c mandatory/ft_split.c mandatory/ft_split2.c mandatory/ft_start.c mandatory/ft_strjoin.c mandatory/ft_strstr.c mandatory/infile_cmd1.c mandatory/outfile_cmd2.c mandatory/pipex.c

SOURCEB = bonus/error_bonus.c bonus/ft_free_bonus.c bonus/ft_pipe_bonus.c bonus/ft_split2_bonus.c bonus/ft_split_bonus.c bonus/ft_strjoin_bonus.c bonus/ft_strstr_bonus.c bonus/get_cmd_bonus.c bonus/pipex_bonus.c bonus/process_bonus.c
OBJ = $(SOURCE:.c=.o)
BOBJ = $(SOURCEB:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	
bonus: $(BOBJ)
	$(CC) $(CFLAGS) $(BOBJ) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -rf $(OBJ) $(BOBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

