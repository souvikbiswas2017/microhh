#include <cstdio>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include "input.h"

cinput::cinput()
{
  std::printf("Creating instance of object input\n");

  // construct input list before implementing file reading
  /*// setup Moser 180 case
  inputlist["grid"]["itot"] = "64";
  inputlist["grid"]["jtot"] = "64";
  inputlist["grid"]["ktot"] = "64";

  inputlist["grid"]["xsize"] = "6.28";
  inputlist["grid"]["ysize"] = "3.14";
  inputlist["grid"]["zsize"] = "2.";

  // set the time properties
  inputlist["time"]["runtime"] = "10000.";
  inputlist["time"]["cflmax" ] = "0.8";
  inputlist["time"]["adaptivestep" ] = "true";*/
  // end setup Moser case
  
  // read the input file
  std::ifstream inputfile("microhh.ini");
  std::string inputline;
  std::string blockstring, itemstring, valuestring;
  size_t left, right, equal;

  while(!inputfile.eof())
  {
    std::getline(inputfile, inputline);
    // check the three cases: block, value, rubbish
    // check for block, find [ and find ] and parse the string in between
    //
    left  = inputline.find_first_of("[");
    right = inputline.find_last_of("]");
    equal = inputline.find_first_of("=");
    if(left != std::string::npos && right != std::string::npos)
    {
      blockstring = inputline.substr(left+1, right-1);
    }
    else if(equal != std::string::npos)
    {
      itemstring  = inputline.substr(0, equal);
      valuestring = inputline.substr(equal+1, std::string::npos);

      // insert item in map
      if(!blockstring.empty())
      {
        std::printf("Insert %s = %s in [%s]\n", itemstring.c_str(), valuestring.c_str(), blockstring.c_str());
        inputlist[blockstring][itemstring] = valuestring;
      }
    }
    else
      std::printf("Illegal input line: %s\n", inputline.c_str());
    

    // if no block extract a value
    // if no block and value report rubbish
    // std::printf("%s\n", inputline.c_str());
  }
}

cinput::~cinput()
{
  std::printf("Destroying instance of object input\n");
}

// overloaded return functions
int cinput::getItem(int *value, std::string cat, std::string item)
{
  std::string inputstring = inputlist[cat][item];

  // trim from both sides
  size_t left, right;
  left  = inputstring.find_first_of("123456789");
  right = inputstring.find_last_of ("0123456789");

  std::string inputproc = inputstring.substr(left, right-left+1);

  std::istringstream ss(inputproc);
  ss >> *value;

  std::ostringstream sscheck;
  sscheck << *value;
  if(ss.str() != sscheck.str())
    printf("ERROR: Value %s of item %s is not of type int\n", inputlist[cat][item].c_str(), item.c_str());

  return 0;
}

int cinput::getItem(double *value, std::string cat, std::string item)
{
  std::string inputstring = inputlist[cat][item];

  // trim from both sides
  size_t left, right;
  left  = inputstring.find_first_of("0123456789.");
  right = inputstring.find_last_of ("0123456789.");

  while(inputstring.substr(right,1) == "." || inputstring.substr(right,1) == "0")
    right--;

  std::string inputproc = inputstring.substr(left, right-left+1);

  std::istringstream ss(inputproc);
  ss >> *value;

  std::ostringstream sscheck;
  sscheck << *value;
  if(ss.str() != sscheck.str())
    printf("ERROR: Value %s of item %s is not of type double (%s,%s)\n", inputlist[cat][item].c_str(), item.c_str(), ss.str().c_str(), sscheck.str().c_str());

  return 0;
}

int cinput::getItem(bool *value, std::string cat, std::string item)
{
  std::string itemvalue = inputlist[cat][item];
  std::istringstream ss(itemvalue);
  if(itemvalue == "true" || itemvalue == "false")
    ss >> std::boolalpha >> *value;
  else if(itemvalue == "1" || itemvalue == "0")
    ss >> std::noboolalpha >> *value;
  else
    printf("ERROR: Value %s of item %s is not of type bool\n", inputlist[cat][item].c_str(), item.c_str());

  return 0;
}

