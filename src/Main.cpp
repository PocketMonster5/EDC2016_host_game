// Created by cyx15 & ty15, 2016.9


#include"Game.h"

using namespace std;

int TargetSuspend = 0;  //TODO 移动到合适的位置
bool IsTarget = false; //TODO

int test_Map() {
    Map map("./data/test.txt");

    // Refresh Target Test
    for (int i = 0; i < 20; ++i) {
        map.RefreshTarget();
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
    Point p_plane(30, 140);//构造飞机位置篇p_plane
    Point p_plane2(50, 80); //飞机位置2

    //测试开始
    plane_test.Refresh(p_plane, 0); cout << "当前位置 30，140" << endl;
    cout << "PlaneStatus is:" << plane_test.GetPlaneStatus() << endl;//测试设定飞机状态
    cout << "p1 is in the AttackRange ? " << plane_test.IsInAttackRange(p1) << endl;
    cout << "p2 is in the AttackRange ? " << plane_test.IsInAttackRange(p2) << endl;//测试攻击范围判定
    cout << "p1 is in the HealRange   ? " << plane_test.IsInHealRange(p1) << endl;
    cout << "p2 is in the HealRange   ? " << plane_test.IsInHealRange(p2) << endl;//测试治疗范围判定
    cout << endl << endl;

    plane_test.Refresh(p_plane2, 255); cout << "当前位置 70，200" << endl;
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

int test_Game()
{
    Game game;
    
    for (int i = 0; i < 15; ++i) {
        cout << "Round " << game.GetRoundCount() << endl;
        game.Refresh(Point(0, 0), Point(0, 0), Point(0, 0));
    }

    system("pause");
    return 0;
}

int main() {

    cout << "======= <test> Map =========" << endl;
    test_Map();

    cout << "======= <test> Plane =========" << endl;
    test_Plane();

    cout << "======= <test> Car =========" << endl;
    test_Car();

    cout << "======= <test> Game =========" << endl;
    test_Game();

    return 0;
}
