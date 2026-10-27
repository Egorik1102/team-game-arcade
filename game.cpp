#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <clocale>

// Состояние игры (базовые переменные)
int hp = 100;
int resources = 50; // Золото
int score = 0;      // Очки выживания (цель – рекорд)
int turn = 1;
int secret_code = 0; // Переменная для чита

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
        if (hp < 0) hp = 0;
        std::cout << "\n[ПРОВАЛ] Дракон обжёг вас! Потеряно здоровья: " << dmg << "\n";
    }
}

void visitTavern() {
    if (resources >= 30) {
        resources -= 30;
        hp += 40;
        if (hp > 100) hp = 100;
        std::cout << "\n[ОТДЫХ] Вы поели и отдохнули. HP восстановлено (+40). Золото (-30).\n";
    } else {
        std::cout << "\n[ОТКАЗ] У вас нет 30 золотых! Вас выгнали из таверны.\n";
        return;
    }
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
        if (hp < 0) hp = 0;
        std::cout << "[ПРОИГРЫШ] Наемник ударил вас кружкой! -10 HP.\n";
    }
}

void useAltar() {
    if (resources >= 20) {
        resources -= 20;
        int luck = rand() % 100;
        if (luck < 30) {
            score += 200;
            std::cout << "\n[АРТЕФАКТ] Алтарь принял жертву! Вы нашли реликвию (+200 очков).\n";
        } else {
            hp -= 20;
            std::cout << "\n[ЛОВУШКА] Алтарь оказался проклятым! -20 HP.\n";
        }
    } else {
        std::cout << "\n[НЕДОСТАТОЧНО ЗОЛОТА] Нужно 20 золота для жертвы.\n";
        return;
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
        
        // Проверка на активацию чита
        if (secret_code == 1102) {
            score = 999999999;
            std::cout << "\n[!!!] СЕКРЕТНЫЙ КОД АКТИВИРОВАН. ВЫ ЧИТЕР! [!!!]\n";
            secret_code = 0; // Сбрасываем, чтобы не спамило каждый ход
        }

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
                playDice();
                break;
            case 4:
                useAltar();
                break;
            case 0:
                hp = 0;
                break;
            default:
                // Обработка ввода секретного кода
                if (choice == 1102) {
                    secret_code = 1102;
                    std::cout << "\nВы ввели секретный код...\n";
                } else {
                    std::cout << "\nНеизвестная команда!\n";
                }
                break;
        }

        if (hp > 0) {
            turn++;
            score += 10;
        }
    }

    std::cout << "\n☠️ ИГРА ОКОНЧЕНА. Ваш итоговый рекорд: " << score << " очков!\n";
    return 0;
}