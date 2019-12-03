#ifndef LATEX_AST_H_INCLUDED
#define LATEX_AST_H_INCLUDED

#include "HTML_AST.h"
#include<vector>
#include<stack>
#include<string>
using namespace std;


struct LATEX_AST_node
{
    string type;
    string label;
    string string_sequence;
    vector<LATEX_AST_node> children;
    bool parameterized;
};

LATEX_AST_node LATEX_root_tag;
vector<string> preamble;

    LATEX_AST_node build_LATEX_AST(HTML_AST_node node, HTML_AST_node parent_node)
    {
        LATEX_AST_node latex_node;

        if(node.label == "html")
        {
            latex_node.type = "environment";
            latex_node.label = "document";
            latex_node.parameterized = false;
            latex_node.string_sequence = "";
        }

        else if(node.label == "docstart" || node.label == "head" || node.label == "body" || node.label == "dd" || node.label == "div")
        {
            latex_node.type = "";
            latex_node.label = "";
            latex_node.parameterized = false;
            latex_node.string_sequence = "";
        }

        else if(node.label == "p")
        {
            latex_node.type = "";
            latex_node.label = "paragraph";
            latex_node.parameterized = false;
            latex_node.string_sequence = "";
        }

        else if(node.label == "title")
        {
            latex_node.type = "command";
            latex_node.label = "maketitle";
            latex_node.parameterized = false;
            latex_node.string_sequence = "";
        }

        else if(node.label == "br1")
        {
            latex_node.type = "command";
            latex_node.label = "newline";
            latex_node.parameterized = false;
            latex_node.string_sequence = "";
        }

        else if(node.label == "br2")
        {
            latex_node.type = "command";
            latex_node.label = "vspace{5mm}";
            latex_node.parameterized = false;
            latex_node.string_sequence = "";
        }

        else if(node.label == "center")
        {
            latex_node.type = "environment";
            latex_node.label = "center";
            latex_node.parameterized = false;
            latex_node.string_sequence = "";
        }

        else if(node.label == "h1")
        {
            latex_node.type = "command";
            latex_node.label = "LARGE_section";
            latex_node.parameterized = true;
            latex_node.string_sequence = "";
        }

        else if(node.label == "h2")
        {
            latex_node.type = "command";
            latex_node.label = "Large_section";
            latex_node.parameterized = true;
            latex_node.string_sequence = "";
        }

        else if(node.label == "h3")
        {
            latex_node.type = "command";
            latex_node.label = "large_section";
            latex_node.parameterized = true;
            latex_node.string_sequence = "";
        }

        else if(node.label == "h4")
        {
            latex_node.type = "command";
            latex_node.label = "normalsize_section";
            latex_node.parameterized = true;
            latex_node.string_sequence = "";
        }

        else if(node.label == "li" || node.label == "dt")
        {
            latex_node.type = "command";
            latex_node.label = "item";
            latex_node.parameterized = false;
            latex_node.string_sequence = "";
        }

        else if(node.label == "ul")
        {
            latex_node.type = "environment";
            latex_node.label = "itemize";
            latex_node.parameterized = false;
            latex_node.string_sequence = "";
        }

        else if(node.label == "ol")
        {
            latex_node.type = "environment";
            latex_node.label = "enumerate";
            latex_node.parameterized = false;
            latex_node.string_sequence = "";
        }

        else if(node.label == "dl")
        {
            latex_node.type = "environment";
            latex_node.label = "description";
            latex_node.parameterized = false;
            latex_node.string_sequence = "";
        }

        else if(node.label == "b" || node.label == "strong")
        {
            latex_node.type = "command";
            latex_node.label = "textbf";
            latex_node.parameterized = true;
            latex_node.string_sequence = "";
        }

        else if(node.label == "i")
        {
            latex_node.type = "command";
            latex_node.label = "textit";
            latex_node.parameterized = true;
            latex_node.string_sequence = "";
        }

        else if(node.label == "u")
        {
            latex_node.type = "command";
            latex_node.label = "underline";
            latex_node.parameterized = true;
            latex_node.string_sequence = "";
        }

        else if(node.label == "em")
        {
            latex_node.type = "command";
            latex_node.label = "emph";
            latex_node.parameterized = true;
            latex_node.string_sequence = "";
        }

        else if(node.label == "tt")
        {
            latex_node.type = "command";
            latex_node.label = "texttt";
            latex_node.parameterized = true;
            latex_node.string_sequence = "";
        }

        else if(node.label == "small")
        {
            latex_node.type = "command";
            latex_node.label = "small";
            latex_node.parameterized = true;
            latex_node.string_sequence = "";
        }

        else if(node.label == "sup")
        {
            latex_node.type = "command";
            latex_node.label = "textsuperscript";
            latex_node.parameterized = true;
            latex_node.string_sequence = "";
        }

        else if(node.label == "sub")
        {
            latex_node.type = "command";
            latex_node.label = "textsubscript";
            latex_node.parameterized = true;
            latex_node.string_sequence = "";
        }

        else if(node.label == "font")
        {
            latex_node.type = "command";
            latex_node.label = "";
            string attr;
            for(int i = 0; i < node.attributes.size(); i++)
            {
                if(node.attributes[i].find("size=") != string::npos)
                {
                    attr = node.attributes[i];
                    int attr_val_pos = attr.find("=");
                    string font_size = attr.substr(attr_val_pos+2, attr.size() - attr_val_pos - 3);
                    if(font_size.size() == 1)
                    {
                        if(font_size == "0")latex_node.label = "tiny";
                        if(font_size == "1")latex_node.label = "scriptsize";
                        if(font_size == "2")latex_node.label = "footnotesize";
                        if(font_size == "3")latex_node.label = "small";
                        if(font_size == "4")latex_node.label = "normalsize";
                        if(font_size == "5")latex_node.label = "large";
                        if(font_size == "6")latex_node.label = "Large";
                        if(font_size == "7")latex_node.label = "LARGE";
                    }
                    else latex_node.label = "LARGE";
                    break;
                }
            }

            latex_node.parameterized = true;
            latex_node.string_sequence = "";
        }

        else if(node.label == "a")
        {
            preamble.push_back("\\usepackage{hyperref}");
            latex_node.type = "command";
            latex_node.label = "";
            string attr;
            for(int i = 0; i < node.attributes.size(); i++)
            {
                if(node.attributes[i].find("href=") != string::npos)
                {
                    attr = node.attributes[i];
                    int attr_val_pos = attr.find("=");
                    string url = attr.substr(attr_val_pos+2, attr.size() - attr_val_pos - 3);
                    latex_node.label = "href{" + url + "}";
                    break;
                }
            }

            latex_node.parameterized = true;
            latex_node.string_sequence = "";
        }

        else if(node.label == "img")
        {
            preamble.push_back("\\usepackage{graphicx}");
            preamble.push_back("\\graphicspath{{./}}");
            latex_node.type = "command";
            string image_width = "";
            string image_height = "";
            string image_name = "";
            string attr = "";
            string label = "";
            for(int i = 0; i < node.attributes.size(); i++)
            {
                if(node.attributes[i].find("src=") != string::npos)
                {
                    attr = node.attributes[i];
                    int attr_val_pos = attr.find("=");
                    image_name = attr.substr(attr_val_pos+2, attr.size() - attr_val_pos - 3);
                }

                else if(node.attributes[i].find("width=") != string::npos)
                {
                    attr = node.attributes[i];
                    int attr_val_pos = attr.find("=");
                    image_width = attr.substr(attr_val_pos+2, attr.size() - attr_val_pos - 3);
                }

                else if(node.attributes[i].find("height=") != string::npos)
                {
                    attr = node.attributes[i];
                    int attr_val_pos = attr.find("=");
                    image_height = attr.substr(attr_val_pos+2, attr.size() - attr_val_pos - 3);
                }
            }
            if(image_name != "")
            {
                label += "includegraphics";
                if(image_width != "" && image_height == "")label += "[width = " + image_width + "cm]";
                else if(image_width == "" && image_height != "")label += "[height = " + image_height + "cm]";
                else if(image_width != "" && image_height != "")label += "[width = " + image_width + "cm, height = " + image_height + "cm]";
                label += "{" + image_name + "}";
            }
            latex_node.label = label;

            latex_node.parameterized = false;
            latex_node.string_sequence = "";
        }

        else if(node.label == "figure")
        {
            latex_node.type = "environment";
            latex_node.label = "figure";
            latex_node.parameterized = false;
            latex_node.string_sequence = "";
        }

        else if(node.label == "figurecaption")
        {
            latex_node.type = "command";
            latex_node.label = "caption";
            latex_node.parameterized = true;
            latex_node.string_sequence = "";
        }

        else if(node.label == "comment")
        {
            preamble.push_back("\\usepackage{verbatim}");
            latex_node.type = "environment";
            latex_node.label = "comment";
            latex_node.parameterized = false;
            latex_node.string_sequence = "";
        }

        else if(node.label == "string")
        {
            if(parent_node.label == "title")
            {
                string s = "";
                for(int i = 0; i < node.attributes.size(); i++)
                    s += node.attributes[i] + ((i < node.attributes.size()) ? " " : "");
                if(s != "")preamble.push_back("\\title{" + s + "}");
                latex_node.type = "NULL";
                latex_node.label = "NULL";
                latex_node.parameterized = false;
                latex_node.string_sequence = "";
                return latex_node;
            }

            latex_node.type = "string";
            latex_node.label = "";
            latex_node.parameterized = false;
            latex_node.string_sequence = "";
            string s = (parent_node.label == "dt") ? "[" : "";

            for(int i = 0; i < node.attributes.size(); i++)
            {
                s += node.attributes[i];
                if(parent_node.label != "comment" && i < node.attributes.size()-1) s += " ";
            }
            if(parent_node.label == "dt") s += "]";
            latex_node.string_sequence = s;
        }

        else
        {
            latex_node.type = "NULL";
            latex_node.label = "NULL";
            latex_node.parameterized = false;
            latex_node.string_sequence = "";
            return latex_node;
        }

        for(int i = 0; i < node.children.size(); i++)
        {
            LATEX_AST_node child = build_LATEX_AST(node.children[i], node);
            if(child.type != "NULL")
            {
                latex_node.children.push_back(child);
            }
        }
        return latex_node;
    }


#endif // LATEX_AST_H_INCLUDED
