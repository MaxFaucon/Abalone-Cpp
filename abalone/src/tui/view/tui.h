#ifndef TUI_H
#define TUI_H

#include <vector>

#include "model/game.h"

class Subject;

/**
 * @brief The Tui class View of the game. Manages the user interface and
 * the user inputs. Observer of the model.
 */
class Tui: public Observer
{

public:
    /**
     * @brief Tui Constructor of Tui. Add the tui as an observer of a subject.
     * @param source The subject to observe.
     */
    Tui(Game & source) : m_game { source }
    {        
        source.addObserver(this);            
    }

    /**
     * @brief Virtual method that each observer must implement. It's this
     * method that the observed subject calls when there is a notification.
     * @param propertyName A string that allows the observer to know what
     * has been modified in the subject.
     */
    virtual void update(const std::string & propertyName) override;

    virtual ~Tui() = default;

    /**
     * @brief displayBoard Displays the game board.
     * @param board The game board.
     */
    void displayBoard(Board board);

    /**
     * @brief displayEjectedMarblesCount Displays the number of marbles that the
     * current player has ejected.
     * @param currentPlayer The current player.
     */
    void displayEjectedMarblesCount(const Player* currentPlayer, char color);

private:
    /**
     * @brief displayLineElements Displays the hexagons of a line.
     * @param line A line of the board.
     * @param board The game board.
     */
    std::string displayLineElements(int line, Board board);       

private:
    Game & m_game;
};

#endif // TUI_H
