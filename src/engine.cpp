#include "engine.h"
#include <algorithm>

Engine::Engine(const std::string& SaveFile) : serializer(SaveFile) {
    if(fs::is_regular_file(SaveFile)) serializer.LoadData(teams);
    else teams = DefaultTeams, serializer.SaveData(teams);
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

u32 Engine::EliminateLessThan(Team& team, const u32 minGoalCount) {
    u32 c = 0;
    auto it = team.players.begin();
    
    while (it != team.players.end()) {
        if (it->goalCount < minGoalCount)
            it = team.players.erase(it),
            ++c;
        else ++it;
    }
    
    return c;
}

Nationality Engine::GetCountryWithMostPlayers() const {
    std::array<u32, NATIONALITY_SIZE> count {};

    for(const Team& team : teams)
        for(const Player& player : team.players)
            ++count[static_cast<u32>(player.nationality)];

    return static_cast<Nationality>(
        std::distance(count.begin(), 
        std::max_element(count.begin(), count.end()))
    );
}

std::vector<Player> Engine::GetMostGoals() const {
    u32 mostGoals = 0;

    for(const Team& team : teams)
        for(const Player& player : team.players)
            mostGoals = std::max(mostGoals, player.goalCount);

    std::vector<Player> players;
    players.reserve(3);

    for(const Team& team : teams)
        for(const Player& player : team.players)
            if(player.goalCount == mostGoals)
                players.push_back(player);

    std::sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
        return a.name < b.name;
    });

    return players;
}