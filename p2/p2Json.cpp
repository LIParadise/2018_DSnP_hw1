/****************************************************************************
  FileName     [ p2Json.cpp ]
  PackageName  [ p2 ]
  Synopsis     [ Define member functions of class Json and JsonElem ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2018-present DVLab, GIEE, NTU, Taiwan ]
 ****************************************************************************/
#include <iostream>
#include <string>
#include <cctype> // int isspace ( int );
#include "p2Json.h"

using namespace std;

// Implement member functions of class Row and Table here
  bool
Json::read(const string& jsonFile)
{
  fstream fs;
  fs.open( jsonFile );

  if( fs.good() ){
    parse( fs );
    return true;
  }else{
    return false;
  }

  // TODO ...Done
}

void
Json::parse( const fstream& file ){

  string temp_str = "";
  file.seekg( 0, file.beg );
  bool working = false;

  while( getline( temp_str, file ) ){ // string::getline
    if( !working ){
      // check if this line indicates start of a .json description, i.e. "{";
      for( size_t i = 0; i < temp_str.size(); i++ ){
        if( !isspace( (int)temp_str[i] ) ){
          // shall be "{";
          if( temp_str[i] == '{' ){
            working = true;
          }
        }
      }
    }else{
      continue;
    }

    // working; read the described JsonElem, store it in this->_obj;
    size_t first_q_mark_pos = 0;
    size_t end_q_mark_pos = 0;
    size_t colon_pos = 0;
    string key = "";
    string value = "";
    bool temp = false;

    for( size_t i = 0; i < temp_str.size(); i++ ){
      if( temp_str[i] == "\"" ){
        if( temp == false ){
          first_q_mark_pos = i;
          temp = true;
        }else{
          end_q_mark_pos = ( ( (i+1)>temp_str.size() )? temp_str.size() : (i+1) );
          // string::substr is closed at LHS, open at RHS
          break;
        }
      }
    }

    if( temp == false){
      continue;
      // this line have no content;
    }
    key = temp_str.substr( first_q_mark_pos, end_q_mark_pos-first_q_mark_pos );

    for( size_t i = 0;




}


  ostream&
operator << (ostream& os, const JsonElem& j)
{
  return (os << "\"" << j._key << "\" : " << j._value);
}

