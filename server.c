// char convert_binary_to_char(char *bin_str)
// {
// int i;
// int decimal_val;
// int total;

// total = 0;
// decimal_val = 1;
// i = 7;
// while(i >= 0)
// {
//   if (bin_str[i] == '1')
//     total += decimal_val;
//   decimal_val *= 2;
//   i--;

// }
// return (char)(total);
// }

// void handler_sigusr(int sigtype, siginfo_t *siginfo, void *ucontext)
// {
// static char binary_str[7];
// int   bin_index;

// (void)ucontext;
// usleep(100);
// bin_index = ft_strlen(binary_str);
// if (sigtype == SIGUSR1)
//   binary_str[bin_index] = '1';
// else
//   binary_str[bin_index] = '0';
// if (bin_index < 7)
//   binary_str[bin_index + 1] = 0;
// else
// {
//   binary_str[0] = 0;
//   msg = ft_strjoin_free(&msg, convert_binary_to_char(binary_str));
//   if (convert_binary_to_char(binary_str) == '\0')
//     ft_putstr_fd(msg, 1);
// }
// ft_putnbr_fd(1, siginfo->si_pid);
// kill(siginfo->si_pid, SIGUSR1);
// }

#include "./includes/server.h"

static char *msg;

static void handler_sigusr_bis(int sigtype, siginfo_t *siginfo, void *ucontext)
{
  static char c;
  static int bin_index;
  static char is_first_signal;

  (void)ucontext;
  (void)siginfo;
  usleep(100);

  if (is_first_signal == '\0')
  {
    bin_index = 7;
    is_first_signal = '1';
  }
  if (bin_index >= 0)
  {
    // ft_putnbr_fd(sigtype == SIGUSR1, 1);
    //kill(siginfo->si_pid, SIGUSR1);
    c |= (char)((sigtype == SIGUSR1) << bin_index);
    bin_index--;
  }
  if (bin_index < 0)
  {
    // ft_putchar_fd(c, 1);
    msg = ft_strjoin_free(&msg, c);
    is_first_signal = '\0';
    if (c == '\0')
    {
      ft_putstr_fd(msg, 1);
      msg = NULL;
    }
    c = 0;
  }
}

int main()
{
  struct sigaction sa;

  ft_memset(&sa, 0, sizeof(struct sigaction));
  // sa.sa_sigaction = handler_sigusr;
  sa.sa_sigaction = handler_sigusr_bis;
  sa.sa_flags = SA_SIGINFO;
  ft_putnbr_fd(getpid(), 1);
  ft_putchar_fd('\n', 1);
  sigaction(SIGUSR1, &sa, NULL);
  sigaction(SIGUSR2, &sa, NULL);

  while (1)
    pause();
  return (0);
}