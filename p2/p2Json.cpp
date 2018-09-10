/****************************************************************************
  FileName     [ p2Json.cpp ]
  PackageName  [ p2 ]
  Synopsis     [ Define member functions of class Json and JsonElem ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2018-present DVLab, GIEE, NTU, Taiwan ]
 ****************************************************************************/
#include <iostream>
#include <string>
#include <cctype>  // int isspace ( int );
#include <ios>     // restore cout states;
#include <climits> // INT_MIN, INT_MAX
#include <iomanip> // cout << setprecision (1 );
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
Json::parse( fstream& file ){

  string temp_str = "";
  file.seekg( 0, file.beg );

  while( getline( file, temp_str ) ){ // string::getline
    if( temp_str.find_first_of( "{" ) != string::npos )
      break;
  }

  temp_str = "";
  string key = "";
  string value = "";
  int    value_data = 0;
  bool   valid_line = true;
  size_t start_quot_mark = 0;
  size_t end_quot_mark   = 0;
  size_t colon_mark      = 0;
  size_t start_value     = 0;
  size_t end_value       = 0;

  while( getline( file, temp_str ) ){ // parsing, return fail or throw exception if bad;

    valid_line = true;
    // if (!valid_line), then this->_obj would not be modified.

    if( temp_str.find_first_of( "}" ) != string::npos ){
      break;
    }

    start_quot_mark = temp_str.find_first_of( "\"" );
    end_quot_mark   = temp_str.find_first_of( "\"", start_quot_mark+1 );

    if( start_quot_mark != string::npos && end_quot_mark != string::npos ){
      key = temp_str.substr( start_quot_mark+1, end_quot_mark-start_quot_mark-1 );
    }else{
      valid_line = false;
    }

    colon_mark = temp_str.find_first_of ( ":",  end_quot_mark+1 );

    if( colon_mark != string::npos ){
      start_value = temp_str.find_first_of( "-0123456789", colon_mark+1 );
      // maybe there's only zero as the value...
      end_value = temp_str.find_first_not_of( "0123456789", start_value+1 );
      if( start_value != string::npos && end_value != string::npos ){
        // shall be normal line, with others pending, s.t. we met ',';
        value = temp_str.substr( start_value, end_value - start_value );
      }else if( start_value != string::npos && end_value == string::npos ){
        end_value = temp_str.size();
        value = temp_str.substr( start_value, end_value - start_value );
      }else{
        valid_line = false;
      }
    }else{
      valid_line = false;
    }

    if( valid_line ){
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

      if( keys.find( key ) == keys.end() ){
        _obj.push_back( JsonElem( key, value_data ) );
        keys.insert( key) ;
      }else{
        cout << "Error: Key \"" << key << "\" is repeated!!" << endl;
      }
    }
  }

  file.close();
  return true;

}

bool
Json::valid_key( string& key ) const{
  return ( key.find_first_not_of( _validKey ) == string::npos );
}

bool
Json::exist_key( string& key ){
  return ! ( keys.find( key ) == keys.end() );
}

void
Json::print() {

  cout << "{\n";
  if( !_obj.empty() ){
    for( size_t i = 0 ; i < _obj.size(); i++ ){
      cout << "  " << _obj.at(i) ;
      if( i != _obj.size()-1 ){
        cout << ",\n";
      }else{
        cout << "\n";
      }
    }
  }
  cout << "}\n";

}

int 
Json::sum(){

  if( _obj.size() == 0 ){
    cerr << "Error: No element found!!\n" ;
    return 0;
  }else{

    int sum = 0;
    for( auto& it : _obj ){
      sum += it.getValue();
    }

    cout << "The summation of the values is: " << sum << ".\n" ;
    return sum;
  }

}

long double
Json::ave(){

  if( _obj.empty() ){
    cerr << "Error: No element found!!\n" ;
    return 0;
  }else{
    ios_base::fmtflags org_cout_flags( cout.flags() );
    int sum = 0;
    for( auto&it : _obj) {
      sum += it.getValue();
    }
    long double ave = sum/( (long double)_obj.size() );
    cout << fixed << setprecision(1) << "The average of the values is: " << ave << ".\n" ;
    cout.flags( org_cout_flags );
    return ave;
  }
}

int
Json::max(){
  if( _obj.empty()){
    cerr << "Error: No element found!!\n" ;
    return 0;
  }else{

    int max = INT_MIN;
    int idx = 0;
    for( size_t i = 0; i < _obj.size(); i++ ){
      if( _obj.at(i).getValue() > max ){
        max = _obj.at(i).getValue();
        idx = i;
      }
    }
    cout << "The maximum element is: { " << _obj.at(idx) << " }.\n";
    return max;
  }
}

int
Json::min(){
  if( _obj.empty()){
    cerr << "Error: No element found!!\n" ;
    return 0;
  }else{

    int min = INT_MAX;
    int idx = 0;
    for( size_t i = 0; i < _obj.size(); i++ ){
      if( _obj.at(i).getValue() < min ){
        min = _obj.at(i).getValue();
        idx = i;
      }
    }
    cout << "The minimum element is: { " << _obj.at(idx) << " }.\n";
    return min;
  }
}

bool
Json::add( string& new_key, string& new_value ){

  _obj.push_back( (JsonElem( new_key, stoi( new_value, nullptr, 10 ) )  ) );
  keys.insert( new_key );
  return true;
}

void
Json::exit(){
  _obj.clear();
  keys.clear();
}

int
JsonElem::getValue() const{
  return _value;
}

  ostream&
operator << (ostream& os, const JsonElem& j)
{
  return (os << "\"" << j._key << "\" : " << j._value);
}
