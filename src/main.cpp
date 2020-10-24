#include <iostream>
#include <CommandStateMachine.h>
#include <States/StateType.h>
#include <IO/ConsoleIO.h>

int main(int argc, char* argv[]) {

  std::shared_ptr<Context> context = std::make_shared<Context>(std::make_shared<TaskService>(), std::make_shared<ConsoleIO>());
  auto start_state = StateType::MAIN_MENU;
  auto machine = CommandStateMachine::create(start_state, std::move(context));
  machine.execute();
   /*
  StateMachine k = StateMachine::create(StatesMachineType::MAIN, context);
  if(!k.execute()) {
    std::cout << "FATAL ERROR" << std::endl;
  }*/
  return 0;
}
