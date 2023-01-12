/*!
\file
\brief ������������ ���� � ��������� ������ Leaderboard

������ ���� �������� � ���� ����������� ������ Leaderboard
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
\brief ����� ��� �������� ������� ������� � ������ � ���
*/


class Leaderboard {
public:
/*!
\brief ��������� ��� �������� ������� �������� ������������
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
	\brief ����� ��� ���������� ���������� ��� �������� ����� �����������
	\param name ��� ������������ (���� �� ������� - ��� id)
	\param num ���������� �����������, �������� �� ��������� �������
	*/
	void update(std::string& name, int num);
	/*!
	\brief ����� ��� ��������� ������� ������� ��������� ������� �� �������� ������
	\param lim ������ ������� �������
	\param vec ������, � ������� ������� ������� ����� ���������
	\param type ������������ ���������� ����������: 1 - ����, 2 - ������, 3 - �� �����
	*/
	void top(int lim, std::vector<std::pair<std::string, int>>& vec, int type);

private:
	std::vector<User> list_all;
	int _find(std::string name);
	
};

#endif