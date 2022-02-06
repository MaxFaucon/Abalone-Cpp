#ifndef GHEXACELL_H
#define GHEXACELL_H

#include <QObject>
#include <QGraphicsPolygonItem>
#include <QGraphicsEllipseItem>

#include "model/position.h"
#include "model/color.h"

/**
 * @brief The GHexaCell class Represents an hexagon.
 */
class GHexaCell : public QObject, public QGraphicsPolygonItem
{

    Q_OBJECT

protected:
    double m_x, m_y;
    Position m_position;
    Color m_color;
    bool m_selected = false;
    char m_line;

public:
    /**
     * @brief GHexaCell Constructor of GHexacell.
     * @param x The position of the hexagon on the x-axis.
     * @param y The position of the hexagon on the y-axis.
     * @param position The position of the hexagon according to the game board.
     * @param color The color of the hexagon.
     * @param line The line of the hexagon on the board.
     * @param parent The parent of this class which is the class that represents
     * a polygon.
     */
    explicit GHexaCell(double x, double y, Position position, Color color,
                       char line, QGraphicsPolygonItem * parent = nullptr);

    /**
     * @brief x Getter of x.
     * @return The position of the hexagon on the x-axis.
     */
    inline double x() const;

    /**
     * @brief y Getter of y.
     * @return The position of the hexagon on the y-axis.
     */
    inline double y() const;

    /**
     * @brief position Getter of position
     * @return The position of the hexagon according to the game board.
     */
    inline Position position() const;

    /**
     * @brief color Getter of color.
     * @return The color of the hexagon.
     */
    inline Color color() const;

    /**
     * @brief color Setter of color.
     * @param Color The color of the hexagon.
     */
    inline void color(Color Color);

    /**
     * @brief selected Getter of selected.
     * @return True if the hexagon is selected, false otherwise.
     */
    inline bool selected() const;

    /**
     * @brief selected Setter of selected.
     * @param selected True if the hexagon is selected, false otherwise.
     */
    inline void selected(bool selected);

    /**
     * @brief line Getter of line.
     * @return The line of the hexagon on the board.
     */
    inline char line() const;

    /**
     * @brief paint Paints the hexagon.
     * @param painter The painter.
     * @param option The options to paint.
     * @param widget The widget.
     */
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);    

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

private:
    /**
     * @brief paintCircle Paints a circle on the hexagon if the color of the
     * hexagon isn't null.
     * @param painter The painter.
     */
    void paintCircle(QPainter * painter);

    /**
     * @brief paintLabel Paints the labels around the board.
     * @param painter The painter.
     */
    void paintLabel(QPainter * painter);

signals:
    /**
     * @brief sendValue Signal that send the position.
     * @param position The position of the hexagon according to the game board.
     */
    void sendValue(Position position);

};

double GHexaCell::x() const
{
    return m_x;
}

double GHexaCell::y() const
{
    return m_y;
}

Position GHexaCell::position() const
{
    return m_position;
}

Color GHexaCell::color() const
{
    return m_color;
}

void GHexaCell::color(Color color)
{
    m_color = color;
}

bool GHexaCell::selected() const
{
    return m_selected;
}

void GHexaCell::selected(bool selected)
{
    m_selected = selected;
}

char GHexaCell::line() const
{
    return m_line;
}

#endif // GHEXACELL_H
