#include <CommandStateMachineCreator.h>

int main(int argc, char* argv[]) {
  auto machine = command_state_machine_creator::StartCLI();
  machine.execute();
  return 0;
}
