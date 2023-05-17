#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>

#include "doctest.h"

#include "sources/Character.hpp"
#include "sources/OldNinja.hpp"
#include "sources/YoungNinja.hpp"
#include "sources/TrainedNinja.hpp"
#include "sources/Cowboy.hpp"
#include "sources/Team.hpp"
#include "sources/Team2.hpp"
#include <random>
#include <chrono>

using namespace std;
using namespace ariel;

TEST_CASE("Point class Initialazation and function calling:")
{
    // valid initailizations:
    CHECK_NOTHROW(Point p1{0, 0});
    CHECK_NOTHROW(Point pNegative{-10, -10});

    Point pNegative{-10, -10};
    Point p1(1, 1), p2(7, 1), p3(1, 7), p41(7, 7);
    Point p4(0, 0), p5(10, 10), p6(0, 3);

    // checking distance():
    CHECK_EQ(p1.distance(p2), 6);
    CHECK_EQ(p1.distance(p3), 6);
    CHECK_EQ(p1.distance(p41), doctest::Approx(8.485281).epsilon(0.001));
    CHECK(p2.distance(p3) == doctest::Approx(8.485281).epsilon(0.001));
    CHECK_EQ(pNegative.distance(p5), doctest::Approx(28.284271).epsilon(0.001));

    // checking moveTowards():
    Point originPoint(Point::moveTowards(pNegative, p5, 28.4271 / 2.0));
    CHECK_EQ(originPoint.getX(), doctest::Approx(0).epsilon(0.1));
    CHECK_EQ(originPoint.getY(), doctest::Approx(0).epsilon(0.1));

    double distance = p4.distance(p5);
    double middle_point = distance / 2;
    Point pMiddle{Point::moveTowards(p4, p5, middle_point)}; // pMiddle = (5,5)

    CHECK(distance == doctest::Approx(14.142136).epsilon(0.001));
    CHECK_EQ(pMiddle.getX(), 5);
    CHECK_EQ(pMiddle.getY(), 5);

    distance = p4.distance(p6); // = 3
    CHECK(distance == 3);
    double twoThird = distance * 2.0 / 3.0; // = 2
    CHECK_EQ(twoThird, 2);
    Point pTwoThird{Point::moveTowards(p4, p6, twoThird)}; // pTwoThirds = (0,2)
    CHECK_EQ(pTwoThird.getX(), 0);
    CHECK_EQ(pTwoThird.getY(), 2);

    // invalid argument, should throw:
    CHECK_THROWS_AS(Point::moveTowards(p1, p2, -100), std::invalid_argument); // negative distance
}

TEST_CASE("Cowboy class Initialazation and function calling, cowboy vs cowboy: ")
{
    // valid initialization:
    Cowboy *mcree = new Cowboy("mcree", {0, 0});
    Cowboy *ely = new Cowboy("Ely", {4, 20});

    CHECK(ely->getName() == "Ely");

    // invalid initialization, name cannot be empty:
    CHECK_THROWS(Cowboy("", {1, 1}));
    CHECK_THROWS(Cowboy(NULL, {1, 1}));

    // upon initialization, cowboy should be alive:
    CHECK_EQ(true, mcree->isAlive());
    CHECK_EQ(true, ely->isAlive());
    CHECK_EQ(ely->distance(mcree), mcree->distance(ely));

    // testing shoot(), reload(), isAlive(), hasBoolets():
    //  shooting a full mag twice. making sure the character react correctly:
    for (int i = 0; i < 6; i++)
    {
        ely->shoot(mcree);
    }

    //can't shoot with no bullets
    CHECK_THROWS(ely->shoot(mcree));
    ely->reload();

    CHECK_EQ(true, mcree->isAlive());

    for (int i = 0; i < 6; i++)
    {
        ely->shoot(mcree);
    }

    CHECK_EQ(false, ely->hasboolets());
    ely->reload();
    CHECK_EQ(true, ely->hasboolets());
    CHECK_EQ(false, mcree->isAlive());
    CHECK_THROWS(mcree->reload()); // dead cowboy can't reload

    delete ely;
    delete mcree;
}

