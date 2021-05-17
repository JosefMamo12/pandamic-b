#include <iostream>
#include "Board.hpp"
#include "Player.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Dispatcher.hpp"

using namespace std;

namespace pandemic
{
    Player &Dispatcher::fly_direct(City c)
    {
        if (c == this->currentCity)
        {
            throw invalid_argument("You'r already at this city");
        }
        if (pandemic::Board::get_research_station().at(this->currentCity))
        {
            this->currentCity = c;
            return *this;
        }
        if (this->player_deck.find(c) != this->player_deck.end())
        {
            this->player_deck.erase(c);
            this->currentCity = c;
            return *this;
        }
        throw invalid_argument(NO_RESEARCH_CITY + " or " + NOT_EXISITNG_CARD);
    }
}