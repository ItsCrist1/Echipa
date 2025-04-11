#pragma once
#include "data.h"

class Serializer {
    const std::string SaveFile;
    
    void savePlayer(std::ofstream&, const Player&) const;
    void saveTeam(std::ofstream&, const Team&) const;

    Player loadPlayer(std::ifstream&) const;
    Team loadTeam(std::ifstream&) const;
public:
    Serializer(const std::string&);

    void SaveData(const std::vector<Team>&) const;
    void LoadData(std::vector<Team>&) const;
};