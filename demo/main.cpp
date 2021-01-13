#include <iostream>

#include "../src/spell.hpp"

int main(int argc, char** argv)
{
    spell::node* root = spell::div
	("root",
	 { spell::h1("hello, world!"),
	   spell::div
	   ("content",
	    { "highlight", "centered" },
	    { spell::p("it's nice to see you again c:") }),
	});
		
    std::cout << root->get_text(0, 4) << std::endl;

    spell::node* div = root->get_child_by_id("content");
    std::cout << div->classes[0] << std::endl;
    
    delete root;
    return 0;
}
