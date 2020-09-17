#include "processor.h"
#include "linux_parser.h"

using std::string;
using std::stof;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  string line, cpu;
  string user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
  float total;
  float cpu_utilization = 0.0;
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
    total = stof(user) + stof(nice) + stof(system) + stof(idle) + stof(iowait) + stof(irq) + stof(softirq) + stof(steal) + stof(guest) + stof(guest_nice);
    cpu_utilization = 1.0 - stof(idle) / total;
  }
  return cpu_utilization;
  }