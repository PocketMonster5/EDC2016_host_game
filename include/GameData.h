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
        char buffer[512];
        sprintf(buffer, " [ HP %.1lf pos (%d,%d) color %d A L%d S%d PA%d PH%d AC%d(%d) ] ",
            _health, _pos.x, _pos.y, _color, 
            _long_attack_map, _short_attack_map, 
            _attack_plane, _heal_plane, 
            _air_command, _count_air_command);
        return buffer;
        // return all data
    }

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


    //目标点信息
    double targetHealth;//生命值
    Point target_pos; //目标点位置

    //地图动态信息
    Point _prop_pos;//道具所在位置
    PropType _prop; // 道具类型

    std::string getString() {

        char buffer[512];
        sprintf(buffer, " round %d : target (%d,%d) %.1lf ; plane (%d,%d) %d ; prop (%d,%d) %d ; ",
            _round,
            target_pos.x, target_pos.y, targetHealth,
            planePos.x, planePos.y, planeStatus,
            _prop_pos.x, _prop_pos.y, _prop);
        return (buffer + carData[Red].getString() + carData[Blue].getString());
        // ( call carData.getString()) and return all data 
    }

	MyString getComunicationString() {
		char s[20] = "TEST COMMUNICATION";
		return MyString(s, 20);
		// TODO IT LATER
	}
};

