// Created by cyx15 & ty15, 2016.9

#include<iostream>
#include<string>
#include"Common.h"
#include"Map.h"
#include"Car.h"
#include"Plane.h"

using namespace std;

int RoundCount = 0;
int TowerSuspend = 0;

bool IsTower = false;
bool Reverse = false;

int test_Map();
int test_Plane();
int test_Car();
int test_Round();

int main() {

    cout << "======= <test> Map =========" << endl;
    test_Map();

    cout << "======= <test> Plane =========" << endl;
    test_Plane();

    cout << "======= <test> car =========" << endl;
    test_Car();

    return 0;
}


int test_Map() {
    Map map("./data/test.txt");

    // Refresh Tower Test
    for (int i = 0; i < 20; ++i) {
        map.RefreshTower();
        Point p = map.GetFocus();
        cout << "Focus (" << int(p.x) << ", " << int(p.y) << ")" << (int)map.GetPointColor(p) << endl;
    }

    // Refresh Prop Test
    for (int i = 0; i < 20; ++i)
    {
        map.RefreshProp();
        Point p = map.GetPropPos();
        Prop pr = map.GetProp();
        cout << "The prop is at: " << "(" << int(p.x) << ", " << int(p.y) << ") " << pr << endl;
    }

    system("pause");
    return 0;
}


int test_Plane()
{

    Point p1(30, 100);//构造小车1
    Point p2(70, 200);//构造小车2

    Plane plane_test;
    Point p_plane(30, 140); p_plane.x = 30; p_plane.y = 140;//构造飞机位置篇p_plane
    Point p_plane2(50, 80); //飞机位置2

    //测试开始
    //cout<<"目前为止 30，140"<<endl;
    plane_test.Refresh(p_plane, 0);
    cout << "PlaneStatus is:" << plane_test.GetPlaneStatus() << endl;//测试设定飞机状态
    cout << "p1 is in the AttackRange ? " << plane_test.IsInAttackRange(p1) << endl;
    cout << "p2 is in the AttackRange ? " << plane_test.IsInAttackRange(p2) << endl;//测试攻击范围判定
    cout << "p1 is in the HealRange   ? " << plane_test.IsInHealRange(p1) << endl;
    cout << "p2 is in the HealRange   ? " << plane_test.IsInHealRange(p2) << endl;//测试治疗范围判定
    cout << endl << endl;
    //cout<<"目前为止 70，200"<<endl;
    plane_test.Refresh(p_plane2, 255);
    cout << "PlaneStatus is:" << plane_test.GetPlaneStatus() << endl;//测试设定飞机状态
    cout << "p1 is in the AttackRange ? " << plane_test.IsInAttackRange(p1) << endl;
    cout << "p2 is in the AttackRange ? " << plane_test.IsInAttackRange(p2) << endl;//测试攻击范围判定
    cout << "p1 is in the HealRang    ? " << plane_test.IsInHealRange(p1) << endl;
    cout << "p2 is in the HealRang    ? " << plane_test.IsInHealRange(p2) << endl;//测试治疗范围判定
    system("pause");
    return 0;
}


int test_Car()
{
    Car car_test;
    Point p1(30, 100);//构造小车位置1
    Point p2(70, 200);//构造小车位置2
    car_test.ResetCar();//初始化小车

    car_test.Refresh(p1, 0);//设置到位置1，黑色
    car_test.LongAttackedByMap();//被地图小攻击
    car_test.AttackedByPlane();//被飞机攻击
    cout << car_test.GetHealth() << " " << car_test.GetLongAttackMap() << " " << car_test.GetShortAttackMap() << " " << car_test.GetAttackPlane() << " " << car_test.GetHealPlane() << " " << car_test.CommandAir() << endl;//显示状态

    car_test.Refresh(p2, 255);//设置到位置2，白色
    car_test.ShortAttackedByMap();//被地图大攻击
    car_test.HealedByPlane();//被飞机治疗
    cout << car_test.GetHealth() << " " << car_test.GetLongAttackMap() << " " << car_test.GetShortAttackMap() << " " << car_test.GetAttackPlane() << " " << car_test.GetHealPlane() << " " << car_test.CommandAir() << endl;//显示状态

    car_test.Refresh(p1, 0);//回到位置1，黑色
    car_test.AcquireAirCommand();//获取制空权
    cout << car_test.GetHealth() << " " << car_test.GetLongAttackMap() << " " << car_test.GetShortAttackMap() << " " << car_test.GetAttackPlane() << " " << car_test.GetHealPlane() << " " << car_test.CommandAir() << endl;//显示状态

    //停留在位置1，黑色
    for (int i = 0; i < 5; ++i) {
        car_test.Refresh(p1, 0);
        cout << car_test.GetHealth() << " " << car_test.GetLongAttackMap() << " " << car_test.GetShortAttackMap() << " " << car_test.GetAttackPlane() << " " << car_test.GetHealPlane() << " " << car_test.CommandAir() << endl;//显示状态
    }

    system("pause");
    return 0;
}

int test_Round()
{

    return 0;
}