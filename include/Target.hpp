

#pragma once

#include"Common.h"

class Target {
public:
    void Reset() { _health = TARGET_HEALTH; }//生命值置满

    double GetHealth() const { return _health; }//返回血量

    void ShortAttack() { _health -= SHORT_ATTACK; }//近战减血
    void LongAttack() { _health -= LONG_ATTACK; }//远战减血
    void Attack(bool critical) { //远/近减血
        if (critical) ShortAttack(); else LongAttack();
    }
private:
    double _health;//生命值
};