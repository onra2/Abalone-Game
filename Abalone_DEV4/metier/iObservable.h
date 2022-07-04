#ifndef IOBSERVABLE_H
#define IOBSERVABLE_H

#include "iObserver.h"
#include <string>

class iObservable{
public:
    virtual ~iObservable() {};

    /*!
     * \brief adds an observer to the list
     *
     *  \param observer an observer to add
     */
    virtual void addObserver(iObserver * observer) = 0;

    /*!
     * \brief removes an observer
     *
     *  \param observer an observer to remove
     */
    virtual void removeObserver(iObserver * observer) = 0;

    /*!
     * \brief notifies the obsers
     *
     *  \param name the option to notify
     *  \param object the object to send
     */
    virtual void notify(std::string name, void * object) = 0;
};

#endif // IOBSERVABLE_H
