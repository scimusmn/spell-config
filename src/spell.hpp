/** @file Declare spell-config's classes and functions */

#ifndef SPELL_CONFIG_HPP
#define SPELL_CONFIG_HPP

#include <vector>
#include <list>
#include <string>

namespace spell
{
    /** @brief Base class for all other DOM nodes. */
    class node
    {
    private:
	std::string type;
	std::string id;
	std::vector<std::string> classes;
	std::list<spell::node*> children;

	std::string opening_tag();
	std::string closing_tag();
	
    public:
	node(std::string type, std::string id,
		 std::initializer_list<std::string> classes,
		 std::initializer_list<node*> children);
	~node();

	virtual std::string get_text(int indent_level, int indent_size);
	void add_child(spell::node* node);
	void add_children(std::initializer_list<node*> nodes);
    };

    typedef std::initializer_list<std::string> string_list;
    typedef std::initializer_list<node*> node_list;

    /** @brief DOM text nodes. */
    class text_node : public node
    {
    private:
	std::string text;
    public:
	text_node(std::string text);
	std::string get_text(int indent_level, int indent_size);
    };

    /* convenience functions */
    node* text(std::string text);
    
#define SPELL_DECLARE_NODE_TYPE(TYPE) \
    node* TYPE(std::string text); \
    node* TYPE(node_list children);		    \
    node* TYPE(std::string id, node_list children); \
    node* TYPE(std::string id, string_list classes, node_list children);

    SPELL_DECLARE_NODE_TYPE(div)
    SPELL_DECLARE_NODE_TYPE(p)
    SPELL_DECLARE_NODE_TYPE(h1)
}

#endif
