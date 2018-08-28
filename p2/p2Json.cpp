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
  _fileName = jsonFile;
  fstream fs;
  fs.open( _fileName );

  return ( fs.good() && parse( fs ) );

  // TODO ...Done
}

bool
Json::parse( const fstream& file ){

  string temp_str = "";
  file.seekg( 0, file.beg );

  while( getline( temp_str, file ) ){ // string::getline
    if( temp_str.find_first_of( "{" ) != string::npos )
      break;
  }

  temp_str = "";
  string key = "";
  string value = "";
  int    value_data = 0;
  size_t start_quot_mark = 0;
  size_t end_quot_mark   = 0;
  size_t colon_mark      = 0;
  size_t start_key       = 0;
  size_t end_key         = 0;

  while( getline( temp_str, file ) ){ // parsing, return fail or throw exception if bad;

    if( temp_str.find_first_of( "}" ) != string::npos ){
      break;
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

    if( !valid_key( key ) ){
      return false;
    }
    
    try{
      value_data = stoi( value, nullptr, 10 );
    }catch( const invalid_argument& ia ){
      cerr << "invalid value inside file \"" << _fileName << "\"" << endl;
      return false;
    }catch( const out_of_range& oor ) {
      cerr << "value out of range inside file\"" << _fileName << "\"" << endl;
      return false;
    }

    _obj.push_back( key, value_data );
  }

  return true;
      
}

bool
Json::valid_key( string& key ) const{
  return ( key.find_first_not_of( _validKey ) == string::npos );
}

ostream&
operator << (ostream& os, const JsonElem& j)
{
  return (os << "\"" << j._key << "\" : " << j._value);
}

