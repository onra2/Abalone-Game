#ifndef HEXACELL_H
#define HEXACELL_H

#include <QGraphicsPolygonItem>
#include <QPolygonF>
#include <string>
#include <QPointF>
#include <QMouseEvent>
#include "iObservable.h"

class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QGraphicsSceneHoverEvent;
class QGraphicsSceneMouseEvent;
class QGraphicsSceneWheelEvent;

class HexaCell : public QGraphicsPolygonItem, iObservable
{
    static const double zValMax; //z-val of selected items
    double zval; //z-val at instanciation

    /*!
     * \brief The observers list
     */
    std::list<iObserver *> observers;

    protected:
        double rad, dx, dy;//hexagon radius, coordinate (x,y) of center
        bool mouseover, selected;//mouse interaction booleans
        int player;
        std::string ABAPROCoord;

        void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
        void mousePressEvent(QGraphicsSceneMouseEvent * event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);

    public:
        HexaCell(std::string ABAPROCoord, double rad = 100, double dx = 0, double dy = 0, QGraphicsItem * parent = 0);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        inline QPointF coord(double x, double y) const;

        inline void setLocation(double x, double y);

        bool getSelected() const;
        void unselect();

        void setPlayer(int value);
        int getPlayer();

        /*!
         * \brief Add a observer on HexaCell
         * \param observer the observer to add
         */
        virtual void addObserver(iObserver * observer);

        /*!
         * \brief Remove a observer on HexaCell
         * \param observer the observer to remove
         */
        virtual void removeObserver(iObserver * observer);

        /*!
         * \brief Notify all observer
         */
        virtual void notify(std::string name, void * object);
};

#endif // HEXACELL_H
