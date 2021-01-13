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
	std::string(indent_size * indent_level, ' ') + opening_tag();
    for (auto child=children.begin(); child != children.end(); child++)
	text += "\n" + (*child)->get_text(indent_level + 1, indent_size);
    text += "\n" + std::string(indent_size * indent_level, ' ') + closing_tag();
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
    


spell::node* spell::node::get_child_by_id(std::string id, int recursion_level)
{
    bool recurse = recursion_level > 0 || recursion_level < 0;

    for (auto child = children.begin(); child != children.end(); child++) {
	if ((*child)->id == id)
	    return *child;
	else if (recurse) {
	    spell::node* n = (*child)->get_child_by_id(id, recursion_level-1);
	    if (n != nullptr)
		return n;
	}
    }

    return nullptr;
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
    return std::string(indent_level * indent_size, ' ') + text;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * convenience functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

spell::node* spell::text(std::string text) { return new spell::text_node(text); }

#define SPELL_DEFINE_NODE_TYPE(TYPE) \
    spell::node* spell::TYPE(std::string text) \
    { return new spell::node(#TYPE, "", {}, { new spell::text_node(text) }); } \
    spell::node* spell::TYPE(spell::node_list children)		       \
    { return new spell::node(#TYPE, "", {}, children); }		\
    spell::node* spell::TYPE(std::string id, spell::node_list children) \
    { return new spell::node(#TYPE, id, {}, children); }		\
    spell::node* spell::TYPE(std::string id, spell::string_list classes, spell::node_list children) \
    { return new spell::node(#TYPE, id, classes, children); }

SPELL_DEFINE_NODE_TYPE(div)
SPELL_DEFINE_NODE_TYPE(p)
SPELL_DEFINE_NODE_TYPE(h1)
