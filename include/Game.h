/*
 * ��Ϸ�߼�
 */

#pragma once

#include"Common.h"
#include"Car.hpp"
#include"Map.hpp"
#include"Plane.hpp"

//ˢ�����У�λ�ã�
//����
//Ѫ������
//�ж���Ϸ�Ƿ����

class Game {


public:
    Game(std::string filename = "./data/test.txt");

    void Refresh(const Point& p1, const Point& p2, const Point& pp);//ˢ��Plane, carsλ��

    //Game ����ӿ�

    inline GameStatus GetGameStatus() const { return _game_status; }//���ر���״̬
    inline Point GetLocationProp() const { return _map.GetPropPos(); }//���ص���λ��
    inline Point GetLocatinTower() const { return _map.GetFocus(); }//����Towerλ��
    inline unsigned char GetTowerColor() const { return _map.GetPointColor(_map.GetFocus()); }//����ĿǰTower����ɫ
    inline double GetHealthTower() const { return _map.GetTowerHealth(); }
    inline int GetRoundCount() const { return _round_count; } // ��ȡ��ǰ�غ�

    inline double GetCar_Health(CarName car_name) const { return _car[car_name].GetHealth(); }
    inline bool IfCar_LongAttackedByMap(CarName car_name) const { return _car[car_name].GetLongAttackMap(); }
    inline bool IfCar_ShortAttackedByMap(CarName car_name) const { return _car[car_name].GetShortAttackMap(); }
    inline bool IfCar_AttackedByMap(CarName car_name) const { return _car[car_name].GetAttackMap(); }
    inline bool IfCar_HealedByPlane(CarName car_name) const { return _car[car_name].GetHealPlane(); }
    inline bool IfCommandAircar(CarName car_name) const { return _car[Red].CommandAir(); }

private:
    Car _car[2];    //����С��
    Plane _plane;   //�ɻ�
    Map _map;       //��ͼ
    GameStatus _game_status;    //��Ϸ״̬
    Random _random; //�����

    int _round_count; //��ǰ�غ���

    //Game�ڲ����й���
    void ShortAttack(CarName car_name);//����Դ˳��Ľ���
    void LongAttack(CarName car_name); //����Դ˳���Զ��
    void Attack(CarName car_name, bool critical); //����Դ˳���Զ/����

    void CheckProp(Car& car_prop);//���е����ж�
    void SettleDamage();//�˺�����Ѫ������
    void RefreshTower();//�������и��º�ά��
    void Judge();//�غϽ���

};
