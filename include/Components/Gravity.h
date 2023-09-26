#ifndef _ROC_GRAVITY_COMPONENT_H_
#define _ROC_GRAVITY_COMPONENT_H_

#include "Component.h"

ROCKET_COMPONENT(Gravity,
public:
    double acceleration = 9.81;
);

#endif