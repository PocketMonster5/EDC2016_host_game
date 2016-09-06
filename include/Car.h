
#pragma once

#include"Common.h"
class Car {
public:

    void Refresh(Point p, unsigned char c);//修改当前位置；将和血量相关的三个布尔型状态设为false；检查制空权回合数

    void LongAttackedByMap();//地图小攻击，减血+改状态
    void ShortAttackedByMap();//地图大攻击
    void AttackedByMap(bool critical); 

    void AttackedByPlane();//飞机攻击

    void HealedByPlane();//飞机加血
    void HealByProp();//道具加血

    void AcquireAirCommand();//获得制空权，持续一定回合数
    void DismissAirCommand();//解除制空权，清空count

    inline bool IsAlive() { return (_health >= DEATH_BlOOD); }//是否存活
    inline bool CommandAir() const { return _air_command; }//是否有制空权

    inline Point GetPoint() const { return this->_pos; }//返回小车位置
    inline double GetHealth() const { return _health; }//返回血量(补充）
    inline bool GetLongAttackMap() const { return _long_attack_map; }//返回是否被地图小攻击(补充）
    inline bool GetShortAttackMap() const { return _short_attack_map; }//返回是否被地图小攻击(补充）
    inline bool GetAttackMap() const {  return _long_attack_map || _short_attack_map; } //返回是否被地图攻击
    inline bool GetAttackPlane() const { return _attack_plane; }//返回是否被飞机攻击(补充）
    inline bool GetHealPlane() const { return _heal_plane; }//返回是否被飞机加血(补充）

    void ResetCar();//初始化小车：生命、制空回合（补充）

private:
    double _health;//血量
    Point _pos;//位置
    unsigned char _color;//小车所在点的颜色，即黑白

    bool _long_attack_map;//是否被地图小攻击
    bool _short_attack_map;//是否被地图大攻击
    bool _attack_plane;//是否被飞机攻击
    bool _heal_plane;//是否被飞机加血

    bool _air_command;//是否有制空权
    int _count_air_command;//记录制空权回合数

};
