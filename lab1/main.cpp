#include <iostream>
#include <fstream>

using namespace std;

int ReadPositiveNumber()
{
    int result;
    cin >> result;
    while (!cin || result < 0)
    {
        cout << "Введите целое неотрицательное число ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> result;
    }

    return result;
}

void NotEnoughArea(int area)
{
    cout << "У вас всего " << area << " акров" << endl;
}

int main()
{
    cout << "Добро пожаловать в 'Правитель Египта'!" << endl;

    srand(time(0));

    int population = 100;
    int wheat = 2800;
    int area = 1000;
    int hungry_villagers = 0;
    int harvest = 0;
    int newcomers = 0;
    bool plague = false;
    int harvest_rate;
    int rat_damage = 0;
    int total_hungry_percentage = 0;
    int year = 1;

    fstream in("save.sav");
    if (in.is_open())
    {
        cout << "Найдено сохранение. Желаете ли вы продолжить игру? (y/n)" << endl;
        if (cin.get() == 'y')
        {
            in >> population >> wheat >> area >> hungry_villagers >> harvest >> newcomers >> plague >> harvest_rate >> rat_damage >> total_hungry_percentage >> year;
            cout << "Игра загружена" << endl;
        }
        cin.get();
    }
    in.close();

    while (year <= 10)
    {
        cout << "Введите q, чтобы выйти, или нажмите клавишу 'Ввод', чтобы продолжить ";

        if (cin.get() == 'q')
            return 0;

        int area_price = 17 + rand() % 10;

        cout << "Мой повелитель, соизволь поведать тебе" << endl
             << "   В году " << year << " твоего высочайшего правления" << endl;

        if (hungry_villagers > 0)
        {
            cout << "   " << hungry_villagers << " человек умерли с голода";

            if (newcomers <= 0)
                cout << endl;
        }

        if (newcomers > 0)
        {
            if (hungry_villagers > 0)
                cout << ", и ";
            else
                cout << "   ";

            cout << newcomers << " человек прибыли в наш великий город" << endl;
        }

        if (plague)
        {
            population /= 2;
            cout << "   Чума истребила половину населения" << endl;
        }

        if (harvest > 0)
        {
            cout << "   Мы собрали " << harvest << " бушелей пшеницы" << " по " << harvest_rate << " бушеля с акра" << endl;
        }

        if (rat_damage > 0)
        {
            cout << "   Крысы истребили " << rat_damage << " бушелей пшеницы, оставив " << wheat << " бушеля в амбарах" << endl;
        }
        else
        {
            cout << "   В закромах города " << wheat << " бушелей пшеницы" << endl;
        }

        cout
            << "   В городе проживает " << population << " человек" << endl
            << "   Город занимает " << area << " акров земли" << endl
            << "   1 акр земли стоит сейчас " << area_price << " бушель." << endl;

        cout << "Что пожелаешь, повелитель?" << endl;

        while (true)
        {
            cout << "Сколько акров земли повелеваешь купить? ";
            int area_to_buy = ReadPositiveNumber();

            int total_price = area_to_buy * area_price;
            if (total_price <= wheat)
            {
                area += area_to_buy;
                wheat -= total_price;
                cout << area_to_buy << " акров куплено за " << total_price << " бушелей" << endl;
                break;
            }
            else
            {
                cout << area_to_buy << " акров стоят " << total_price << " бушелей, а у вас их всего " << wheat << endl;
            }
        }

        while (true)
        {
            cout << "Сколько акров земли повелеваешь продать? ";
            int area_to_sell = ReadPositiveNumber();

            if (area_to_sell <= area)
            {
                int total_price = area_to_sell * area_price;
                area -= area_to_sell;
                wheat += total_price;
                cout << area_to_sell << " акров продано за " << total_price << " бушелей" << endl;
                break;
            }
            else
            {
                NotEnoughArea(area);
            }
        }

        while (true)
        {
            cout << "Сколько бушелей пшеницы повелеваешь съесть? ";
            int wheat_to_eat = ReadPositiveNumber();

            if (wheat_to_eat <= wheat)
            {
                wheat -= wheat_to_eat;
                hungry_villagers = max(population - wheat_to_eat / 20, 0);
                cout << "Накормлено " << population - hungry_villagers << " жителей" << endl;
                break;
            }
            else
            {
                cout << "У вас всего " << wheat << " бушелей" << endl;
            }
        }

        harvest_rate = 1 + rand() % 6;
        while (true)
        {
            cout << "Сколько акров земли повелеваешь засеять? ";
            int area_to_sow = ReadPositiveNumber();
            int wheat_for_seeds = area_to_sow / 2;

            if (area_to_sow > population * 10)
            {
                cout << "Население не справится с такой площадью!" << endl;
            }
            else if (area_to_sow > area)
            {
                NotEnoughArea(area);
            }
            else if (wheat < wheat_for_seeds)
            {
                cout << "Чтобы засеять " << area_to_sow << " акров нужно " << wheat_for_seeds << " бушелей пшеницы на семена" << endl;
            }
            else
            {
                harvest = area_to_sow * harvest_rate;
                wheat -= wheat_for_seeds;
                wheat += harvest;
                break;
            }
        }

        rat_damage = rand() % 701 * wheat / 10000;

        wheat -= rat_damage;

        plague = rand() % 100 < 15;

        newcomers = max(0, min(hungry_villagers / 2 + (5 - harvest) * wheat / 600 + 1, 50));

        int hungry_percentage = hungry_villagers * 100 / population;

        total_hungry_percentage += hungry_percentage;

        population -= hungry_villagers;

        population += newcomers;

        year++;

        if (hungry_percentage > 45)
        {
            cout << "Слишком много жителей умерло от голода!" << endl;
            break;
        }

        ofstream out("save.sav");
        if (out.is_open())
        {
            out << population << ' ' << wheat << ' ' << area << ' ' << hungry_villagers << ' ' << harvest << ' ' << newcomers << ' ' << plague << ' ' << harvest_rate << ' ' << rat_damage << ' ' << total_hungry_percentage << ' ' << year;
            cout << "Игра сохранена" << endl;
        }
        out.close();

        cin.get();
    }

    int p = total_hungry_percentage / (year - 1);
    int l = area / population;

    if (p > 33 || l < 7)
        cout << "Из-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города. "
             << "Теперь вы вынуждены влачить жалкое существование в изгнании" << endl;
    else if (p > 10 || l < 9)
        cout << "Вы правили железной рукой, подобно Нерону и Ивану Грозному. "
             << "Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем" << endl;
    else if (p > 3 || l < 10)
        cout << "Вы справились вполне неплохо, у вас, конечно, есть недоброжелатели, "
             << "но многие хотели бы увидеть вас во главе города снова" << endl;
    else
        cout << "Фантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше" << endl;

    remove("save.sav");

    return 0;
}