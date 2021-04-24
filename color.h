
#ifndef COLOR_H
#define COLOR_H
#include <string>

/*


*REMINDER*: the following method make use of ANSI escape codes
            and hence is suggested to be operated in Unix-like system

This header provide functions to change the color of text and background
Detailed implementation see color.cpp

Colors include:
black, red, green, yellow, blue, magenta, cyan, white

Functions:

1.  color.set(string color_to_change, string optional_attribute <optional>)

    To set color of the frontground afterwards into color of color_to_change

    Input:
      color_to_change: the color wanted to change
      optional_attribute <optional>: (default: "normal") accept 2 kind of strings and do works respectively
        "bright": the color of color_to_change will be brighter
        "background": the color set will be on background instead of frontground

    Output:
      None


2.  color.reset()

    To reset all color changes made.

    Input:
      None

    Output:
      None


3.  color.setphrase(string string_to_color, string front_color <optional>, string brightness <optional>, string back_color <optional>)

    Return a particular string with color changed, reset color afterwards.

    Input:
      string_to_color: the string wanted to be colored
      front_color <optional>: (default: "normal") to set the frontground color of string_to_color into front_color
      brightness <optional>: (default: "normal") the color of front_color will be brighter if "bright" is entered
      back_color <optional>: (default: "normal") to set the background color of string_to_color into back_color

    Output:
      Return string_to_color with color changed, reset color afterwards.


Example: (all output are "text")
  color.set("magenta", "bright");
  color.set("black", "background");
  cout << "text" << endl;                                               // frontground: bright magenta, background: black
  color.reset();
  cout << "text" << endl;                                               // frontground: default, background: default
  cout << color.setphrase("text", "red", "bright", "green") << endl;    // frontground: bright red, background: green
  cout << "text" << endl;                                               // frontground: default, background: default
  cout << color.setphrase("text", "white") << endl;                     // frontground: white, background: default


*/

class Color{
public:

  // input: color, attribute
  // output: ANSI escape codes of that color and brightness
  void set(std::string c, std::string special = "normal");

  // reset all changes made
  void reset();

  // return a string that color/background is/are changed, after that reset all
  std::string setphrase(std::string s, std::string c = "normal", std::string brightness = "normal", std::string backcolor = "normal");


private:

  // Full ANSI escape code for reset, partial ANSI escape codes for others
  std::string rset    = "\033[0m";
  std::string normal  = "\033[3";
  std::string bright  = "\033[9";
  std::string bground = "\033[4";

  std::string generalcolor(std::string c);

};

// with credit to https://stackoverflow.com/questions/10422034/when-to-use-extern-in-c
extern Color color;

// with credits to:
// https://stackoverflow.com/questions/9158150/colored-output-in-c
// https://en.wikipedia.org/wiki/ANSI_escape_code

#endif
