# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 11:07:35 by lgiband           #+#    #+#              #
#    Updated: 2023/02/06 11:44:06 by lgiband          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/bash

# List of all the sources (.cpp)
# -------------------------------------------------------------------------
SRCS =		main.cpp \
			test_stack.cpp \
			test_reverse_iterator.cpp \
			test_equal.cpp \
			test_lexicographical_compare.cpp \
			test_map.cpp \
			test_set.cpp \
			test_pair.cpp \
			test_vector.cpp \
#			test_map.cpp \

# test_is_integral.cpp test_enable_if.cpp

# List of the related directories
# -------------------------------------------------------------------------
OBJS_DIR =	objs
SRCS_DIR =	srcs
HEAD_DIR =	includes

TAG	 =			std
# List of all compilation options
# -------------------------------------------------------------------------
CXX = 		c++
CXXFLAGS =	-Wall -Wextra -Werror --std=c++98
ifeq ($(n), std)
	CPPFLAGS	+= -D NAMESPACE=0
	TAG			=		std
else
	CPPFLAGS	+= -D NAMESPACE=1
	TAG			=		ft
endif

# Description of the final target
# -------------------------------------------------------------------------
NAME_FT =			ft_containers
NAME_STD =			std_containers

# Libraries
# -------------------------------------------------------------------------

# General rules on makefile
# -------------------------------------------------------------------------
OBJS = 		$(addprefix $(OBJS_DIR)/$(TAG)/,$(SRCS:.cpp=.o))
DEPS =		$(OBJS:.o=.d)

INCLUDES =	$(addprefix -I,$(HEAD_DIR))

RM =		rm -f

vpath %.c $(SRCS_DIR)
vpath %.h $(HEAD_DIR)

# Color
# -------------------------------------------------------------------------
_GREY		= \033[30m
_RED		= \033[31m
_GREEN		= \033[32m
_YELLOW		= \033[33m
_BLUE		= \033[34m
_PURPLE		= \033[35m
_CYAN		= \033[36m
_WHITE		= \033[37m
_NO_COLOR	= \033[0m

# create a compilation method to do two executables one with std and one without
# -------------------------------------------------------------------------
	
all:
	@make --no-print-directory n=ft $(NAME_FT)
	@make --no-print-directory n=std $(NAME_STD)

$(NAME_FT):		$(OBJS)
				$(CXX) $(LDFLAGS) -o $@ $(OBJS)

$(NAME_STD):	$(OBJS)
				$(CXX) $(LDFLAGS) -o $@ $(OBJS)

$(OBJS_DIR)/$(TAG)/%.o: $(SRCS_DIR)/%.cpp $(OBJS_DIR)/$(TAG)/%.d
	@if [ ! -d $(dir $@) ]; then \
		mkdir -p $(dir $@); \
		echo -e "\n$(_BLUE)$(dir $@): Create$(_NO_COLOR)"; \
	fi
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) -o $@ -c $<

clean:		dclean
			rm -Rf $(OBJS_DIR)
			@if [ -d $(OBJS_DIR) ]; then \
				find $(OBJS_DIR) -type d | xargs rmdir -p --ignore-fail-on-non-empty; \
			fi

fclean:		clean
			$(RM) std_containers
			$(RM) ft_containers
			rm -Rf test/

re:			fclean all

.PHONY:		all clean fclean re doc tests
.NOTPARALLEL: re $(NAME)

# Library rules
# -----------------------------------------------------------------------

# General dependences management
# ------------------------------------------------------------------------
$(OBJS_DIR)/$(TAG)/%.d: $(SRCS_DIR)/%.cpp Makefile
	@if [ ! -d $(dir $@) ]; then \
		mkdir -p $(dir $@); \
		echo -e "\n$(_BLUE)$(dir $@): Create$(_NO_COLOR)"; \
	fi
	$(CXX) -MM -MT $(@:.d=.o) $(CXXFLAGS) $(INCLUDES) $< >> $@

dclean:
			rm -Rf $(OBJS_DIR)/std/$(DEPS)
			rm -Rf $(OBJS_DIR)/ft/$(DEPS)

.PHONY:		dclean
.SILENT:    $(DEPS) dclean

-include	$(DEPS)
