#include <cmath>
#include <QPainter>
#include <QPointF>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QColor>
#include <QLabel>
#include <iostream>

#include "ghexacell.h"

GHexaCell::GHexaCell(double x, double y, Position position, Color color,
                     char line, QGraphicsPolygonItem * parent)
    : QGraphicsPolygonItem (parent), m_x { x }, m_y { y }, m_position { position },
      m_color { color }, m_line { line }
{
    static const double pi_over_6 = atan(1) * 4 / 6;
    static const double r = 40;

    QPolygonF polygon;
    polygon << QPointF(r * cos(pi_over_6), r * sin(pi_over_6));
    polygon << QPointF(0, r);
    polygon << QPointF(-r * cos(pi_over_6), r * sin(pi_over_6));
    polygon << QPointF(-r * cos(pi_over_6), -r * sin(pi_over_6));
    polygon << QPointF(0, -r);
    polygon << QPointF(r * cos(pi_over_6), -r * sin(pi_over_6));
    setPolygon(polygon);
}

void GHexaCell::paint(QPainter * painter,
                      [[maybe_unused]] const QStyleOptionGraphicsItem * option,
[[maybe_unused]] QWidget * widget)
{
    QPen pen(Qt::black, 1);
    painter->setPen(pen);
    QBrush brush;
    QColor brown(173, 105, 74);

    if (m_color == 0)
    {
        paintLabel(painter);
    } else {

        if (!m_selected)
        {
            brush.setColor(Qt::lightGray);
            brush.setStyle(Qt::SolidPattern);
        } else
        {
            brush.setColor(Qt::darkGray);
            brush.setStyle(Qt::SolidPattern);
        }

        painter->setBrush(brush);
        painter->drawPolygon(polygon());

        paintCircle(painter);
    }
}

void GHexaCell::paintCircle(QPainter * painter)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    if (m_color == Color::WHITE)
    {
        brush.setColor(Qt::white);
        painter->setBrush(brush);
        painter->drawEllipse(QPointF(0, 0), 25, 25);
    } else if (m_color == Color::BLACK)
    {
        brush.setColor(Qt::black);
        painter->setBrush(brush);
        painter->drawEllipse(QPointF(0, 0), 25, 25);
    }
}

void GHexaCell::paintLabel(QPainter * painter)
{
    QPen pen(Qt::white, 1);
    QBrush brush(Qt::white);

    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawPolygon(polygon());
    pen.setColor(Qt::black);
    painter->setPen(pen);
    painter->setFont(QFont("Verdana", 20, QFont::Bold));
    painter->drawText(-5, 10, QString(m_line));
}

void GHexaCell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    m_selected = true;
    update();
    emit sendValue(m_position);
}
