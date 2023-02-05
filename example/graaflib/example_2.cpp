#include <string>
#include <iostream>

#include <graaflib/graph.h>

struct user_struct {
	int number{};
	std::string data{};

	bool operator==(const user_struct& rhs) const {
		return number == rhs.number && data == rhs.data;
	}
};

struct user_struct_hash {
	std::size_t operator()(const user_struct& key) const {
		return std::hash<int>()(key.number) ^ (std::hash<std::string>()(key.data) << 1);
	}
};

int main() {

	const user_struct v1{3, "some string data"};
	const user_struct v2{5, "some other string data"};

	const auto graph {graaf::graph<user_struct, user_struct_hash>::builder().vertices({
        {0, v1},
        {1, v2}
    }).edges({
        {0, 1}
    }).build()};

    std::cout << graph.vertex_count() << std::endl;
}
