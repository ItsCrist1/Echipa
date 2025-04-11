#include "serializer.h"
#include <fstream>

Serializer::Serializer(const std::string& SaveFile) : SaveFile(SaveFile) {}

void Serializer::savePlayer(std::ofstream& os, const Player& player) const {
    writeWstr(os, player.name);
    writeBF<Nationality>(os, player.nationality);
    writeBF<u32>(os, player.goalCount);
}

void Serializer::saveTeam(std::ofstream& os, const Team& team) const {
    writeWstr(os, team.name);
    
    writeBF<u32>(os, team.players.size());
    for(const Player& player : team.players) savePlayer(os, player);

    writeBF<u32>(os, team.points);
}

Player Serializer::loadPlayer(std::ifstream& is) const {
    const std::wstring name = readWstr(is);
    const Nationality nationality = readBF<Nationality>(is);
    const u32 goalCount = readBF<u32>(is);

    return Player (name, nationality, goalCount);
}

Team Serializer::loadTeam(std::ifstream& is) const {
    const std::wstring name = readWstr(is);

    const u32 sz = readBF<u32>(is);
    std::vector<Player> players;
    players.reserve(sz);
    for(u32 i=0; i < sz; ++i) players.push_back(loadPlayer(is));

    const u32 points = readBF<u32>(is);

    return Team (name, players, points);
}

void Serializer::SaveData(const std::vector<Team>& teams) const {
    std::ofstream os (SaveFile, std::ios::binary);
    
    writeBF<u32>(os, teams.size());
    for(const Team& team : teams) saveTeam(os, team);

    os.close();
}

void Serializer::LoadData(std::vector<Team>& teams) const {
    std::ifstream is (SaveFile, std::ios::binary);
    const u32 sz = readBF<u32>(is);

    teams.reserve(sz);
    for(u32 i=0; i < sz; ++i) teams.push_back(loadTeam(is));

    is.close();
}