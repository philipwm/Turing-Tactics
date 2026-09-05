#include "MainWindow.h"
#include "GameController.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    /*
    QCoreApplication::setOrganizationName("TuringTactics");
    QCoreApplication::setApplicationName("Turing Tactics");
    QCoreApplication::setApplicationVersion("1.0.0");
    */

    // Optional: Apply clean modern styling (Fusion style works well across OSs)
    app.setStyle(QStyleFactory::create("Fusion"));

    // 2. Instantiate the GameController (which encapsulates the engine models)
    GameController gameController;

    // 3. Instantiate the MainWindow and pass the controller reference/pointer
    MainWindow mainWindow(&gameController);
    mainWindow.show();

    // 4. Start the Qt Event Loop
    return app.exec();
}