// Created by cyx15 & ty15, 2016.9


#include"Game.h"
#include"Random.hpp"

#include <opencv2/opencv.hpp>
#include <fstream>

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

    const int force = 6;
    const int move = 6, range = move * 2;

    // load map
    ifstream in("./data/test.txt");
    in >> size;
    cv::Mat map = cv::Mat::zeros(size, size, CV_8UC3);
    for (int i=0; i<size; ++i)
        for (int j = 0; j < size; ++j) {
            int k; in >> k;
            if (0 == k) map.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 0);
            else map.at<cv::Vec3b>(i, j) = cv::Vec3b(255, 255, 255);
        }

    // display
    cv::Mat display;

    for (int i = 0; i < 1800; ++i) {

        GameData gamedata = game.getGameData();

        Point t = game.GetTargetPoint();
        p1.x += random.Rand() % range - move; p1.y += random.Rand() % range - move;
        
        if (PropHP == game.GetProp() || 
            ( PropAC == game.GetProp() /*&& gamedata.carData[Red].health > gamedata.carData[Blue].health*/)
            ) { // get prop first!
            t = game.GetPropPoint();
            if (p1.x > t.x) p1.x -= force; else p1.x += force;
            if (p1.y > t.y) p1.y -= force; else p1.y += force;
        } else 
        if (game.GetTargetHP() > 0) {
            t = game.GetTargetPoint();
            if (p1.x > t.x) p1.x -= force; else p1.x += force;
            if (p1.y > t.y) p1.y -= force; else p1.y += force;
        }

        p2.x += random.Rand() % range - move; p2.y += random.Rand() % range - move;
        if (PropHP == game.GetProp() ) { // get prop first!
            t = game.GetPropPoint();
            if (p2.x > t.x) p2.x -= force; else p2.x += force;
            if (p2.y > t.y) p2.y -= force; else p2.y += force;
        } else
        if (game.GetTargetHP() > 0) { // get to the target!
            t = game.GetTargetPoint();
            if (p2.x > t.x) p2.x -= force; else p2.x += force;
            if (p2.y > t.y) p2.y -= force; else p2.y += force;
        }

        
        pp.x += random.Rand() % range - move; pp.y += random.Rand() % range - move;

        if (gamedata.carData[Red].air_command) {
            if (gamedata.planeStatus == PlaneAttack /*&& gamedata.carData[Red].health > gamedata.carData[Blue].health*/) {
                t = gamedata.carData[Blue].pos;
                if (pp.x > t.x) pp.x -= force; else pp.x += force;
                if (pp.y > t.y) pp.y -= force; else pp.y += force;
            }
            if (gamedata.planeStatus == PlaneHeal) {
                t = gamedata.carData[Red].pos;
                if (pp.x > t.x) pp.x -= force; else pp.x += force;
                if (pp.y > t.y) pp.y -= force; else pp.y += force;
            }
        }
        

        game.Refresh(p1, p2, pp);



        ////////////////////////////////////////// display
        gamedata = game.getGameData();
		cout << gamedata.getString() << endl;

        int radius = 9;

        char buffer[512];

        display = map.clone();
        t = gamedata.targetPoint;
        if (gamedata.targetHealth > 0) 
            cv::circle(display, cv::Point(t.y, t.x), radius, cv::Scalar(0, 255, 0), -1);
        t = gamedata.carData[Red].pos;
        cv::circle(display, cv::Point(t.y, t.x), radius, cv::Scalar(0, 0, 255), -1);
        t = gamedata.carData[Blue].pos;
        cv::circle(display, cv::Point(t.y, t.x), radius, cv::Scalar(255, 0, 0), -1);
        t = gamedata.planePoint;
        cv::circle(display, cv::Point(t.y, t.x), radius, cv::Scalar(255, 255, 0), -1);
        t = gamedata.propPoint;
        if (gamedata.propType != PropET) {
            cv::circle(display, cv::Point(t.y, t.x), radius, cv::Scalar(255, 0, 255), -1);
            sprintf(buffer, "%d", gamedata.propType);
            cv::putText(display, buffer, cv::Point(t.y-3, t.x+3), 1, 1, cv::Scalar(255, 255, 255));
        }
        
        /*sprintf(buffer, "%.1lf", gamedata.carData[Red].health);
        cv::putText(display, buffer, cv::Point(0, 250), 1, 1, cv::Scalar(0, 0, 255));
        sprintf(buffer, "%.1lf", gamedata.carData[Blue].health);
        cv::putText(display, buffer, cv::Point(200, 250), 1, 1, cv::Scalar(255, 0, 0));
        sprintf(buffer, "%.1lf", gamedata.carData[Red].health - gamedata.carData[Blue].health);
        cv::putText(display, buffer, cv::Point(0, 230), 1, 0.7, cv::Scalar(0, 0, 255));
        */

        cv::rectangle(display, cv::Rect(20, 252, gamedata.carData[Red].health, 3), cv::Scalar(0, 0, 255), -1);
        cv::rectangle(display, cv::Rect(20, 249, gamedata.carData[Blue].health, 3), cv::Scalar(255, 0, 0), -1);

        cv::resize(display, display, cv::Size(512, 512));

        cv::imshow("display", display);
        cv::waitKey(100);

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
