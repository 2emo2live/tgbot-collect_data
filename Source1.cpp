#include <set>

int main() {
	std::set <unsigned char*> img_st;
	unsigned char img_hash[32];
	img_hash = "Hello, world";
	img_st.insert(img_hash);
	img_hash = "Goodbye";
	img_st.insert(img_hash);
}