#include <iostream>
#include "runtime/EngineRuntime.h"

int main(int argc, char **argv)
{
    std::cout << "Hello, world!\n";
    Elysian::EngineRuntime *engine = new Elysian::EngineRuntime();

    engine->startEngine();
    engine->run();
    engine->shutdownEngine();
}
