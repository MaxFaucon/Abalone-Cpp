#include <iostream>

#include "model/game.h"
#include "view/tui.h"
#include "controller/controller.h"
using namespace std;

int main()
{
    Game model { };
    Tui view { model };
    Controller controller(model, view);
    controller.start();
    return 0;
}
