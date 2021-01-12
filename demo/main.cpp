#include <iostream>

#include "../src/spell.hpp"

int main(int argc, char** argv)
{
    spell::node* root = spell::div
	({ spell::h1("hello, world!"),
	   spell::div
	   ({ spell::p("it's nice to see you again c:") }),
	});
		
    std::cout << root->get_text(0, 4) << std::endl;
    delete root;
    return 0;
}
