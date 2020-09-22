#include <iostream>
#include <StateMachine.h>
#include <IO/ConsoleIO.h>

int main(int argc, char* argv[]) {
  std::shared_ptr<Context> context = std::make_shared<Context>(std::make_shared<TaskService>(), std::make_shared<ConsoleIO>());
  StateMachine k = StateMachine::create(StatesMachineType::MAIN, context);
  if(!k.execute()) {
    std::cout << "FATAL ERROR" << std::endl;
  }
  return 0;
}
