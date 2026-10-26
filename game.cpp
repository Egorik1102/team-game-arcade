#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include<windows.h>
#include<clocale>
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

void exploreLair() {
    int roll = rand() % 100;
    if (roll < 50) {
        int gold = 20 + rand() % 30;
        resources += gold;
        score += 100;
        std::cout << "\n[УДАЧА] Вы победили гоблина! Найдено золота: " << gold << "\n";
    } else {
        int dmg = 30 + rand() % 20;
        hp -= dmg;
	if (hp < 0) hp = 0; // ФИКС: запрещаем уходить в минус
        std::cout << "\n[ПРОВАЛ] Дракон обжёг вас! Потеряно здоровья: " << dmg << "\n";
    }
}

void visitTavern() {
    if (resources >= 30) {
        resources -= 30;
        hp += 40;
        if (hp > 100) hp = 100; // Защита от превышения лимита
        std::cout << "\n[ОТДЫХ] Вы поели и отдохнули. HP восстановлено (+40). Золото (-30).\n";
    } else {
    std::cout << "\n[ОТКАЗ] У вас нет 30 золотых! Вас выгнали из таверны.\n";
    return; // ФИКС: прерываем ход, чтобы не давать очки
	}
}

int main() {
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	setlocale(LC_ALL, "Russian");
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
                exploreLair();
                break;
            case 2:
    		visitTavern();
    		break;
            case 3:
                // [РАЗРАБОТЧИК 3: ПОДКЛЮЧИТ РУЛЕТКУ/КОСТИ (ISSUE #3)]
                std::cout << "\n[!] Модуль событий еще в разработке (Issue #3).\n";
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