

#pragma once

#include"Common.h"

class Target {
public:

    void Reset() { //生命值置满
		_health = TARGET_HEALTH; 
		_waiting_count = 0;
		_alive = true;
	}

	bool Refresh() { 
		if (!_alive) {
			++_waiting_count;
			if (_waiting_count >= TARGET_CD) {
				_waiting_count = 0;
				return true;
			}
		}
		return false;
	} //refresh

    void ShortAttack() { _health -= SHORT_ATTACK; }//近战减血
    void LongAttack() { _health -= LONG_ATTACK; }//远战减血
    void Attack(bool critical) { if (critical) ShortAttack(); else LongAttack(); } //远/近减血

	inline double GetHealth() const { return _health; }//返回血量
	inline bool isAlive() const { return _alive;  }

private:

	
    double _health;//生命值

	bool _alive;

	int _waiting_count;

};