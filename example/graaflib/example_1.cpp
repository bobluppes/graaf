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

	graaf::directed_graph<user_struct> example_graph{
		{{0, v1}, {1, v2}}, 	// vertices
		{{0, 1}}				// edges
	};

	std::cout << example_graph.vertex_count() << std::endl;
}
