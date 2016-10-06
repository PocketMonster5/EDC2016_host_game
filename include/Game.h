/*
 * ��Ϸ�߼�
 */

#pragma once
#include<fstream>

#include"Common.h"
#include"Car.hpp"
#include"Map.hpp"
#include"Plane.hpp"
#include"Prop.hpp"
#include"GameData.h"

//ˢ�����У�λ�ã�
//����
//Ѫ������
//�ж���Ϸ�Ƿ����

class Game {


public:
    Game(std::string filename = "./data/test.txt");

    void Refresh(const Point& p1, const Point& p2, const Point& pp);//ˢ��Plane, carsλ��

	GameData getGameData(); 

    //Game ����ӿ�

    inline GameStatus GetGameStatus() const { return _game_status; }//���ر���״̬
	inline Point GetLocationProp() const { return _prop.getPoint(); }//���ص���λ��
    inline Point GetLocatinTower() const { return _map.GetTargetPoint(); }//����Towerλ��
    inline unsigned char GetTowerColor() const { return _map.GetPointColor(_map.GetTargetPoint()); }//����ĿǰTower����ɫ
    inline double GetHealthTower() const { return _map.GetTargetHealth(); }
    inline int GetRoundCount() const { return _round_count; } // ��ȡ��ǰ�غ�

    inline double GetCarHealth(CarName car_name) const { return _car[car_name].GetHealth(); }
    inline bool IfCarLongAttackedByMap(CarName car_name) const { return _car[car_name].GetLongAttackMap(); }
    inline bool IfCarShortAttackedByMap(CarName car_name) const { return _car[car_name].GetShortAttackMap(); }
    inline bool IfCarAttackedByMap(CarName car_name) const { return _car[car_name].GetAttackMap(); }
    inline bool IfCarHealedByPlane(CarName car_name) const { return _car[car_name].GetHealPlane(); }
    inline bool IfCommandAircar(CarName car_name) const { return _car[Red].CommandAir(); }


	
private:
	std::ofstream out_file;
	Car _car[2];    //����С��
    Plane _plane;   //�ɻ�
    Map _map;       //��ͼ
    GameStatus _game_status;    //��Ϸ״̬
	Prop _prop;
	
	Random _random; //�����

    int _round_count; //��ǰ�غ���

    //Game�ڲ����й���
    void ShortAttack(CarName car_name);//����Դ˳��Ľ���
    void LongAttack(CarName car_name); //����Դ˳���Զ��
    void Attack(CarName car_name, bool critical); //����Դ˳���Զ/����

    void CheckProp(Car& car_prop);//���е����ж�
    void SettleDamage();//�˺�����Ѫ������
    //void GenerateTarget();//�������и��º�ά��
	void GenerateProp();
    void Judge();//�غϽ��� 

};
