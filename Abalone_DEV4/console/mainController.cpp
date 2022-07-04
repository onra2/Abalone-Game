#include "mainController.h"

MainController::MainController()
{
    game = new Game;
    textView =  new TextView;

    game->addObserver(textView);
    textView->addObserver(game);
}

void MainController::start(){
    game->start();
}
