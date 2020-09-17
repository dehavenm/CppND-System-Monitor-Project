#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

//Constructor
Process::Process(int pid) {
    pid_ = pid;
    pid_directory_ = "/" + to_string(pid) + "/";
}

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { 
  string line, value, utime, stime, cutime, cstime, priority, nice, num_threads, itrealvalue, starttime;
  float seconds;
  std::ifstream stream(LinuxParser::kProcDirectory + pid_directory_+ LinuxParser::kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i =0; i < 13; i++) {
      linestream >> value;
    }
    linestream >> utime >> stime >> cutime >> cstime >> priority >> nice >> num_threads >> itrealvalue >> starttime;
    seconds = (float)(LinuxParser::UpTime() - std::stol(starttime)/sysconf(_SC_CLK_TCK));

    return ( (std::stof(utime) + std::stof(stime) + std::stof(cutime) + std::stof(cstime))/sysconf(_SC_CLK_TCK) ) / seconds;

  }
  return 0; }

// TODO: Return the command that generated this process
string Process::Command() { 
    string cmd;
    std::ifstream stream(LinuxParser::kProcDirectory + pid_directory_+ LinuxParser::kCmdlineFilename);
    if (stream.is_open()) {
      std::getline(stream, cmd);

    }
    
    return cmd; }

// TODO: Return this process's memory utilization
string Process::Ram() { 
  string line, key, value;
  long kb;

  std::ifstream filestream(LinuxParser::kProcDirectory + pid_directory_+ LinuxParser::kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          kb = std::stol(value);
          return to_string(kb / 1024);
        }
      }
    }
  }
  return string(); }

// TODO: Return the user (name) that generated this process
string Process::User() { 
  string line, key, password, value, uid;

  std::ifstream filestream(LinuxParser::kProcDirectory + pid_directory_+ LinuxParser::kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          uid = value;
          break;
        }
      }
    }
  }
  filestream.close();

  filestream.open(LinuxParser::kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> value >> password >> key;
      if (key == uid) {
        return value;
          
      }
      
    }
  }
    
  return string(); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
  string line, value;
  std::ifstream stream(LinuxParser::kProcDirectory + pid_directory_+ LinuxParser::kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i =0; i < 22; i++) {
      linestream >> value;
    }
    return LinuxParser::UpTime() - std::stol(value)/sysconf(_SC_CLK_TCK);

  }
  return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return a.CpuUtilization() < CpuUtilization(); }