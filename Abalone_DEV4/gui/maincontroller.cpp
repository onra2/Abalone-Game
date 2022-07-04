#include "maincontroller.h"

MainController::MainController()
{
    game = new Game();
    mainWindow =  new MainWindow();

    game->addObserver(mainWindow);
    mainWindow->addObserver(game);
}

void MainController::start(){
    mainWindow->show();
    game->start();
}
