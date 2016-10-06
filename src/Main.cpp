// Created by cyx15 & ty15, 2016.9


#include"Game.h"
#include"Random.hpp"

using namespace std;

int test_Map() {
    Map map("./data/test.txt");

    // Refresh Target Test
    for (int i = 0; i < 20; ++i) {
        map.GenerateTarget();
        Point p = map.GetTargetPoint();
        cout << "tid (" << int(p.x) << ", " << int(p.y) << ")" << (int)map.GetPointColor(p) << endl;
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
    cout << "p1 is in the AttackRange  " << plane_test.IsInAttackRange(p1) << endl;
    cout << "p2 is in the AttackRange  " << plane_test.IsInAttackRange(p2) << endl;//测试攻击范围判定
    cout << "p1 is in the HealRange    " << plane_test.IsInHealRange(p1) << endl;
    cout << "p2 is in the HealRange    " << plane_test.IsInHealRange(p2) << endl;//测试治疗范围判定
    cout << endl << endl;

    plane_test.Refresh(p_plane2, 255); cout << "当前位置 70，200" << endl;
    cout << "PlaneStatus is:" << plane_test.GetPlaneStatus() << endl;//测试设定飞机状态
    cout << "p1 is in the AttackRange  " << plane_test.IsInAttackRange(p1) << endl;
    cout << "p2 is in the AttackRange  " << plane_test.IsInAttackRange(p2) << endl;//测试攻击范围判定
    cout << "p1 is in the HealRang     " << plane_test.IsInHealRange(p1) << endl;
    cout << "p2 is in the HealRang     " << plane_test.IsInHealRange(p2) << endl;//测试治疗范围判定
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
    Game game("./data/test.txt");
    Random random;

    int size = game.GetMapSize();

    Point p1(random.Rand() % size, random.Rand() % size);    
    Point p2(random.Rand() % size, random.Rand() % size);
    Point pp(random.Rand() % size, random.Rand() % size);

    Point t;

    for (int i = 0; i < 1800; ++i) {

        t = game.GetTargetPoint();

        p1.x += random.Rand() % 10 - 5; p1.y += random.Rand() % 10 - 5;
        if (p1.x > t.x) p1.x -= 5; else p1.x += 5;
        if (p1.y > t.y) p1.y -= 5; else p1.y += 5;

        p2.x += random.Rand() % 10 - 5; p2.y += random.Rand() % 10 - 5;
        if (p2.x > t.x) p1.x -= 5; else p2.x += 5;
        if (p2.y > t.y) p1.y -= 5; else p2.y += 5;

        pp.x += random.Rand() % 10 - 5; pp.y += random.Rand() % 10 - 5;

        game.Refresh(p1, p2, pp);

		cout << game.getGameData().getString() << endl;

        if (game.GetGameStatus() != Running) break;
    }

    system("pause");
    return 0;
}

int main() {

    /*cout << "======= <test> Map =========" << endl;
    test_Map();

    cout << "======= <test> Plane =========" << endl;
    test_Plane();

    cout << "======= <test> Car =========" << endl;
    test_Car();*/

    cout << "======= <test> Game =========" << endl;
    test_Game();

    return 0;
}
