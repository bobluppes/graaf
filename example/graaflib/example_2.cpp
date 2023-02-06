#include <string>
#include <iostream>

#include <graaflib/directed_graph.h>

struct user_struct {
	int number{};
	std::string data{};

	bool operator==(const user_struct& rhs) const {
		return number == rhs.number && data == rhs.data;
	}
};

int main() {

	const user_struct v1{3, "some string data"};
	const user_struct v2{5, "some other string data"};

	const auto graph {graaf::directed_graph<user_struct>::builder().vertices({
        {0, v1},
        {1, v2}
    }).edges({
        {0, 1}
    }).build()};

    std::cout << graph.vertex_count() << std::endl;
}
