#include "image_storage.h"

int ImageStorage::add(std::string username, std::string& img)
{
	int img_hash = std::hash<std::string>{}(img);
	int len = img_st.size();
	img_st.insert(img_hash);
	if (len == img_st.size()) {
		return 1;
	}
	else {
		std::ofstream out;
		out.open("../images/" + username + '_' + std::to_string(name) + ".jpg", std::ios::binary);
//		out.open(username + '_' + std::to_string(name) + ".jpg", std::ios::binary);
		name++;
		out << img;
		out.close();
		return 0;
	}
}