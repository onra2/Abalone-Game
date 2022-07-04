#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <string>

class iObserver{
public:
    virtual ~iObserver() {};

    /*!
     * \brief updates all observers
     *
     *  \param name option to apply
     *  \param object the object from the observable
     */
    virtual void update(std::string name, void * object) = 0;
};

#endif // IOBSERVER_H
