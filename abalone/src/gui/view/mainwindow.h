#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

#include "view/ghexacell.h"
#include "view/hexboard.h"
#include "model/game.h"
#include "controller/controller.h"

class QDebug;
class Subject;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow Constructor of MainWindow.
     * @param model The model.
     * @param controller The controller.
     * @param parent The widget parent.
     */
    MainWindow(Game & model, Controller & controller,
                        QWidget *parent = nullptr);

    virtual ~MainWindow();    
    /**
     * @brief Virtual method that each observer must implement. It's this
     * method that the observed subject calls when there is a notification.
     * @param propertyName A string that allows the observer to know what
     * has been modified in the subject.
     */
    virtual void update(const std::string & propertyName) override;

    /**
     * @brief initGame Initializes the different elements of the view.
     */
    void initGame();

    /**
     * @brief moveSuccessfull Updates the view according to the successfull move.
     */
    void moveSuccessfull();

    /**
     * @brief moveFailed Updates the view according to the failed move.
     */
    void moveFailed();

    /**
     * @brief displayWinner Display the end game message.
     */
    void displayWinner();    

private slots:

    /**
     * @brief on_ghexacell_clicked Manages when the user presses a hexagon
     * @param position The position of the hexagon pressed by the user.
     */
    void on_ghexacell_clicked(Position position);

    /**
     * @brief on_helpButton_clicked Displays the help when the button is pressed.
     */
    void on_helpButton_clicked();

    /**
     * @brief on_StopButton_clicked Stops the application when the user press
     * the button.
     */
    void on_StopButton_clicked();

    /**
     * @brief on_restartButton_clicked Restarts the game when the user press the
     * button.
     */
    void on_restartButton_clicked();

private:
    Game & m_game;
    Ui::MainWindow *m_ui;
    HexBoard m_board;
    std::vector<Position> m_positions;
    Controller & m_controller;
};
#endif // MAINWINDOW_H
