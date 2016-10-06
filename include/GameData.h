#pragma once

#include <string>


#include "Common.h"
#include "my_string.hpp"

struct CarData
{
    //小车信息
    double _health;//血量
    Point _pos;//位置
    unsigned char _color;//小车所在点的颜色，即黑白
    bool _long_attack_map;//是否被地图小攻击
    bool _short_attack_map;//是否被地图大攻击
    bool _attack_plane;//是否被飞机攻击
    bool _heal_plane;//是否被飞机加血
    bool _air_command;//是否有制空权
    int _count_air_command;//记录制空权回合数

	std::string getString() {
		char Out[50];
		sprintf(Out, "%f (%d,%d) %c %d %d %d %d %d %d", _health,_pos.x,_pos.y,_color,_long_attack_map,_short_attack_map,_attack_plane,_heal_plane,_air_command,_count_air_command);
		return Out;
		// return all data
	};

};


struct GameData
{
    //回合数
    int _round;
    //小车信息
    CarData carData[2];//对象采用camel命名

    //飞机信息
    Point planePos;
    PlaneStatus planeStatus;


    //塔信息
    double targetHealth;//生命值

    //地图动态信息
    Point _prop_pos;//道具所在位置
    PropType _prop; // 道具类型

	std::string getString() {

		char Out[50];
		sprintf(Out, "%d (%d,%d) %d %f (%d,%d) %d ", _round, planePos.x, planePos.y, planeStatus, targetHealth, _prop_pos.x, _prop_pos.y, _prop);
		return (Out + carData[Red].getString() + carData[Blue].getString()+'\n');
		// ( call carData.getString()) and return all data 
	}

	MyString getComunicationString() {
		char s[20] = "TEST COMMUNICATION";
		return MyString(s, 20);
		// TODO IT LATER
	}
};

