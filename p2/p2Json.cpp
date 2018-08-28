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

  return ( fs.good() && parse( fs ) );

  // TODO ...Done
}

void
Json::parse( const fstream& file ){

  string temp_str = "";
  file.seekg( 0, file.beg );
  bool working = false; // indicator for "{}";

  while( getline( temp_str, file ) ){ // string::getline
    if( temp_str.find_first_of( "{" ) != string::npos )
      break;
  }

  temp_str = "";
  string key = "";
  string value = "";
  size_t start_quot_mark = 0;
  size_t end_quot_mark   = 0;
  size_t colon_mark      = 0;
  size_t start_key       = 0;
  size_t end_key         = 0;

  while( getline( temp_str, file ) ){

    if( temp_str.find_first_of( "}" ) != string::npos ){
      continue;
    }

    start_quot_mark = temp_str.find_first_of( '\"' );
    end_quot_mark   = temp_str.find_first_of( '\"', start_quot_mark+1 );
    if( end_quot_mark == string::npos ){
      return false;
    }

    key = temp_str.substr( start_quot_mark, end_quot_mark+1 );
    colon_mark = temp_str.find_first_of ( ':',  end_quot_mark+1 );
    if( colon_mark == string::npos ){
      return false;
    }

    start_key = temp_str.find_first_of( "-123456789", colon_mark+1 );
    end_key   = temp_str.find_first_of( ',', start_key+1 );
    if( end_key == string::npos ){
      end_key = temp_str.find_first_of( " \t\n\v\f\r\b" , start_key+1 );
    }
    value = temp_str.substr( start_key, ( (end_key+1)>temp_str.size() )?
        temp_str.size() : end_key+1 );





}


  ostream&
operator << (ostream& os, const JsonElem& j)
{
  return (os << "\"" << j._key << "\" : " << j._value);
}

