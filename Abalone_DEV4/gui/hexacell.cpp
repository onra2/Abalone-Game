#include "hexacell.h"

#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QMainWindow>

#include <iostream>
#include <cmath>

#include "point.hpp"

double const HexaCell::zValMax = 10000;//arbitrary

bool HexaCell::getSelected() const
{
    return selected;
}

void HexaCell::unselect(){
    this->selected = false;
}

void HexaCell::setPlayer(int value)
{
    player = value;
}

int HexaCell::getPlayer()
{
    return this->player;
}

HexaCell::HexaCell(std::string ABAPROCoord, double rad, double dx, double dy, QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent), rad(rad), dx(dx), dy(dy), mouseover(false), selected(false), ABAPROCoord(ABAPROCoord)
{
    this->setAcceptHoverEvents(true);
    zval = zValue();

    static const double piOver6 = atan(1) * 4 / 6;

    QPolygonF polygon;
    auto&& corners = orbit({dx, dy}, 6, rad, piOver6);
    for(auto& p : corners)
        polygon << QPointF(p.first, p.second);

    setPolygon(polygon);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void HexaCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(selected)
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);

        if(this->getPlayer() == 1){//black player
            brush.setColor(Qt::black);
        }
        else if(this->getPlayer() == 2){//white player
            brush.setColor(Qt::white);
        }
        else {
            brush.setColor(Qt::lightGray);
        }

        QPen pen(Qt::red, 5);
        painter->setPen(pen);
        painter->setBrush(brush);
    }
    else if(mouseover)
    {
        QPen pen(Qt::black, 1);
        painter->setPen(pen);

        QBrush brush;
        brush.setColor(Qt::gray);
        brush.setStyle(Qt::SolidPattern);

        painter->setBrush(brush);
    }
    else
    {
        QBrush brush;
        Qt::GlobalColor c;

        if(this->getPlayer() == 1){
            brush.setColor(Qt::black);
            c = Qt::white;
        }
        else if(this->getPlayer() == 2){
            brush.setColor(Qt::white);
            c = Qt::black;
        }
        else {
            brush.setColor(Qt::lightGray);
            c = Qt::black;
        }
        brush.setStyle(Qt::SolidPattern);

        QPen pen(c, 1);
        painter->setPen(pen);

        painter->setBrush(brush);
    }

    painter->drawPolygon(polygon());
}

void HexaCell::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    mouseover = true;
    update();
}

void HexaCell::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mouseover = false;
    update();
}

void HexaCell::mousePressEvent(QGraphicsSceneMouseEvent * event)
{   
    selected = !selected; //I'd like to put this in "released"
    if(selected){
        notify("selectedHexaCell", &ABAPROCoord);
    }else{
        notify("unselectedHexaCell", &ABAPROCoord);
    }
    update();

    //relaunches the event in order to allow dragging
    QGraphicsItem::mousePressEvent(event);
}

void HexaCell::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //why isn't this ever fired ?
}

void HexaCell::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    notify("unselectAll", nullptr);
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void HexaCell::addObserver(iObserver * observer) {
    observers.push_back(observer);
}

void HexaCell::removeObserver(iObserver * observer) {
    observers.remove(observer);
}

void HexaCell::notify(std::string name, void * object) {
    for (iObserver * o : observers) {
        o->update(name, object);
    }
}


#pragma GCC diagnostic pop

