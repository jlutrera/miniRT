/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 09:57:24 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/05 12:13:21 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdarg.h>

void	*ft_memset(void *dest, int c, size_t n);
void	ft_bzero(void *b, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *b, int c, size_t n);
int		ft_memcmp(const void *b1, const void *b2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *str);
size_t	ft_strlcat(char *dest, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
t_list	*ft_lstnew(void *content);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst,	void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);

//get_next_line project
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char	*get_next_line(int fd);
int		ft_findnl(char *s);
char	*ft_adjust_buff(char *s, int pos_nl, int i);
char	*ft_strjoin2(char *s1, char *s2);
int		ft_strlen2(char *s);

//ft_printf project
typedef struct s_flags{
	int		dot;
	bool	sharp;
	bool	add;
	bool	minus;
	bool	space;
	bool	zero;
	int		width;
	int		prec;
	char	type;
}	t_flags;
int		ft_printf(char const *format, ...);
int		ft_putchar(char c);
int		ft_putchar_bonus(char c, t_flags flags);
int		ft_putstr(char *s);
int		ft_putstr_bonus(char *s, t_flags flags);
int		ft_putdigit(long n, t_flags flags);
int		ft_putunsigned(unsigned long n, t_flags flags);
int		ft_puthex(unsigned int nb, t_flags flags);
int		ft_putpointer(void *pointer, t_flags flags);
int		char_in_str(char c, char const *s);
int		len_str(char *s);
int		len_number(long n, int len_base);
int		ulen_number(unsigned long n, int len_base);
char	*ft_uitoa(unsigned long n);
t_flags	read_flags(char *s, va_list ap);
int		ft_zeros(t_flags flags, char c, int len);
int		ft_spaces(t_flags flags, char c, int len);
int		putdigit(char *s, t_flags flags, char c, int len);

#endif