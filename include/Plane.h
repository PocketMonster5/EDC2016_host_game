
#pragma once

#include "Common.h"

class Plane {
public:
    void Refresh(Point p, unsigned char color);//刷新飞机位置,根据Tower的颜色来决定飞机状态

    bool IsInAttackRange(Point p);
    bool IsInHealRange(Point p);

    PlaneStatus GetPlaneStatus();
    void Plane::SetPlaneStatus(unsigned char color);

    void Command();//以后再实现

private:
    Point _pos;
    PlaneStatus _status;
};