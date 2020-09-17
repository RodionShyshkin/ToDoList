#include <iostream>
#include <StateMachine.h>

int main(int argc, char* argv[]) {
  std::shared_ptr<Context> context = std::make_shared<Context>(std::make_shared<FakeService>(), std::make_shared<ConsoleIO>());
  StateMachine k = StateMachine::create(StatesGraphType::MAIN, context);
  if(!k.execute()) {
    std::cout << "ERROR" << std::endl;
  }
  return 0;
}
