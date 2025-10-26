#include <stdlib.h>
#include <wait.h>

#include "signals.h"

void init_child_signals(void) {
  struct sigaction sa;

  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_NOCLDSTOP | SA_NOCLDWAIT | SA_RESTART;
  sa.sa_handler = SIG_IGN;
  sigaction(SIGCHLD, &sa, NULL);

  // Clean up any zombies (inherited from .xinitrc etc) immediately.
  while (waitpid(-1, NULL, WNOHANG) > 0)
    ;
}
