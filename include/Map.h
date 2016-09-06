
#pragma once

#include"Common.h"
#include"Tower.hpp"

class Map {
public:
    Map(std::string Filename);//constructor

    void RefreshTower(bool reverse = false);//更换塔，reverse代表是否因为BW道具强制换色
    void RefreshProp(); //更新道具，修改_prop和_prop_pos
    void ConsumeProp(); //消耗道具

    void ShortAttack();//塔近攻
    void LongAttack();//塔远攻
    void Attack(bool critical);

    inline unsigned char GetPointColor(const Point& p) const { return _map[int(p.x)][int(p.y)]; }//return 0 or 255 in the map
    inline Point GetFocus() const { return _targets[_focus]; }//return _focus
    inline double GetTowerHealth() const { return _tower.GetHealth(); }//return 塔的血量
    inline Point Map::GetPropPos() const { return _prop_pos; }//return 道具位置
    inline Prop Map::GetProp() const { return _prop; }// return 道具类型

private:

    void RefreshFocus(bool reverse = false);//更换争抢点，reverse代表是否强制换色

    int _map_size;
    unsigned char _map[256][256];

    std::vector<Point> _targets; //目标点
    int _targets_size; //目标点总数
    int _focus; //当前目标点
    Tower _tower;//塔

    Point _prop_pos;//道具所在位置
    Prop _prop; // 道具类型

    Random _random;


};
