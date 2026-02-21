#ifndef MODEL_HPP
#define MODEL_HPP
#include "main.h"

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
protected:
    ModelListener* modelListener;
       dashboard_t *r;
};

#endif // MODEL_HPP
