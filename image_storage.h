/*!
\file
\brief Заголовочный файл с описанием класса image_storage
*/

#pragma once
#ifndef ImSt_ImSt_H_20220612
#define ImSt_ImSt_H_20220612

#include <string>
#include <set>
#include <fstream>

/*!
\brief Класс для хранения для сохранения принятых фотографий, хранения их хешей и сравнения отправляемых фотографий с уже принятыми
*/

class ImageStorage {
public:
	ImageStorage() = default;
	~ImageStorage() = default;
	ImageStorage(const ImageStorage& copy) = default;
	/*!
	\brief Метод для обработки отправленных фотографий, их сохранения и хеширования

	Возвращает 0, если изображение принято, и 1, если данное изображение уже отправлялось ранее
	\param username Имя пользователя (если не указано - его id)
	\param img Изображение, записанное в виде строки
	*/
	int add(std::string username, std::string& img);

private:
	std::set <int> img_st;
	int name = 1;
};

#endif