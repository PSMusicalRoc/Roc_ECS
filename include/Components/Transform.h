#ifndef _ROC_TRANSFORM_COMPONENT_H_
#define _ROC_TRANSFORM_COMPONENT_H_

#include "Component.h"

ROCKET_COMPONENT(Transform,
    ROCKET_PROPERTY_DEFVAL(public, double, x, 0)
    ROCKET_PROPERTY_DEFVAL(public, double, y, 0)
    ROCKET_PROPERTY_DEFVAL(public, double, z, 0)
);

#endif