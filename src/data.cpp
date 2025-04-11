#include "data.h"

Player::Player(const std::wstring& name, const Nationality nationality, const u32 goalCount)
: name(name), nationality(nationality), goalCount(goalCount) {}

Team::Team(const std::wstring& name, const std::vector<Player>& players, const u32 points)
: name(name), players(players), points(points) {}