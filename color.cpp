#include "color.h"
#include <iostream>

using std::string;

// The following is the detailed implementation of color.h
// See "color.h" for explanation and how to use the class


// To turn respective color into partial ANSI escape code
// Input: string of a color
// Output: partial ANSI escape code of that color
string Color::generalcolor(string c){
  string to_return = "";

  if (c == "black")
    to_return += "0m";
  if (c == "red")
    to_return += "1m";
  if (c == "green")
    to_return += "2m";
  if (c == "yellow")
    to_return += "3m";
  if (c == "blue")
    to_return += "4m";
  if (c == "magenta")
    to_return += "5m";
  if (c == "cyan")
    to_return += "6m";
  if (c == "white")
    to_return += "7m";

  return to_return;
}

// Below are public functions
// See color.h for descriptions

void Color::set(string c, string special = "normal"){
  string to_return = "";

  if (special == "normal")
    to_return += normal;
  if (special == "bright")
    to_return += bright;
  if (special == "background")
    to_return += bground;

  to_return += generalcolor(c);

  std::cout << to_return;
}

void Color::reset(){
  std::cout << rset;
}

string Color::setphrase(string s, string c = "normal", string brightness = "normal", string backcolor = "normal"){
  if (c != "normal")
    set(c, brightness);
  if (backcolor != "normal")
    set(backcolor, "background");
  return s + rset;
}
