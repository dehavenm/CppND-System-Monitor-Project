#include <string>
#include <math.h>
#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    long hours, minutes, min_sec, sec;
    string h_string, m_string, s_string;
    hours = floor(seconds / 3600.0);
    min_sec = seconds - hours*3600.0;
    minutes = floor(min_sec / 60.0);
    sec = min_sec - minutes*60.0;
    h_string = std::to_string((int)hours);
    if (hours < 10.0) {h_string = "0" + h_string;}
    m_string = std::to_string((int)minutes);
    if (minutes < 10.0) {m_string = "0" + m_string;}
    s_string = std::to_string((int)sec);
    if (sec < 10.0) {s_string = "0" + s_string;}
    string output = h_string + ":" + m_string + ":" + s_string;
    return output; }