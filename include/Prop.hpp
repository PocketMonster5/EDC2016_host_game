
#pragma once


#include <vector>

#include "Common.h"

class Prop {

public:

	Prop()
		: _waiting_count(0)
	{
	}

	// 如果道具需要刷新，返回true；否则返回false
	bool Refresh() {
		if (PropET == _prop) {
			++_waiting_count;
			if (_waiting_count >= PROP_CD) {
				_waiting_count = 0;
				return true;
			}
		}

		return false;
	}

	void Generate(std::vector<Point> avoid_point_list, int _map_size, double distance = 50) {
		// 产生一个道具，而且不能非常靠近传进来的几个点(小车,目标点什么的)
		for(int i=0;i<10;i++)
		{
			_point.x = _random.Rand() % _map_size;
			_point.y = _random.Rand() % _map_size;
			if (_point.getDistance(avoid_point_list[0]) >= distance && _point.getDistance(avoid_point_list[1]) >= distance && _point.getDistance(avoid_point_list[2]) >= distance)
				break;
		}

		// 隔一段时间会出现道具
		_prop = (PropType)(_random.Rand() % (PROP_SIZE - 1) + 1); // 避免0号NULL道具

		
	}

	bool CheckPoint(Point p) { //检查此点是否距离 _point 足够近
		return p.getDistance(_point) < PROP_DISTANCE;
	}

	inline Point getPoint() const { return _point; }
	inline PropType getPropType() const { return _prop; }

private:

	Point _point;
	PropType _prop;

	Random _random;

	int _waiting_count;

};