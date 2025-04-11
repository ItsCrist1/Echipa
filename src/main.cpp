#include "engine.h"

#ifndef _WIN32
#include <locale>
#else
#include <windows.h>
#include <corecrt.h>
#include <fcntl.h>
#include <io.h>
#endif

static const std::string SaveFile = "data.dat";

static const std::wstring SelectedColor = getCol({ 245, 212, 66 });
static const std::wstring UnselectedColor = getCol({ 112, 109, 96 });

Engine engine (SaveFile);

std::wstring getCol(const bool condition) {
    return condition ? SelectedColor : UnselectedColor;
}

static const u8 MAIN_MENU_ENTRIES_SIZE = 5;

static const std::array<std::wstring, MAIN_MENU_ENTRIES_SIZE> MainMenuEntries {
    L"Show Team",
    L"Show Teams in Order",
    L"Eliminate Players with less than x goals",
    L"Show Country with most players",
    L"Show Players with most goals"
};

Team& TeamsMenu() {
    const u32 teamsSize = engine.teams.size();
    u32 idx = 0;

    while(true) {
        clearScreen();

        for(u32 i=0; i < teamsSize; ++i)
            std::wcout << getCol(idx == i) << i + 1 << L") " 
                       << engine.teams[i].name << L'\n' << getCol();

        const char c = getChar();

        if(std::isdigit(c)) {
            if(const u8 nidx=c-'0'; nidx > 0 && nidx <= teamsSize) idx = nidx - 1;
            continue;
        }

        switch(c) {
            case 'w':
            case 'd': idx = idx == 0 ? teamsSize - 1 : idx - 1;
            break;

            case 's':
            case 'a': idx = idx == teamsSize - 1 ? 0 : idx + 1;
            break;

            default: return engine.teams[idx];
        }
    }
}

void ExecMainMenuEntry(const u8 idx) {
    clearScreen();

    switch(idx) {
        case 0: engine.ShowPlayers(TeamsMenu()); break;

        case 1: engine.ShowTop(); break;

        case 2: {
            Team& team = TeamsMenu();
            u32 num;
            std::wcout << L"\nEnter number: ";

            std::cin >> num;
            clearInputBuffer();
        
            std::wcout << getCol(true) << L"\nSuccessfully eliminated " 
                       << engine.EliminateLessThan(team, num) << L" players"
                       << getCol();
            break;
        }

        case 3: std::wcout << L"Country: " << getCountryWstr(engine.GetCountryWithMostPlayers()); break;

        case 4: {
        for(const Player& player : engine.GetMostGoals())
            std::wcout << player.name << L" - " << player.goalCount << L'\n';
        break;
        }
    }
    
    getCharV();
}

void MainMenu() {
    u8 idx = 0;
    
    while(true) {
        clearScreen();
        
        for(u8 i=0; i < MAIN_MENU_ENTRIES_SIZE; ++i)
            std::wcout << getCol(idx == i) << i + 1 << L") " 
                       << MainMenuEntries[i] << L'\n' << getCol();

        const char c = getChar();

        if(std::isdigit(c)) {
            if(const u8 nidx=c-'0'; nidx > 0 && nidx <= MAIN_MENU_ENTRIES_SIZE) idx = nidx - 1;
            continue;
        }

        switch(c) {
            case 'w':
            case 'd': idx = idx == 0 ? MAIN_MENU_ENTRIES_SIZE - 1 : idx - 1;
            break;

            case 's':
            case 'a': idx = idx == MAIN_MENU_ENTRIES_SIZE - 1 ? 0 : idx + 1;
            break;

            case 'q': return;

            default: ExecMainMenuEntry(idx); break;
        }

    }
}

i32 main() {
    #ifndef _WIN32
    initTerminalStates();
    std::locale::global (std::locale(""));
    std::system("reset");
	#else
    if(!_setmode(_fileno(stdout), _O_U16TEXT)) {
        std::wcerr << L"Unable to set UTF-16 in the terminal, some symbols or colors may not render correctly, do you wish to continue? [y/N] ";
        if(std::tolower(getChar()) != 'y') return 1;
    }
    #endif
    
    MainMenu();

    std::wcout << getCol(RGB{0,255,0}) << L"\n\nAll data saved successfully\nGoodbye!" << getCol() << std::endl;
    
#ifndef _WIN32
    cleanup(0);
    std::system("reset");
#endif
    
    return 0;
}
