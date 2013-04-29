#include "Editor.h"


Editor::Editor(void)
{

}


Editor::Editor(char* _query)
{
	commands.push_back("add");
	commands.push_back("set");
	commands.push_back("get");
}





Editor::~Editor(void)
{
}
void Editor::add (string tag_name, string tag_value)
{
	//here must be realisation using tinyhml
}
string Editor::get (string tag_name)
{
	return tag_name;
}
void Editor::set (string tag_name, string tag_value)
{
}