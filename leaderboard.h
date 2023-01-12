/*!
\file
\brief Заголовочный файл с описанием класса Leaderboard

Данный файл содержит в себе определение класса Leaderboard
*/

#pragma once
#ifndef Lead_Lead_H_20222112
#define Lead_Lead_H_20222112

#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <time.h>
#include <iostream>

/*!
\brief Класс для хранения таблицы лидеров и работы с ней
*/


class Leaderboard {
public:
/*!
\brief Структура для хранения времени отправок пользователя
*/
	struct User {
		User() = default;
		User(std::string name, std::vector<time_t> submits);
		~User() = default;
		User(const User& copy) = default;
		std::string name;
		std::vector<time_t> submits;
	};
	Leaderboard() = default;
	~Leaderboard() = default;
	Leaderboard(const Leaderboard& copy) = default;
	/*!
	\brief Метод для обновления информации при принятии новых изображений
	\param name Имя пользователя (если не указано - его id)
	\param num Количество изображений, принятых за последнюю посылку
	*/
	void update(std::string& name, int num);
	/*!
	\brief Метод для получения таблицы лидеров заданного размера за заданный период
	\param lim Размер таблицы лидеров
	\param vec Вектор, в котором таблица лидеров будет сохранена
	\param type Определитель временного промежутка: 1 - день, 2 - неделя, 3 - всё время
	*/
	void top(int lim, std::vector<std::pair<std::string, int>>& vec, int type);

private:
	std::vector<User> list_all;
	int _find(std::string name);
	
};

#endif