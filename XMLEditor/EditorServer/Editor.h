#pragma once
#include "string"
#include "vector"
#include "iostream"
#include "tinyxml2.h"

using namespace std;
class Editor
{

std::string command;
std::string tag_name;
std::string tag_value;

vector<string> commands;

public:
   tinyxml2::XMLDocument doc;  

	void add (string tag_name, string tag_value);
	string get (string tag_name);
	void set (string tag_name, string tag_value);
	Editor(void);
	Editor(char* _query);
	~Editor(void);
};

