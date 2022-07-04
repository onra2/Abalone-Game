#include "textview.h"
#include "color.h"
#include <algorithm>

using namespace std;
template<typename T>
void print(T const & msg) {
    std::cout << msg << std::endl;
}

TextView::TextView() {
#ifdef __unix__
    isWin32 = false;
#elif defined(_WIN32) || defined(WIN32)
    isWin32 = true;
#endif
}

void TextView::printSideBarOpen(int lineIndex) {
    switch (lineIndex) {
        case 0: cout << "    I /";
            break;
        case 1: cout << "   H /";
            break;
        case 2: cout << "  G /";
            break;
        case 3: cout << " F /";
            break;
        case 4: cout << "E |";
            break;
        case 5: cout << " D \\";
            break;
        case 6: cout << "  C \\";
            break;
        case 7: cout << "   B \\";
            break;
        case 8: cout << "    A \\";
            break;
    }
}

void TextView::printSideBarClosed(int lineIndex) {
    if (lineIndex <= 3) {
        cout << "\\" << std::endl;
    }
    else if (lineIndex == 4) {
        cout << "|" << std::endl;
    }
    else {
        switch (lineIndex) {
            case 5: cout << ((isWin32)?"/":"\033[37;m/") << std::endl;
                break;
            case 6: cout << ((isWin32)?"/":"\033[37;m/") << "  9" << std::endl;
                break;
            case 7: cout << ((isWin32)?"/":"\033[37;m/") << "  8" << std::endl;
                break;
            case 8: cout << ((isWin32)?"/":"\033[37;m/") << "  7" << std::endl;
                break;
        }
    }
}

void TextView::displayBoard(
    std::array<std::array<int, BoardSize>, BoardSize> marbles) {
    int shift = 4;
    int limit = BoardSize;
    cout << ((isWin32)?"":"\033[37;m") << "       ---------" << endl;
    for ( int i = 0; i < BoardSize; i++ ) {
        printSideBarOpen(i);
        for ( int j = shift; j < limit; j++ ) {
            std::cout << ((isWin32)?"":Color::getANSICode(marbles[i][j]));
            if (marbles.at(i).at(j) == -1) {
                if(!isWin32) std::cout << "\033[37;m";
                std::cout << ".";
            }
            else {
                std::cout << Color::getChar(marbles.at(i).at(j));
            }
            if (j != 8 && j != limit - 1) {
                std::cout << " ";
            }
            if(!isWin32) std::cout << "\033[37;m";
        }
        printSideBarClosed(i);
        if (shift > 0) {
            --shift;
        }
        else if (shift == 0) {
            --limit;
        }
    }
    if(!isWin32) cout << "\033[37;m";
    cout << "       ---------  6" << endl;
    cout << "         1 2 3 4 5" << ((isWin32)?"":"\033[37;m") << endl;
}

void TextView::askMove() {

    string buffer;
    array<string, 3> * result = new array<string, 3>();

    std::cout << "What do you want to move?" << endl;
    std::cout << "(Use ABA-PRO notation ex: A1B2 or A1A3B2)" << endl;

    do {
        if (!buffer.empty()) {
            std::cout << "Please use only ABA-PRO notation" << endl;
            std::cout << "for exemple: to move a marbel use A1B2" << endl;
            std::cout << "             to move a line use A1A3B2" << endl;
        }

        cin >> buffer;

    }
    while (buffer.length() != 4 && buffer.length() != 6);

    //toUpperCase
    std::transform(buffer.begin(), buffer.end(), buffer.begin(),
                   ::toupper);

    //séparer en 3 résultats
    for (size_t i(0); i < sizeof(char[6]) &&
            i + 2 <= buffer.size(); i = i + 2) {
        result->at(i / 2) = buffer.substr(i, 2);
    }

    this->notify("ABAPROMove", result);
    std::cout << endl;
}

void TextView::displayHeader(std::array<int, 2> score) {
    std::cout << ((isWin32)?"":"\033[37;m") << "--------------SCORES------------" << std::endl;
    for (size_t i(0); i < score.size(); ++i) {
        std::cout << "PLAYER " << Color::getChar(i) << ": " << score[i] <<
                  std::endl;
    }
    std::cout << "--------------------------------" << std::endl;
}

void TextView::displayWinner(int * player) {
    std::cout << std::endl << "--------------------------------" <<
              std::endl;
    std::cout << "|   PLAYER " << Color::getChar(* player) <<
              " HAS WON THE GAME  |" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    delete player;
}

void TextView::displayMessage(string message) {
    std::cout << std::endl;
    std::cout << message << std::endl;
    std::cout << std::endl;
}

void TextView::update(std::string name, void * object) {

    if (name == "Board") {
        std::array<std::array<int, BoardSize>, BoardSize> * marbels;
        marbels = static_cast<std::array<std::array<int, BoardSize>, BoardSize> *>
                  (object);

        this->displayBoard(*marbels);
        this->askMove();

    }
    else if (name == "Score") {
        this->displayHeader(*static_cast<std::array<int, 2> *>(object));

    }
    else if (name == "displayWinner") {
        this->displayWinner(static_cast<int *>(object));

    }
    else if (name == "currentPlayer") {
        int * str = static_cast<int *>(object);
        this->displayMessage(((isWin32)?"":Color::getANSICode(
                                 *str)) + "## Player " +
                             Color::getChar(*str) + " to play");

    }
    else if (name == "error") {
        std::exception * str = static_cast<std::exception *>(object);
        this->displayMessage(str->what());
        this->askMove();

    }
    else {
        throw new exception();
    }

}

void TextView::addObserver(iObserver * observer) {
    observers.push_back(observer);
}

void TextView::removeObserver(iObserver * observer) {
    observers.remove(observer);
}

void TextView::notify(std::string name, void * object) {
    for (iObserver * o : observers) {
        o->update(name, object);
    }
}
