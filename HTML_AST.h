#ifndef HTML_AST_H_INCLUDED
#define HTML_AST_H_INCLUDED

#include<vector>
#include<stack>
#include<string>
using namespace std;

struct HTML_AST_node
{
    string label;
    vector<string> attributes;
    vector<HTML_AST_node> children;
};

HTML_AST_node root_tag;
stack<HTML_AST_node> tag_sequence;

enum status {TAG_S, TAG_E, TAG_S_E};
status tag_status;

void initialize_the_tag(string s);
void end_the_tag();
void add_string_on_top(string s);
void delete_string_on_top();

void initialize_the_tag(string s)
{
    HTML_AST_node node;
    string tag = "";
    int i = 0;
    while(s[i] != ' ' && s[i] != '>' && s[i] != '/' && s[i] != '-')
    {
        if(s[i] != '<')tag += (s[i] >= 97 || s[i] >= 48 && s[i] < 58 || s[i] == 33)?s[i]:s[i]+32;
        i++;
    }

    if(tag == "")
    {
        //cout << s << endl;
        add_string_on_top(s);
        return;
    }
    if(tag == "br")
    {
        if(tag_sequence.top().label == "string")
            tag += "1";
        else
            tag += "2";
    }
    delete_string_on_top();
    node.label = tag;
    string node_attribute = "";

    if(tag != "!")
    {
        bool attval = true;
        while(s[i] != '>')
        {
            if(attval && (s[i] == ' ' || s[i] == '/'))
            {
                if(node_attribute != "")node.attributes.push_back(node_attribute);
                node_attribute = "";
            }
            else node_attribute += s[i];
            if(s[i] == 34)attval ^= 1;
            i++;
        }
        if(node_attribute != "")node.attributes.push_back(node_attribute);
    }
    else
    {
        node.label = "comment";
    }
    if(tag_status == TAG_S_E)
    {
        if(tag[0] == '!')node.label = "docstart";
        if(node.label != "docstart")
        {
            HTML_AST_node parent_tag = tag_sequence.top();
            //cout << node.label << "'s parent is " << parent_tag.label << endl;
            parent_tag.children.push_back(node);
            tag_sequence.pop();
            tag_sequence.push(parent_tag);
        }
        else
        {
            tag_sequence.push(node);
        }
    }
    else
    {
        tag_sequence.push(node);
    }
}



void end_the_tag()
{
    delete_string_on_top();
    HTML_AST_node finished_tag = tag_sequence.top();
    tag_sequence.pop();
    if(!tag_sequence.empty())
    {
        HTML_AST_node parent_tag = tag_sequence.top();
        //cout << finished_tag.label << "'s parent is " << parent_tag.label << endl;
        parent_tag.children.push_back(finished_tag);
        tag_sequence.pop();
        tag_sequence.push(parent_tag);
    }
    else root_tag = finished_tag;
}



void add_string_on_top(string s)
{
    HTML_AST_node preceding_node = tag_sequence.top();
    if(preceding_node.label == "string")
    {
        preceding_node.attributes.push_back(s);
        tag_sequence.pop();
        tag_sequence.push(preceding_node);
    }
    else
    {
        HTML_AST_node string_node;
        string_node.label = "string";
        string_node.attributes.push_back(s);
        tag_sequence.pop();
        tag_sequence.push(preceding_node);
        tag_sequence.push(string_node);
    }
}



void delete_string_on_top()
{
    if(!tag_sequence.empty())
    {
        HTML_AST_node preceding_node = tag_sequence.top();
        if(preceding_node.label == "string")
        {
            tag_sequence.pop();
            HTML_AST_node even_more_preceding_node = tag_sequence.top();
            even_more_preceding_node.children.push_back(preceding_node);
            tag_sequence.pop();
            tag_sequence.push(even_more_preceding_node);
        }
    }
}




#endif // HTML_AST_H_INCLUDED