TEST_CASE("cowboy vs ninja: ")
{
    // valid initialization:
    YoungNinja *genji = new YoungNinja("Genji", {0, 0});
    TrainedNinja *genji2 = new TrainedNinja("Genji2", {100, 100});
    Cowboy *ely = new Cowboy("Ely", {4, 20});

    // invalid initialization:
    CHECK_THROWS(YoungNinja("", {1, 1})); // name cannot be empty
    CHECK_THROWS(YoungNinja(NULL, {1, 1}));

    // checking isAlive(), shoot(), hit(), distance()
    CHECK_EQ(true, genji->isAlive());
    CHECK_EQ(true, ely->isAlive());
    CHECK_THROWS(ely->shoot(ely)); // can't shoot yourself (sadly)
    CHECK_THROWS(ely->hit(-5));    // can't receive/deal negative dmg
    CHECK_EQ(ely->distance(genji), genji->distance(ely));

    // killing a ninja with a cowboy:
    for (int i = 0; i < 6; i++)
    {
        ely->shoot(genji);
    }
    ely->reload();

    CHECK_EQ(true, genji->isAlive());

    for (int i = 0; i < 6; i++)
    {
        ely->shoot(genji);
    }
    CHECK_EQ(false, ely->hasboolets());
    ely->reload();
    CHECK_EQ(true, ely->hasboolets());
    CHECK_EQ(false, genji->isAlive());
    CHECK_EQ(true, ely->isAlive());

    // killing a cowboy with a ninja:
    for (int i = 0; i < 40; i++)
    {
        if (genji2->distance(ely) < 1)
        {
            genji2->slash(ely);
        }
        else
        {
            genji2->move(ely);
        }
    }
    CHECK_EQ(false, ely->isAlive());

    delete ely;
    delete genji;
    delete genji2;
}

TEST_CASE("Ninja class Initialazation and function calling, ninja vs ninja: ")
{

    // valid initialization:
    OldNinja *oldGenji = new OldNinja("OldGenji", {5, 5});
    YoungNinja *youngGenji = new YoungNinja("youngGenji", {10, 5});

    // checking getLocation():
    Point oldGPoint(oldGenji->getLocation());
    Point youngGPoint(youngGenji->getLocation());
    CHECK_EQ(oldGPoint.getX(), 5);
    CHECK_EQ(oldGPoint.getY(), 5);
    CHECK_EQ(youngGPoint.getX(), 10);
    CHECK_EQ(youngGPoint.getY(), 5);

    // slashing from far away, should do no harm:
    for (int i = 0; i < 20; i++)
    {
        oldGenji->slash(youngGenji);
    }
    CHECK_EQ(true, youngGenji->isAlive());       // slash is too far away, so no dmg should be taken
    CHECK_THROWS(youngGenji->slash(youngGenji)); // cant slash yourself

    delete oldGenji;
    delete youngGenji;
}

TEST_CASE("Team class Initialazation and function calling,Team vs Team war")
{
    OldNinja *blueTeamLeader = new OldNinja("Master", {30, 30});
    Cowboy *redTeamLeader = new Cowboy("Sherif", {3, 3});
    YoungNinja *blueGenji = new YoungNinja("blueGenji", {33, 33});

    // valid initailizations:
    Team redTeam(redTeamLeader), blueTeam(blueTeamLeader);

    // invalid initailizations:
    CHECK_THROWS(Team(redTeamLeader)); // leader is already taken
    CHECK_THROWS(Team(nullptr));       // leader can't be nullptr

    // testing add():
    CHECK_NOTHROW(blueTeam.add(blueGenji));
    CHECK_THROWS(redTeam.add(blueGenji)); // character is already taken
    CHECK_THROWS(redTeam.add(nullptr));   // character can't be nullptr

    // testing stillAlive():
    CHECK_EQ(redTeam.stillAlive(), 1);
    CHECK_EQ(blueTeam.stillAlive(), 2);

    // testing attack():
    CHECK_THROWS_AS(blueTeam.attack(nullptr), std::invalid_argument); // cant attack null team

    // simulating a full game:
    int teamTurn = 0;
    for (int i = 0; i < 10000 && redTeam.stillAlive() && blueTeam.stillAlive(); ++i)
    {
        if (teamTurn % 2 == 0)
        {
            redTeam.attack(&blueTeam);
        }
        else
        {
            blueTeam.attack(&redTeam);
        }
        teamTurn = (teamTurn + 1) % 2;
    }
}
