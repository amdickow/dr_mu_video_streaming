#ifndef IMAINCONTROLLER_H
#define IMAINCONTROLLER_H


class IMainController
{
public:

    virtual void Progress(double current, double total) = 0;

};

#endif // IMAINCONTROLLER_H
