#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// Состояние игры (базовые переменные)
int hp = 100;
int resources = 50; // Золото
int score = 0;      // Очки выживания (цель – рекорд)
int turn = 1;

void printHUD() {
    std::cout << "\n================ [ХОД: " << turn << " | СЧЕТ: " << score << "] ================\n";
    std::cout << "❤️ Здоровье: " << hp << "/100  |  🪙 Золото: " << resources << "\n";
    std::cout << "--------------------------------------------------------------\n";
}

void playDice() {
    int d20 = rand() % 20 + 1;
    std::cout << "\n[КОСТИ] Вы бросили D20 и выпало: " << d20 << "\n";
    if (d20 > 10) {
        resources += 50;
        score += 50;
        std::cout << "[ПОБЕДА] Вы обыграли пьяного наемника! +50 золота.\n";
    } else {
        int dmg = 10;
        hp -= dmg;
        std::cout << "[ПРОИГРЫШ] Наемник ударил вас кружкой! -10 HP.\n";
    }
}
int main() {
    srand(time(NULL));
    int choice = 0;

    std::cout << ">>> ЗАПУСК СИМУЛЯЦИИ: ПОДЗЕМЕЛЬЕ <<<\n";

    while (hp > 0) {
        printHUD();
        std::cout << "1. Спуститься в логово монстров (Высокий риск / Высокая награда)\n";
        std::cout << "2. Зайти в таверну (Лечение и экономика)\n";
        std::cout << "3. Игра в кости с NPC (Рулетка удачи)\n";
        std::cout << "4. Обыскать древний алтарь (Ваша новая механика)\n";
        std::cout << "0. Сдаться и зафиксировать счет\n";
        std::cout << "Выберите действие > ";

        if (!(std::cin >> choice)) break;

        switch (choice) {
            case 1:
                // [РАЗРАБОТЧИК 1: ПОДКЛЮЧИТ ФУНКЦИЮ РИСКА (ISSUE #1)]
                std::cout << "\n[!] Модуль риска еще в разработке (Issue #1).\n";
                break;
            case 2:
                // [РАЗРАБОТЧИК 2: ПОДКЛЮЧИТ МОДУЛЬ ОТХИЛА (ISSUE #2)]
                std::cout << "\n[!] Модуль таверны еще в разработке (Issue #2).\n";
                break;
            case 3:
    		playDice();
    		break;
            case 4:
                // [РАЗРАБОТЧИК 4: ПОДКЛЮЧИТ АЛТАРЬ (ISSUE #4)]
                std::cout << "\n[!] Модуль алтаря еще в разработке (Issue #4).\n";
                break;
            case 0:
                hp = 0;
                break;
            default:
                std::cout << "\nНеизвестная команда!\n";
                break;
        }

        // Каждый успешный ход дает очки выживания
        if (hp > 0) {
            turn++;
            score += 10;
        }
    }

    std::cout << "\n☠️ ИГРА ОКОНЧЕНА. Ваш итоговый рекорд: " << score << " очков!\n";
    return 0;
}