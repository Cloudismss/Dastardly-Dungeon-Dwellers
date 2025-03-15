#include "BoxArt.h"

#include <iomanip>
#include <iostream>
#include <string>

namespace art
{
  namespace box
  {
    void displayMeInABox(const std::string &message)
    {
      // Offsets are used to clean up integer division spacing
      int offset = 0;
      if (message.length() % 2 == 0)
        offset = 1;

      // Adjusts box width based on message size
      int boxWidth = 0;
      int indent = 0;
      int borderSpacing = 0;
      if (message.length() < 36)
      {
        boxWidth = 46;
        indent = 10;
      }
      else
      {
        boxWidth = 56;
        indent = 5;
      }
      borderSpacing = ((boxWidth - 4) / 2);

      std::cout << std::setw(indent) << "." << std::setfill('-') << std::setw(boxWidth) << ".\n" << std::setfill(' ')
                << std::setw(indent) << "|" << std::setfill(' ') << std::setw(boxWidth) << "|\n"
                << std::setw(indent) << "|" << std::setw(offset + borderSpacing - message.length() / 2) << " " << message << std::setw(borderSpacing - message.length() / 2) << " " << " |\n"
                << std::setw(indent) << "|" << std::setfill(' ') << std::setw(boxWidth) << "|\n"
                << std::setw(indent) << "'" << std::setfill('-') << std::setw(boxWidth) << "'\n" << std::setfill(' ')
                << "\n";
    }

    void displayMeInABox(const std::string &message1, const std::string &message2)
    {
      // Offsets are used to clean up integer division spacing
      int offset1 = 0;
      int offset2 = 0;
      if (message1.length() % 2 == 0)
        offset1 = 1;
      if (message2.length() % 2 == 0)
        offset2 = 1;

      // Adjusts box width based on message size
      int boxWidth = 0;
      int indent = 0;
      int borderSpacing = 0;
      if (message2.length() < 36)
      {
        boxWidth = 46;
        indent = 10;
      }
      else
      {
        boxWidth = 56;
        indent = 5;
      }
      borderSpacing = ((boxWidth - 4) / 2);

      std::cout << std::setw(indent) << "." << std::setfill('-') << std::setw(boxWidth) << ".\n" << std::setfill(' ')
                << std::setw(indent) << "|" << std::setfill(' ') << std::setw(boxWidth) << "|\n"
                << std::setw(indent) << "|" << std::setw(offset1 + borderSpacing - message1.length() / 2) << " " << message1 << std::setw(borderSpacing - message1.length() / 2) << " " << " |\n"
                << std::setw(indent) << "|" << std::setw(offset2 + borderSpacing - message2.length() / 2) << " " << message2 << std::setw(borderSpacing - message2.length() / 2) << " " << " |\n"
                << std::setw(indent) << "|" << std::setfill(' ') << std::setw(boxWidth) << "|\n"
                << std::setw(indent) << "'" << std::setfill('-') << std::setw(boxWidth) << "'\n" << std::setfill(' ')
                << "\n";
    }

    void monologueInABox(const std::string &message)
    {
      std::cout << "." << std::setfill('-') << std::setw(3 + message.length()) << "." << "\n" << std::setfill(' ')
                << "| " << message << " |\n"
                << "'" << std::setfill('-') << std::setw(3 + message.length()) << "'" << "\n\n" << std::setfill(' ');
    }
  }
}
