#ifndef LATEX_GENERATOR_H_INCLUDED
#define LATEX_GENERATOR_H_INCLUDED

#include "LATEX_AST.h"
#include<vector>
#include<stack>
#include<string>
using namespace std;

string generate_LATEX_from_AST(LATEX_AST_node node)
{
        string current = "";
        string from_children = "";

        for(int i = 0; i < node.children.size(); i++)
        {
            if(node.children[i].label == "paragraph")from_children += "\n\n";
            from_children += generate_LATEX_from_AST(node.children[i]);
        }

        if(node.type == "environment")
            current += "\n\n\\begin{" + node.label + "}\n" + from_children + "\n\\end{" + node.label + "}\n";

        else if(node.type == "command" && node.label != "")
        {
            if(node.parameterized)
            {
                if(node.label == "LARGE_section")current = " {\\section*{\\LARGE{" + from_children + "}}} ";
                else if(node.label == "Large_section") current = " {\\section*{\\Large{" + from_children + "}}} ";
                else if(node.label == "large_section") current = " {\\section*{\\large{" + from_children + "}}} ";
                else if(node.label == "normalsize_section") current = " {\\section*{\\normalsize{" + from_children + "}}} ";
                else current = " {\\" + node.label + "{" + from_children + "}} ";
            }
            else
            {
                current += "\\" + node.label + " " + from_children;
            }
        }
        else if(node.type == "string")
            current += node.string_sequence;
        else
            current += from_children;
        return current;
}


#endif // LATEX_GENERATOR_H_INCLUDED
