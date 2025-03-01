NAME := philo

override SRCDIR := srcs/

override BUILDDIR := .build/

override OBJDIR := $(addprefix $(BUILDDIR), objs/)

override DEPDIR := $(addprefix $(BUILDDIR), deps/)

BASENAME := main parsing utils thread_management threads_utils eat_utils \
			monitoring_utils

override SRCS := $(addprefix $(SRCDIR), $(addsuffix .c, $(BASENAME)))

override OBJS := $(addprefix $(OBJDIR), $(addsuffix .o, $(BASENAME)))

override DEPS := $(addprefix $(DEPDIR), $(addsuffix .d, $(BASENAME)))

INCS := includes

CC := cc

COMPFLAGS :=

CFLAGS := -Wall -Wextra -Werror

CPPFLAGS := -I$(INCS)

DEPSFLAGS := -MD -MP -MF

MAKEFLAGS += --no-print-directory

.DEFAULT_GOAL = all

-include $(DEPS)

.PHONY: all
all: 
	@$(MAKE) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CLAGS) $(CPPFLAGS) $(OBJS) $(LDLIBS) $(LDFLAGS) -o $(NAME) $(COMPFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.c | $(BUILDDIR) $(OBJDIR) $(DEPDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEPSFLAGS) $(DEPDIR)$*.d -c $< -o $@ $(COMPFLAGS)

$(BUILDDIR) $(OBJDIR) $(DEPDIR) $(BONUSBUILDDIR) $(BONUSDEPDIR) $(BONUSOBJDIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all
