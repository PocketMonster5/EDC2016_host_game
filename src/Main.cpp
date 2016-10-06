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

    Point p1(30, 100);//����С��1
    Point p2(70, 200);//����С��2

    Plane plane_test;
    Point p_plane(30, 140);//����ɻ�λ��ƪp_plane
    Point p_plane2(50, 80); //�ɻ�λ��2

    //���Կ�ʼ
    plane_test.Refresh(p_plane, 0); cout << "��ǰλ�� 30��140" << endl;
    cout << "PlaneStatus is:" << plane_test.GetPlaneStatus() << endl;//�����趨�ɻ�״̬
    cout << "p1 is in the AttackRange  " << plane_test.IsInAttackRange(p1) << endl;
    cout << "p2 is in the AttackRange  " << plane_test.IsInAttackRange(p2) << endl;//���Թ�����Χ�ж�
    cout << "p1 is in the HealRange    " << plane_test.IsInHealRange(p1) << endl;
    cout << "p2 is in the HealRange    " << plane_test.IsInHealRange(p2) << endl;//�������Ʒ�Χ�ж�
    cout << endl << endl;

    plane_test.Refresh(p_plane2, 255); cout << "��ǰλ�� 70��200" << endl;
    cout << "PlaneStatus is:" << plane_test.GetPlaneStatus() << endl;//�����趨�ɻ�״̬
    cout << "p1 is in the AttackRange  " << plane_test.IsInAttackRange(p1) << endl;
    cout << "p2 is in the AttackRange  " << plane_test.IsInAttackRange(p2) << endl;//���Թ�����Χ�ж�
    cout << "p1 is in the HealRang     " << plane_test.IsInHealRange(p1) << endl;
    cout << "p2 is in the HealRang     " << plane_test.IsInHealRange(p2) << endl;//�������Ʒ�Χ�ж�
    system("pause");
    return 0;
}

int test_Car()
{
    Car car_test;
    Point p1(30, 100);//����С��λ��1
    Point p2(70, 200);//����С��λ��2
    car_test.ResetCar();//��ʼ��С��

    car_test.Refresh(p1, 0);//���õ�λ��1����ɫ
    car_test.LongAttackedByMap();//����ͼС����
    car_test.AttackedByPlane();//���ɻ�����
    cout << car_test.GetHealth() << " " << car_test.GetLongAttackMap() << " " << car_test.GetShortAttackMap() << " " << car_test.GetAttackPlane() << " " << car_test.GetHealPlane() << " " << car_test.CommandAir() << endl;//��ʾ״̬

    car_test.Refresh(p2, 255);//���õ�λ��2����ɫ
    car_test.ShortAttackedByMap();//����ͼ�󹥻�
    car_test.HealedByPlane();//���ɻ�����
    cout << car_test.GetHealth() << " " << car_test.GetLongAttackMap() << " " << car_test.GetShortAttackMap() << " " << car_test.GetAttackPlane() << " " << car_test.GetHealPlane() << " " << car_test.CommandAir() << endl;//��ʾ״̬

    car_test.Refresh(p1, 0);//�ص�λ��1����ɫ
    car_test.AcquireAirCommand();//��ȡ�ƿ�Ȩ
    cout << car_test.GetHealth() << " " << car_test.GetLongAttackMap() << " " << car_test.GetShortAttackMap() << " " << car_test.GetAttackPlane() << " " << car_test.GetHealPlane() << " " << car_test.CommandAir() << endl;//��ʾ״̬

    //ͣ����λ��1����ɫ
    for (int i = 0; i < 5; ++i) {
        car_test.Refresh(p1, 0);
        cout << car_test.GetHealth() << " " << car_test.GetLongAttackMap() << " " << car_test.GetShortAttackMap() << " " << car_test.GetAttackPlane() << " " << car_test.GetHealPlane() << " " << car_test.CommandAir() << endl;//��ʾ״̬
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
