#include "leaderboard.h"

void Leaderboard::update(std::string& name, int num) {
	int i = _find(name);
	if (i == -1)
		list_all.push_back(User(name, std::vector<time_t>(num, time(nullptr))));
	else
		for (size_t j = 0; j < num; j++)
			list_all[i].submits.push_back(time(nullptr));
	std::sort(list_all.begin(), list_all.end(),
		[](User a, User b) { return a.submits.size() > b.submits.size(); });
}

void Leaderboard::top(int lim, std::vector<std::pair<std::string, int>>& vec, int type) {
	std::vector<std::pair<std::string, int>> list;
	if (type != 3) {
		time_t now = time(nullptr);
		int border = 0;
		if (type == 1)
			border = 1;
		else if (type == 2)
			border = 7;
		for (auto i : list_all) {
			int score = 0;
			for (auto j : i.submits) {
				time_t diff = (now - j) / 86400;
				//TODO: проверить, нужно ли округление
				if (diff <= border)
					score++;
			}
			if (score != 0) {
				list.push_back(std::make_pair(i.name, score));
			}
		}
	}
	else
		for (auto i : list_all)
			list.push_back(std::make_pair(i.name, i.submits.size()));
	if (lim <= list.size())
		std::copy(list.begin(), list.begin() + lim, std::back_inserter(vec));
	else
		std::copy(list.begin(), list.end(), std::back_inserter(vec));
}

int Leaderboard::_find(std::string name)
{
	for (size_t i = 0; i < list_all.size(); i++) {
		if (list_all[i].name == name)
			return i;
	}
	return -1;
}

Leaderboard::User::User(std::string name, std::vector<time_t> submits)
	: name(name), submits(submits)
{
}