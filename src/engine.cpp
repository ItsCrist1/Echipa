#include "engine.h"
#include <algorithm>

Engine::Engine(const std::string& SaveFile) : serializer(SaveFile) {
    if(fs::is_regular_file(SaveFile)) teams = DefaultTeams, serializer.SaveData(teams);
    else serializer.LoadData(teams);
}

void Engine::ShowPlayers(const Team& team) const {
    std::wcout << L"Players: ";
    for(const Player& player : team.players) std::wcout << player.name << L"; ";
}

void Engine::ShowTop() const {
    std::vector<Team> sortedTeams = teams;

    std::sort(sortedTeams.begin(), sortedTeams.end(), [](const Team& a, const Team& b) {
        return a.points < b.points;
    });

    std::wcout << "Team Top:\n";
    for(u32 i=0; i < sortedTeams.size(); ++i)
        std::wcout << i+1 << L") " << sortedTeams[i].name << L'\n';
}

void Engine::EliminateLessThan(Team& team, const u32 minGoalCount) {
    for(u32 i=0; i < team.players.size(); ++i) {
        if(team.players[i].goalCount < minGoalCount) team.players.erase(team.players.begin() + i);
    }
}

Nationality Engine::GetCountryWithMostPlayers() const {
    // TODO
}