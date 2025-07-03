#include <iostream>
#include "Physics/Engine.hpp"
#include "Planet.hpp"
#include "Gravity.hpp"

using namespace CG;
using namespace Physics;
using namespace std;

constexpr int iters = 10;

void printWorld(World<Solvers::Verlet>& wrld) {
    int index = 0;
    for (auto& obj : wrld.getObjects()) {
        cout << " === Object " << ++index << " === " << endl;
        cout << "Position: " << obj->position.x << " " << obj->position.y << endl;
        cout << "Velocity: " << obj->velocity.x << " " << obj->velocity.y << endl;
        cout << "Acceleration: " << obj->acceleration.x << " " << obj->acceleration.y << endl;
        cout << "Forces: " << obj->forces.x << " " << obj->forces.y << endl;
    }
}

int main() {
    World<Solvers::Verlet> world;


    world.addForceGenerator<GravityGenerator>();

    shared_ptr<Object> planet1 = make_shared<Object>(100, vec2(10, 0), vec2(0, 0)); // TODO: Make them planets
    shared_ptr<Object> planet2 = make_shared<Object>(100, vec2(0, 10), vec2(0, 0));
    shared_ptr<Object> planet3 = make_shared<Object>(100, vec2(10, 0), vec2(0, 0));
    shared_ptr<Object> planet4 = make_shared<Object>(100, vec2(0, 10), vec2(0, 0));

    world.addObject(planet1);
    world.addObject(planet2);
    world.addObject(planet3);
    world.addObject(planet4);



    for (auto i = 0; i < iters; i++) {
        world.update(20);
        printWorld(world);
    }

    return EXIT_SUCCESS;
}
