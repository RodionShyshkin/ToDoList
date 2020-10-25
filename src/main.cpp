#include <CommandStateMachineFactory.h>

int main(int argc, char* argv[]) {
  auto machine = CommandStateMachineFactory::StartCLI();
  machine.execute();
  return 0;
}
