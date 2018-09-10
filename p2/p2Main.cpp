/****************************************************************************
  FileName     [ p2Main.cpp ]
  PackageName  [ p2 ]
  Synopsis     [ Define main() function ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2016-present DVLab, GIEE, NTU, Taiwan ]
 ****************************************************************************/
#include <iostream>
#include <sstream>
#include <string>
#include "p2Json.h"

using namespace std;

int main()
{
  Json json;

  // Read in the csv file. Do NOT change this part of code.
  string jsonFile;
  cout << "Please enter the file name: ";
  cin >> jsonFile;
  if (json.read(jsonFile))
    cout << "File \"" << jsonFile << "\" was read in successfully." << endl;
  else {
    cerr << "Failed to read in file \"" << jsonFile << "\"!" << endl;
    exit(-1); // jsonFile does not exist.
  }

  // TODO read and execute commands
  // cout << "Enter command: ";
  string input_cmd1, input_cmd2, input_cmd3, extra_cmd;
  stringstream ass; // "a stringstream"
  string str;
  while (true) {
    // cout << "Enter command: ";
    cout << "Enter command: ";
    getline( cin, str );
    input_cmd1.clear();
    input_cmd2.clear();
    input_cmd3.clear();
    extra_cmd.clear();
    ass = (stringstream)str;

    ass >> input_cmd1;
    if( input_cmd1 == "ADD" ){
      if( ass.eof() ){
        cout << "Error: Missing argument!!" << endl;
        continue;
      }
      ass >> input_cmd2;
      if( ass.eof() ){
        cout << "Error: Missing argument!!" << endl;
        continue;
      }
      ass >> input_cmd3 >> extra_cmd;
      if( !extra_cmd.empty() ){
        cout << "Error: Extra argument \"" << extra_cmd << "\"!!" << endl;
        continue;
      }
      
      if( json.exist_key( input_cmd2 ) ){
        continue;
      }else{
        json.add( input_cmd2, input_cmd3 );
      }

    }else if( input_cmd1 == "AVE" ){
      json.ave();
    }else if( input_cmd1 == "SUM" ){
      json.sum();
    }else if( input_cmd1 == "MAX" ){
      json.max();
    }else if( input_cmd1 == "MIN" ){
      json.min();
    }else if( input_cmd1 == "PRINT" ){
      json.print();
    }else if( input_cmd1 == "EXIT" ){
      json.exit();
      break;
    }else{
      cout << "Wrong command format, check your input and try again." << endl;
    }
  }
}
