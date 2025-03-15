#ifndef BOXART_H
#define BOXART_H

#include <string>

namespace art
{
 namespace box
 {
    void displayMeInABox(const std::string &message);
    void displayMeInABox(const std::string &message1, const std::string &message2);
    void monologueInABox(const std::string &message);
 }
}

#endif // BOXART_H
