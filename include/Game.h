/*
 * 游戏逻辑
 */

#pragma once
#include<fstream>

#include"Common.h"
#include"Car.hpp"
#include"Map.hpp"
#include"Plane.hpp"
#include"Prop.hpp"
#include"GameData.h"

//刷新所有（位置）
//道具
//血量计算
//判断游戏是否结束

class Game {


public:
    Game(std::string filename = "./data/test.txt");

    void Refresh(const Point& p1, const Point& p2, const Point& pp);//刷新Plane, cars位置

	GameData getGameData(); 

    //Game 对外接口

    inline GameStatus GetGameStatus() const { return _game_status; }//返回比赛状态
	inline Point GetLocationProp() const { return _prop.getPoint(); }//返回道具位置
    inline Point GetLocatinTower() const { return _map.GetTargetPoint(); }//返回Tower位置
    inline unsigned char GetTowerColor() const { return _map.GetPointColor(_map.GetTargetPoint()); }//返回目前Tower的颜色
    inline double GetHealthTower() const { return _map.GetTargetHealth(); }
    inline int GetRoundCount() const { return _round_count; } // 获取当前回合

    inline double GetCarHealth(CarName car_name) const { return _car[car_name].GetHealth(); }
    inline bool IfCarLongAttackedByMap(CarName car_name) const { return _car[car_name].GetLongAttackMap(); }
    inline bool IfCarShortAttackedByMap(CarName car_name) const { return _car[car_name].GetShortAttackMap(); }
    inline bool IfCarAttackedByMap(CarName car_name) const { return _car[car_name].GetAttackMap(); }
    inline bool IfCarHealedByPlane(CarName car_name) const { return _car[car_name].GetHealPlane(); }
    inline bool IfCommandAircar(CarName car_name) const { return _car[Red].CommandAir(); }


	
private:
	std::ofstream out_file;
	Car _car[2];    //两辆小车
    Plane _plane;   //飞机
    Map _map;       //地图
    GameStatus _game_status;    //游戏状态
	Prop _prop;
	
	Random _random; //随机数

    int _round_count; //当前回合数

    //Game内部进行过程
    void ShortAttack(CarName car_name);//结算对此车的近攻
    void LongAttack(CarName car_name); //结算对此车的远攻
    void Attack(CarName car_name, bool critical); //结算对此车的远/近攻

    void CheckProp(Car& car_prop);//进行道具判断
    void SettleDamage();//伤害（加血）结算
    //void GenerateTarget();//对塔进行更新和维持
	void GenerateProp();
    void Judge();//回合结算 

};
