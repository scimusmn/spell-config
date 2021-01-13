/** @file Declare spell-config's classes and functions */

#ifndef SPELL_CONFIG_HPP
#define SPELL_CONFIG_HPP

#include <vector>
#include <list>
#include <string>

namespace spell
{
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     *
     * DOM elements
     *
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     */
    
    /** @class Base class for all other DOM nodes. */
    class node
    {
    private:
	std::string opening_tag();
	std::string closing_tag();
	
    public:
	/** The DOM node's type */
	std::string type;
	/** The DOM node's id */
	std::string id;
	/** The DOM node's CSS classes */
	std::vector<std::string> classes;
	/** The DOM node's children. */
	std::list<spell::node*> children;

	/** @brief (constructor)
	 *
	 * @param[in] type The type of the DOM node (e.g. div, h1, etc)
	 * @param[in] id The ID to use for the DOM node.
	 * @param[in] classes A list of CSS classes to apply to the node.
	 * @param[in] children A list of pointers to the node's children.
	 *
	 */
	node(std::string type, std::string id,
		 std::initializer_list<std::string> classes,
		 std::initializer_list<node*> children);
	/** @brief (destructor) */
	~node();

	/** @brief Get the HTML for the node.
	 *
	 * @param[in] indent_level The level of indentation to use
	 * @param[in] indent_size The size of each indentation
	 *
	 * @returns A string containing the prettified HTML.
	 */
	virtual std::string get_text(int indent_level, int indent_size);

	/** @brief Add a child to the node.
	 *
	 * @param[in] node A pointer to the node to add as a child.
	 */
	void add_child(spell::node* node);

	/** @brief Add a group of children to the node.
	 *
	 * @param[in] nodes A list of nodes to add to the node's children.
	 */
	void add_children(std::initializer_list<node*> nodes);

	node* get_child_by_id(std::string id, int recursion_level=-1);
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
