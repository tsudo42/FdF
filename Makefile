# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 00:00:00 by tsudo             #+#    #+#              #
#    Updated: 2022/04/01 00:00:00 by tsudo            ###   ##########         #
#                                                                              #
# **************************************************************************** #

NAME		:= fdf
LIBFT		:= libs/libft/libft.a
MINILIBX	:= libs/minilibx-linux/libmlx.a
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -MMD -MP
LDFLAGS		:= -lm -lft -lmlx -lX11 -lXext
RM			:= rm -f

UNAME		:= $(shell uname)

ifeq ($(DEBUG), 1)
CFLAGS	+= -g3 -fsanitize=address
endif

# **************************************************************************** #

SRCS	+= $(C_SRCS)
C_SRCS	:= \
	srcs/camera/change_z_altitude.c \
	srcs/camera/dist_camera.c \
	srcs/camera/zoom_camera.c \
	srcs/camera/move_camera.c \
	srcs/camera/rotate_camera.c \
	srcs/camera/add_camera_effect.c \
	srcs/camera/reset_camera.c \

SRCS	+= $(F_SRCS)
F_SRCS	:= \
	srcs/fdf/draw_line.c \
	srcs/fdf/hook_key.c \
	srcs/fdf/load_file.c \
	srcs/fdf/load_point.c \
	srcs/fdf/color_utils.c \
	srcs/fdf/main.c \
	srcs/fdf/draw_fdf.c \
	srcs/fdf/draw_utils.c \
	srcs/fdf/load_file_eof.c \

INCS	:= \
	includes \
	libs/libft/includes \
	libs/minilibx-linux \

LIBS	:= \
	$(LIBFT) \
	$(MINILIBX) \

# **************************************************************************** #

OBJDIR	= objs/
OBJS	= $(patsubst %.c,$(OBJDIR)%.o, $(notdir $(SRCS)))
DEPS	= $(OBJS:.o=.d)
CFLAGS	+= $(addprefix -I,$(INCS))
LDFLAGS	+= $(addprefix -L,$(dir $(LIBS)))

ifeq ($(UNAME), Darwin)
	# mac
	LDFLAGS	+= -L/usr/X11R6/lib -framework OpenGL -framework AppKit
endif

vpath %.c $(sort $(dir $(SRCS)))

ifeq ($(MAKECMDGOALS),bonus)
	CFLAGS	+= -D PIPEX_BONUS
endif

GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m

# **************************************************************************** #

all: $(NAME)

$(NAME): $(LIBS) $(OBJDIR) $(OBJS)
	@printf "\n$(GR)=== Compiled [$(CC) $(CFLAGS)] ==="
	@printf "\n--- $(notdir $(SRCS))$(RC)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@
	@printf "$(YE)&&& Linked [$(CC) $(LDFLAGS)] &&&\n--- $(NAME)$(RC)\n"

-include $(DEPS)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf "$(GR)+$(RC)"

%.a:
	@printf "\n$(CY)~~~ Preparing $@ ~~~\n$(RC)"
	@make -C $(dir $@)
	@printf "$(CY)~~~ $@ Ready ~~~\n$(RC)"

mostlyclean:
	@printf "$(RE)--- Removing $(OBJDIR)$(RC)\n"
	@$(RM) -r $(OBJDIR)

clean: mostlyclean
	@printf "$(RE)~~~ Cleaning $(dir $(LIBFT)) ~~~$(RC)\n"
	@make -C $(dir $(LIBFT)) fclean
	@printf "$(RE)~~~ Cleaning $(dir $(MINILIBX)) ~~~$(RC)\n"
	@make -C $(dir $(MINILIBX)) clean

fclean: clean
	@printf "$(RE)--- Removing $(NAME)$(RC)\n"
	@$(RM) $(NAME)

re: fclean all

bonus: all

.PHONY: all mostlyclean clean fclean re bonus

# **************************************************************************** #
