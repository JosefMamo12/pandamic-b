#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <set>

using namespace std;
const u_int MAX_COLOR_WORD = 7;
const u_int MAX_CITY_WORD = 13;
namespace pandemic
{
    map<City, int> Board::_disease_level;
    map<City, Color> Board::_cityColor;
    map<City, set<City>> Board::_connections;
    map<City, bool> Board::_research_station;
    map<Color, bool> Board::_isCured;

    /* 
    To intialize the map i chose to stream the game map and details by using stream file which called citites_text
    i read each row from the text and defining the concept with the index varibale.
     */
    void Board::read_units(ifstream &file)
    {
        unsigned int index = 0;
        string sentence;
        string currentCity;
        string connectedCities;
        string cityColor;
        while (file)
        {
            index = 0;
            getline(file, sentence);

            istringstream iss(sentence);
            while (iss)
            {

                if (index == 0)
                {
                    iss >> currentCity >> cityColor;
                    auto it_city = convert_string_to_City.find(currentCity);
                    auto it_color = convert_string_to_Color.find(cityColor);
                    _cityColor[it_city->second] = it_color->second;
                    _research_station[it_city->second] = false;
                    _disease_level[it_city->second] = 0;
                    index++;
                }
                iss >> connectedCities;
                auto it_city = convert_string_to_City.find(currentCity);
                auto it_city_connections = convert_string_to_City.find(connectedCities);
                _connections[it_city->second].insert(it_city_connections->second);
            }
        }
        _isCured[Color::Black] = false;
        _isCured[Color::Blue] = false;
        _isCured[Color::Yellow] = false;
        _isCured[Color::Red] = false;
    }
    Board::Board()
    {
        ifstream units_file{"cities_map.txt"};
        Board::read_units(units_file);
    }
  
    int &Board::operator[](City city)
    {
        return _disease_level[city];
    }
    bool Board::is_clean()
    {
        for (auto &i : _disease_level)
        {
            if (i.second != 0)
            {
                return false;
            }
        }
        return true;
    }
    void Board::remove_cures()
    {
        for (auto &i : _isCured)
        {
            i.second = false;
        }
    }
    void Board::remove_stations()
    {
        for (auto &i : _research_station)
        {
            i.second = false;
        }
    }

    string addBackSpaces()
    {
        return "             ";
    }
    string addBackSpacesCity(City c)
    {
        string ans;
        for (const auto &i : convert_string_to_City)
        {
            if (i.second == c)
            {
                u_int length = i.first.length();
                for (u_int j = 0; j < MAX_CITY_WORD - length; ++j)
                {
                    ans += " ";
                }
                break;
            }
        }
        return ans;
    }
    string addBackSpacesColor(Color c)
    {
        string ans;
        for (const auto &i : convert_string_to_Color)
        {
            if (i.second == c)
            {
                u_int length = i.first.length();
                for (u_int j = 0; j < MAX_COLOR_WORD - length; ++j)
                {
                    ans += " ";
                }
                break;
            }
        }
        return ans;
    }
    ostream &operator<<(ostream &os, const Board &a)
    {
        os << "-------------------------" << endl;
        os << "Disease | Cured/Not Cured" << endl;
        os << "-------------------------" << endl;
        for (const auto &i : pandemic::Board::_isCured)
        {
            os << i.first << addBackSpacesColor(i.first) << " | ";
            if (i.second)
            {
                os << "Cured" << endl;
            }
            else
            {
                cout << "Not Cured" << endl;
            }
        }
        os << endl;
        os << "---------------------------------------------" << endl;
        os << "City          | Diseases level | Research lab" << endl;
        os << "---------------------------------------------" << endl;
        for (const auto &i : pandemic::Board::_disease_level)
        {
            os << i.first << addBackSpacesCity(i.first) << " | " << i.second;
            if (pandemic::Board::_research_station.at(i.first))
            {
                os << addBackSpaces() << " | "
                     << "Exist" << endl;
            }
            else
            {
                os << addBackSpaces() << " | "
                     << "Not Exist" << endl;
            }
        }

        return os;
    }
}
