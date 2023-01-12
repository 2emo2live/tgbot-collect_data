/*!
\file
\brief ������������ ���� � ��������� ������ image_storage
*/

#pragma once
#ifndef ImSt_ImSt_H_20220612
#define ImSt_ImSt_H_20220612

#include <string>
#include <set>
#include <fstream>

/*!
\brief ����� ��� �������� ��� ���������� �������� ����������, �������� �� ����� � ��������� ������������ ���������� � ��� ���������
*/

class ImageStorage {
public:
	ImageStorage() = default;
	~ImageStorage() = default;
	ImageStorage(const ImageStorage& copy) = default;
	/*!
	\brief ����� ��� ��������� ������������ ����������, �� ���������� � �����������

	���������� 0, ���� ����������� �������, � 1, ���� ������ ����������� ��� ������������ �����
	\param username ��� ������������ (���� �� ������� - ��� id)
	\param img �����������, ���������� � ���� ������
	*/
	int add(std::string username, std::string& img);

private:
	std::set <int> img_st;
	int name = 1;
};

#endif