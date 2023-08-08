#ifndef _ROC_GRAVITY_COMPONENT_H_
#define _ROC_GRAVITY_COMPONENT_H_

#include "Component.h"

struct Gravity : public Component
{
    double acceleration = 9.81;
};

#endif