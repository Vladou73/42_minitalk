#include "./includes/client.h"

void  ft_send_signal(int pid, char c)
{
  int mask = 128; /* 10000000 */
  while (mask > 0)
  {
    if ((c & mask) > 0)
      kill(pid, SIGUSR1); //signal for bit 1
    else
      kill(pid, SIGUSR2); //signal for bit 0
    mask >>= 1; /* move the bit down */
    //pause();
    usleep(1000); //need this usleep otherwise for large messages all signals are not sent
  }
}

static void ft_handler_pingpong(int sigtype, siginfo_t *siginfo, void *ucontext)
{
  (void)sigtype;
  (void)siginfo;
  (void)ucontext;
  usleep(10);
}

int main(int argc, char **argv)
{
  char  *msg;
  int   pid;
  struct sigaction sa_client;

  if (argc < 3)
    return (1);

  ft_memset(&sa_client, 0, sizeof(struct sigaction));
  sa_client.sa_sigaction = ft_handler_pingpong;
  sa_client.sa_flags = SA_SIGINFO;

  pid = ft_atoi(argv[1]);
  msg = argv[2];

//  sigaction(SIGUSR1, &sa_client, NULL);

  while (*msg)
  {
    ft_send_signal(pid, *msg);
    msg++;
    // usleep(100);
    // break;
  }
  ft_send_signal(pid, '\0');
  return (0);
}
