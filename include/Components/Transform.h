#ifndef _ROC_TRANSFORM_COMPONENT_H_
#define _ROC_TRANSFORM_COMPONENT_H_

#include "Component.h"

ROCKET_COMPONENT(Transform,
public:
    double x = 0, y = 0, z = 0;
);

#endif