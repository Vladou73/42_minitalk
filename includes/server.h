#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/libft.h"
# include <signal.h>
# include <stdarg.h>

static void handler_sigusr_bis(int sigtype, siginfo_t *siginfo, void *ucontext);

#endif