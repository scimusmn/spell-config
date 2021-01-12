#include "spell.hpp"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * node
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

spell::node::node(std::string type, std::string id,
		  std::initializer_list<std::string> classes,
		  std::initializer_list<node*> children)
    : type(type), id(id), classes(classes), children(children)
{}



spell::node::~node()
{
    for (auto child = children.begin(); child != children.end(); child++)
	delete *child;
}



std::string spell::node::get_text(int indent_level, int indent_size)
{
    std::string text =
	"\n" + std::string(indent_size * indent_level, ' ') + opening_tag();
    for (auto child=children.begin(); child != children.end(); child++)
	text += (*child)->get_text(indent_level + 1, indent_size);
    text += closing_tag() + "\n";
    return text;
}



void spell::node::add_child(spell::node* node)
{
    children.push_back(node);
}



void spell::node::add_children(std::initializer_list<spell::node*> nodes)
{
    children.insert(children.end(), nodes.begin(), nodes.end());
}
    


std::string spell::node::opening_tag()
{
    std::string class_str = "";
    if (!classes.empty()) {
	class_str = " class=\"";
	for (int i=0; i<classes.size()-1; i++)
	    class_str += classes[i] + " ";
	class_str += classes.back() + "\" ";
    }

    std::string id_str = "";
    if (id != "") {
	id_str = " id=\"" + id + "\" ";
    }

    std::string tag = "<" + type + class_str + id_str + ">";
    return tag;
}



std::string spell::node::closing_tag()
{
    std::string tag = "</" + type + ">";
    return tag;
}



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
 *
 * Text node
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

spell::text_node::text_node(std::string text) : node("", "", {}, {}), text(text) {}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

std::string spell::text_node::get_text(int indent_level, int indent_size)
{
    return text;
}
