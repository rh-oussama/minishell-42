/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:06:06 by oussama           #+#    #+#             */
/*   Updated: 2024/03/31 23:30:51 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define BRIGHTCYAN "\x1b[1;36m"
# define LIGTHGREEN "\x1b[38;2;34;221;34m"
# define RESET "\x1b[0m"
# define LIGTHRED  "\x1b[38;2;216;0;50m"

typedef struct s_io
{
	char			type;
	int				fd;
	char			*file;
	struct s_io		*next;
}	t_io;

typedef struct s_cmd
{
	char	**args;
	t_io	*in_red;
	t_io	*out_red;
}	t_cmd;

typedef struct s_plist
{
	char			type;
	void			*data;
	struct s_plist	*next;
}	t_plist;

typedef struct s_aolist
{
	t_io				*in;
	t_io				*out;
	char				type;
	void				*data;
	struct s_aolist		*next;
	struct s_aolist		*prev;
}	t_aolist;

typedef struct s_parse
{
	char		*row_data;
	char		**data;
	int			tmp_flag;
	int			herdoc_flag;
	char		*underscore;
	int			*arr;
	t_aolist	*aolist;
}	t_parse;

t_cmd		*create_command(char *data);
t_aolist	*new_node_aolist(char *data, t_aolist *prev);
t_aolist	*last_node_aolist(t_aolist *head);
t_aolist	*create_tree(char	*data);
t_plist		*create_plist(char	*data);
t_plist		*new_node_plist(char	*data);
t_io		*fill_inred(char	**args);
t_io		*fill_outred(char	**args);
t_io		*new_io_node(char	*data, char type);
t_io		*ft_heredoc(char	*limiter);
int			split_and_or_len( char	*row_data);
int			split_line_len(char *row_data);
int			pipe_line_len(char *data);
int			is_operator(char *data, int index);
int			is_a_parenthesis(char *data);
int			skip_quotation(char *data, int index);
int			skip_quotes_i(char *str, int *i);
int			check_syntax_validity(char	*str);
int			create_tempfile(char *buffer, int flag);
int			just_white_spaces(char *str);
int			create_tempfile(char *buffer, int quots);
int			generate_flag(void);
int			read_and_create_tmp_file(char *limiter, int flag);
char		**split_and_or(char *row_data);
char		*get_split_line(char *row_data, int *index);
char		*ft_theme(void);
char		**get_path(char **envp);
char		*get_pipe_line(char *data, size_t *index);
char		get_type_g(char *data);
char		**ft_split_own(char *str);
char		*remove_quotation(char *str);
char		*add_char_to_str(char *str, char c);
char		*quot_value(char *str, int flag);
char		*wildcard_infile(char *str);
char		*generate_a_buffer_name(int flag);
char		*read_heredoc(char *limiter, int quots);
char		*ft_add_nl(char *str);
char		*remove_parenthesis(char *row_data);
void		create_aolist(void);
void		free_split(char **arr);
void		add_back_io(t_io **head, t_io *new);
void		handle_single_quot(char **new_str, char *str, int *index);
void		handle_double_quot(char **new_str, char *str, int *index);
void		handle_value(char **new_str, char *str, int *index);
void		free_args_list(void *sa, void *sb, char *sc, char *sd);
void		split_and_or_helper(char *row_data, char **data, int *i, int *u);
char		*expand_infile(char *str);
void		add_it_on_env(char *key, char *value);
void		ft_underscore(char **args);
#endif