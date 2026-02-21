#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }
    virtual void rpm(int data)=0;
    virtual void speed(int data)=0;
    virtual void soc(int data)=0;
    virtual void battery1(battery_t data)=0;
    virtual void motor(motor_t data)=0;
    virtual void target(target_t data)=0;
    virtual void time(char *data)=0;
    virtual void gpsspeed(int data)=0;
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
