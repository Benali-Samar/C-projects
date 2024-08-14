#include <iostream>
#include <fstream>
#include <string>
#include <gumbo.h>

// Function to recursively search for specific content in HTML
void searchForContent(GumboNode* node) {
    if (node->type != GUMBO_NODE_ELEMENT) {
        return;
    }

    // Check for specific element IDs
    if (node->v.element.tag == GUMBO_TAG_SPAN) {
        GumboAttribute* id_attr = gumbo_get_attribute(&node->v.element.attributes, "id");
        if (id_attr) {
            std::string id_value(id_attr->value);
            if (id_value == "identity" || id_value == "software" || id_value == "hardware" ||
                id_value == "uptime" || id_value == "datetime" || id_value == "dhcp" ||
                id_value == "ipv4addr" || id_value == "ipv4mask" || id_value == "ipv6addr" ||
                id_value == "macaddr" || id_value == "gateway" || id_value == "nameserver" || id_value == "sipinfo-reg-1" || id_value == "sipinfo-last-1") {
                if (node->v.element.children.length > 0) {
                    GumboNode* text_node = static_cast<GumboNode*>(node->v.element.children.data[0]);
                    if (text_node->type == GUMBO_NODE_TEXT) {
                        std::cout << id_value << ": " << text_node->v.text.text << std::endl;
                    }
                }
            }
        }
    }

    // Recursively search children
    for (int i = 0; i < node->v.element.children.length; ++i) {
        searchForContent(static_cast<GumboNode*>(node->v.element.children.data[i]));
    }
}

std::string readFileToString(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return "";
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    file.close();
    return content;
}

int main() {
    const std::string filename = "index.html";
    std::string htmlContent = readFileToString(filename);

    if (htmlContent.empty()) {
        std::cerr << "Failed to read HTML content from file." << std::endl;
        return 1;
    }

    GumboOutput* output = gumbo_parse(htmlContent.c_str());
    if (output == nullptr) {
        std::cerr << "Failed to parse HTML content." << std::endl;
        return 1;
    }

    searchForContent(output->root);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
    return 0;
}

