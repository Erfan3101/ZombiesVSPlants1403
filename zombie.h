#ifndef ZOMBIE_H
#define ZOMBIE_H

#endif // ZOMBIE_H
#include <iostream>
using namespace std;
class zombie{
    int health_z;
    int movement_delay;
    int attack_power;
    int time_between_attack;
    string description;
public:
    zombie(int h,int m , int a, int t, string d):health_z(h),movement_delay(m),attack_power(a),time_between_attack(t),description(d){}
};
