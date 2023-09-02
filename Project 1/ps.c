#include "types.h"
#include "user.h"
#include "syscall.h"
#include "traps.h"


int
main(int argc, char *argv[])
{
  pssyscall();

  exit();
}
