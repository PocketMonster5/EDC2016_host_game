
#pragma once

#include"Common.h"
#include"Car.h"
#include"Map.h"
#include"Plane.h"

//刷新所有（位置）
//道具
//血量计算
//判断游戏是否结束---运行，结束

class Round {


public:
    Round();

    void Refresh(const Point& p1, const Point& p2, const Point& pp);//刷新Plane, cars位置

    //Round 对外接口

    inline GameStatus GetGameStatus() const { return _game_status; }//返回比赛状态
    inline Point GetLocationProp() const { return _map.GetPropPos(); }//返回道具位置
    inline Point GetLocatinTower() const { return _map.GetFocus(); }//返回Tower位置
    inline unsigned char GetTowerColor() const { return _map.GetPointColor(_map.GetFocus()); }//返回目前Tower的颜色
    inline double GetHealthTower() const { return _map.GetTowerHealth(); }

    inline double GetCar_Health(CarName car_name) const { return _car[car_name].GetHealth(); }
    inline bool IfCar_LongAttackedByMap(CarName car_name) const { return _car[car_name].GetLongAttackMap(); }
    inline bool IfCar_ShortAttackedByMap(CarName car_name) const { return _car[car_name].GetShortAttackMap(); }
    inline bool IfCar_AttackedByMap(CarName car_name) const { return _car[car_name].GetAttackMap(); }
    inline bool IfCar_HealedByPlane(CarName car_name) const { return _car[car_name].GetHealPlane(); }
    inline bool IfCommandAircar(CarName car_name) const { return _car[Red].CommandAir(); }

private:
    Car _car[2];
    Plane _plane;
    Map _map;
    GameStatus _game_status;
    Random _random;

    //Round内部进行过程
    void ShortAttack(CarName car_name);//结算对此车的近攻
    void LongAttack(CarName car_name);//结算对此车的远攻
    void Attack(CarName car_name, bool critical);

    void CheckProp(Car& car_prop);//进行道具判断
    void SettleDamage();//伤害（加血）结算
    void RefreshTower();//对塔进行更新和维持
    void Judge();//回合结算

};
