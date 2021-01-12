#include <iostream>

#include "../src/spell.hpp"

int main(int argc, char** argv)
{
    spell::node root("div", "", {},
		     { new spell::node("h1", "", {}, { new spell::text_node("hello world!") }),
		       new spell::node("p", "", {},
				       { new spell::text_node("have a lovely day c:") })
		     });
    std::cout << root.get_text(0, 4) << std::endl;
    return 0;
}
