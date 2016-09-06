
#pragma once

#include"Common.h"

class Tower {
public:
    void Reset() { _health = TOWER_HEALTH; }//生命值置满

    double GetHealth() const { return _health; }//返回血量

    void ShortAttack() { _health -= SHORT_ATTACK; }//近战减血
    void LongAttack() { _health -= LONG_ATTACK; }//远战减血
private:
    double _health;//生命值
};