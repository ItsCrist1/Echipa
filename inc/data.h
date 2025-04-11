#pragma once
#include "utils.h"
#include <vector>
#include <array>

struct Player {
    std::wstring name;
    Nationality nationality;
    u32 goalCount;

    Player(const std::wstring&, const Nationality, const u32);
};

struct Team {
    std::wstring name;
    std::vector<Player> players;
    u32 points;

    Team(const std::wstring&, const std::vector<Player>&, const u32);
};