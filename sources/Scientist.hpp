#pragma once
#include "Board.hpp"
#include "Player.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <iostream>

using namespace std;

namespace pandemic
{
    class Scientist : public Player
    {
        int num;

    public:
        bool isExistNCards(set<City>& ,Color) const;
        void eraseNCards();
        Scientist(Board &board, City c, int n);
        using Player::Player;
        string role() { return "Scientist"; }
        Player &discover_cure(Color);
    };
}