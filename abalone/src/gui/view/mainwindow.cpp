#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QRectF>
#include <QMessageBox>
#include <cmath>
#include <iostream>

MainWindow::MainWindow(Game & model, Controller & controller, QWidget *parent)
    : QMainWindow(parent)
    , m_game { model }
    , m_ui { new Ui::MainWindow }
    , m_board { m_game.board() }
    , m_controller { controller }
{    
    m_game.addObserver(this);
    m_ui->setupUi(this);

    std::vector<GHexaCell *> gHexaCells = m_board.gHexaCells();
    auto scene = new QGraphicsScene();

    std::for_each(begin(gHexaCells), end(gHexaCells),
                  [this, scene](GHexaCell * e) {
        e->setPos(e->y(), e->x());
        scene->addItem(e);
        QObject::connect(e, SIGNAL(sendValue(Position)),
                         this,
                         SLOT(on_ghexacell_clicked(Position)));
    });
    auto view = new QGraphicsView(scene);
    view->update();
    m_ui->verticalLayout->addWidget(view);
    m_ui->whiteTurn->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::update(const std::string & propertyName)
{    
    if (propertyName == "Successful")
    {
        moveSuccessfull();
    } else if (propertyName == "Failed")
    {
        moveFailed();
    } else if (propertyName == "Init")
    {
        initGame();
    } else if (propertyName == "Over")
    {        
        displayWinner();
    }
}

void MainWindow::initGame()
{
    m_board.updateColors(m_game.board());
    std::string count = std::to_string(
                m_game.currentPlayer()->ejectedOpponentMarbles());
    m_ui->whiteCount->setText(QString::fromStdString(count));
    m_ui->blackCount->setText(QString::fromStdString(count));
    if (m_game.currentPlayer()->color() == Color::BLACK)
    {
        m_ui->whiteTurn->setVisible(false);
        m_ui->blackTurn->setVisible(true);
    } else
    {
        m_ui->blackTurn->setVisible(false);
        m_ui->whiteTurn->setVisible(true);
    }
}

void MainWindow::moveSuccessfull()
{
    m_board.updateColors(m_game.board());
    std::string count = std::to_string(
                m_game.currentPlayer()->ejectedOpponentMarbles());
    if (m_game.currentPlayer()->color() == Color::BLACK)
    {
        m_ui->whiteCount->setText(QString::fromStdString(count));
        m_ui->blackTurn->setVisible(false);
        m_ui->whiteTurn->setVisible(true);
    } else
    {
        m_ui->blackCount->setText(QString::fromStdString(count));
        m_ui->whiteTurn->setVisible(false);
        m_ui->blackTurn->setVisible(true);
    }
}

void MainWindow::moveFailed()
{
    m_board.updateColors(m_game.board());
}

void MainWindow::displayWinner()
{
    QMessageBox winnerMessage;
    winnerMessage.setWindowTitle("Winner");
    winnerMessage.setText("Congratulations ! \n\nThe winner is : "
                        + QString::fromStdString(m_game.winner())
                        + "\n\n Do you want to restart the game ?");
    QAbstractButton* aRestartButton =
            winnerMessage.addButton(tr("Restart"), QMessageBox::YesRole);
    QAbstractButton* aStopButton =
            winnerMessage.addButton(tr("Stop"), QMessageBox::NoRole);
    winnerMessage.exec();
    if (winnerMessage.clickedButton() == aRestartButton)
    {
        m_controller.initGame();
    } else if (winnerMessage.clickedButton() == aStopButton)
    {
        QApplication::quit();
    }
}

void MainWindow::on_ghexacell_clicked(Position position)
{        
    m_positions.push_back(position);

    if (m_positions.size() == 3)
    {
        if (m_positions.at(1) != m_positions.at(2))
        {
            m_controller.playTurn(m_positions);
        } else
        {
            m_positions.pop_back();
            m_controller.playTurn(m_positions);
        }

        m_positions.clear();
        m_controller.checkIfOver();
    }
}


void MainWindow::on_helpButton_clicked()
{
    QMessageBox helpMessage;
    helpMessage.setWindowTitle("Help");
    helpMessage.setText("Help for the moves : \n\n"
                    "To describe a movement, this game uses the ABA-PRO notation.\n"
                    "- For a lateral movement, you just have to press on the "
                    "hexagons that are useful for the movement.\n"
                    "- For a linear movement, you have to press twice on the "
                    "arrival hexagon.");
    helpMessage.exec();
}

void MainWindow::on_StopButton_clicked()
{
    QApplication::quit();
}

void MainWindow::on_restartButton_clicked()
{
    m_controller.initGame();
}
