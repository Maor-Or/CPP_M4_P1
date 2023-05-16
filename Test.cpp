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

TEST_CASE("Point class Initilazation and function calling:")
{

    CHECK_NOTHROW(Point p1{0, 0});
    CHECK_NOTHROW(Point pNegative{-10, -10});

    Point pNegative{-10, -10};
    Point p1(1, 1), p2(7, 1), p3(1, 7), p41(7, 7);
    CHECK_EQ(p1.distance(p2), 6);
    CHECK_EQ(p1.distance(p3), 6);
    CHECK_EQ(p1.distance(p41), doctest::Approx(8.485281).epsilon(0.001));
    CHECK(p2.distance(p3) == doctest::Approx(8.485281).epsilon(0.001));

    Point p4(0, 0), p5(10, 10), p6(0, 3);

    CHECK_EQ(pNegative.distance(p5), doctest::Approx(28.284271).epsilon(0.001));
    Point originPoint(Point::moveTowards(pNegative, p5, 28.4271 / 2.0));
    CHECK_EQ(originPoint.getX(), doctest::Approx(0).epsilon(0.1));
    CHECK_EQ(originPoint.getY(), doctest::Approx(0).epsilon(0.1));

    double distance = p4.distance(p5);

    CHECK(distance == doctest::Approx(14.142136).epsilon(0.001));

    double middle_point = distance / 2;
    Point pMiddle{Point::moveTowards(p4, p5, middle_point)}; // pMiddle = (5,5)
    CHECK_EQ(pMiddle.getX(), 5);
    CHECK_EQ(pMiddle.getY(), 5);

    distance = p4.distance(p6); // = 3
    CHECK(distance == 3);
    double twoThird = distance * 2.0 / 3.0; // = 2
    CHECK_EQ(twoThird, 2);
    Point pTwoThird{Point::moveTowards(p4, p6, twoThird)}; // pTwoThirds = (0,2)
    CHECK_EQ(pTwoThird.getX(), 0);
    CHECK_EQ(pTwoThird.getY(), 2);

    // invalid argument:
    CHECK_THROWS_AS(Point::moveTowards(p1, p2, -100), std::invalid_argument); // negative distance
}

TEST_CASE("Cowboy class Initilazation and function calling, cowboy vs cowboy: ")
{
    Cowboy mcree("mcree", {0, 0});
    Cowboy ely("Ely", {4, 20});

    CHECK(ely.getName() == "Ely");

    CHECK_THROWS(Cowboy("", {1, 1})); // name cannot be empty
    CHECK_THROWS(Cowboy(NULL, {1, 1}));

    CHECK_EQ(true, mcree.isAlive());
    CHECK_EQ(true, ely.isAlive());
    CHECK_EQ(ely.distance(&mcree), mcree.distance(&ely));

    // shooting a full mag twice. making sure the character react correctly:
    for (int i = 0; i < 6; i++)
    {
        ely.shoot(&mcree);
    }
    ely.reload();

    CHECK_EQ(true, mcree.isAlive());

    for (int i = 0; i < 6; i++)
    {
        ely.shoot(&mcree);
    }
    CHECK_EQ(false, ely.hasboolets());
    ely.reload();
    CHECK_EQ(true, ely.hasboolets());

    CHECK_EQ(false, mcree.isAlive());
    CHECK_THROWS(mcree.reload()); // dead cowboy can't reload
}

TEST_CASE("cowboy vs ninja: ")
{
    YoungNinja genji("Genji", {0, 0});
    Cowboy ely("Ely", {4, 20});

    CHECK_THROWS(Cowboy("", {1, 1})); // name cannot be empty
    CHECK_THROWS(Cowboy(NULL, {1, 1}));

    CHECK_EQ(true, genji.isAlive());
    CHECK_EQ(true, ely.isAlive());

    CHECK_THROWS(ely.shoot(&ely)); // can't shoot yourself (sadly)
    CHECK_THROWS(ely.hit(-5));     // can't receive/deal negative dmg

    CHECK_EQ(ely.distance(&genji), genji.distance(&ely));

    for (int i = 0; i < 6; i++)
    {
        ely.shoot(&genji);
    }
    ely.reload();

    CHECK_EQ(true, genji.isAlive());

    for (int i = 0; i < 6; i++)
    {
        ely.shoot(&genji);
    }
    CHECK_EQ(false, ely.hasboolets());
    ely.reload();
    CHECK_EQ(true, ely.hasboolets());

    CHECK_EQ(false, genji.isAlive());

    TrainedNinja genji2("Genji2", {100, 100});
    CHECK_EQ(true, ely.isAlive());

    for (int i = 0; i < 40; i++)
    {
        if (genji2.distance(&ely) < 1)
        {
            genji2.slash(&ely);
        }
        else
        {
            genji2.move(&ely);
        }
    }
    CHECK_EQ(false, ely.isAlive());
}

TEST_CASE("Ninja class Initilazation and function calling, ninja vs ninja: ")
{
    OldNinja oldGenji("OldGenji", {5, 5});
    YoungNinja youngGenji("youngGenji", {10, 5});

    // checking getLocation:
    Point oldGPoint(oldGenji.getLocation());
    Point youngGPoint(youngGenji.getLocation());
    CHECK_EQ(oldGPoint.getX(), 5);
    CHECK_EQ(oldGPoint.getY(), 5);
    CHECK_EQ(youngGPoint.getX(), 10);
    CHECK_EQ(youngGPoint.getY(), 5);

    // slashing from far away:
    for (int i = 0; i < 20; i++)
    {

        oldGenji.slash(&youngGenji);
    }
    CHECK_EQ(true, youngGenji.isAlive());        // slash is too far away, so no dmg should be taken
    CHECK_THROWS(youngGenji.slash(&youngGenji)); // cant slash yourself
}

TEST_CASE("Team class Initilazation and function calling,Team vs Team war")
{
    Cowboy redTeamLeader("Sherif", {3, 3});
    OldNinja blueTeamLeader("Master", {30, 30});

    Team redTeam(&redTeamLeader), blueTeam(&blueTeamLeader);

    CHECK_THROWS(Team(&redTeamLeader)); // leader is already taken

    YoungNinja blueGenji("blueGenji", {33, 33});

    CHECK_NOTHROW(blueTeam.add(&blueGenji));
    CHECK_THROWS(redTeam.add(&blueGenji)); // character is already taken

    CHECK_EQ(redTeam.stillAlive(), 1);
    CHECK_EQ(blueTeam.stillAlive(), 2);

    CHECK_THROWS_AS(blueTeam.attack(nullptr), std::invalid_argument); // cant attack null team

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

