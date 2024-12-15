SRCS = main.c	utils.1.c	parse/free_tree.c	parse/types.c	parse/cmd.c	parse/ft_split_v2.c	parse/tree.c			\
	parse/io.c	parse/fill_in.c	parse/tree_utils.c	parse/plist.c	parse/quotation.c	parse/heredoc.c					\
	parse/parse.c	parse/Syntax_Check/split_tokenize.c	parse/Syntax_Check/check_syntax_utils_2.c						\
	parse/Syntax_Check/check_validity_utils.c	parse/Syntax_Check/check_validity.c	parse/signals.c						\
	parse/tree_utils_1.c	parse/utils.c	parse/fill_out.c	execution/variable_value_2.c							\
	execution/handle_single_quots.c	execution/exec_pipe.c	execution/wildcard/check_wild_helper.c						\
	execution/wildcard/other.c	execution/wildcard/create_wild_pattern.c	utils.c	utils_0.c							\
	execution/wildcard/check_wild.c	execution/exec_tree.c	execution/built_in_cmd/bic_export_helper.c					\
	execution/built_in_cmd/bic_unset.c	execution/built_in_cmd/bic_cd.c	execution/built_in_cmd/bic_export.c				\
	execution/built_in_cmd/ft_exit.c	execution/built_in_cmd/bic_pwd.c	execution/built_in_cmd/bic_echo.c			\
	execution/built_in_cmd/bic_env.c	execution/built_in_cmd/bic_cd_2.c	execution/handle_variables_value_utils.c	\
	execution/handle_variables_value.c	execution/exec_cmd.c	execution/exeution.c	execution/handle_double_quots.c	\
	execution/utils.c	execution/apply_redirections.c	execution/wildcard/wildcard_redirection.c

OBJS = $(SRCS:.c=.o)

OBJ_FILES = $(addprefix srcs/, $(OBJS))

NAME = minishell

CC = cc

CFLAGS = -I./includes -Wall -Werror -Wextra

LIBFT = lib/libft/libft.a





all:$(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) -lreadline $(CFLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C lib/libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)
	make -C lib/libft clean

fclean: clean
	rm -f $(NAME)
	make -C lib/libft fclean

re: fclean all

