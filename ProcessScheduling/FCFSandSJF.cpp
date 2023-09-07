#include <bits/stdc++.h>

using namespace std;

struct Process {
  string name;
  int arrival_time, burst_time;
};

bool compareArrivalTime(Process p1, Process p2) {
  return p1.arrival_time < p2.arrival_time;
}

bool compareBurstTime(Process p1, Process p2) {
  return p1.burst_time < p2.burst_time;
}

void firstComeFirstServe(Process *p, int n) {
  sort(p,p+n,compareArrivalTime);
  int start_time[n], end_time[n], waiting_time[n], turnaround_time[n];
  float avg_waiting_time = 0, avg_turnaround_time = 0, avg_turnaround_time_by_bt = 0;
  start_time[0] = p[0].arrival_time;
  end_time[0] = start_time[0] + p[0].burst_time;
  waiting_time[0] = 0;
  turnaround_time[0] = end_time[0] - p[0].arrival_time;
  avg_waiting_time += waiting_time[0];
  avg_turnaround_time += turnaround_time[0];
  avg_turnaround_time_by_bt += (float)turnaround_time[0]/p[0].burst_time;
  for (int i=1;i<n;i++) {
    start_time[i] = end_time[i-1];
    end_time[i] = start_time[i] + p[i].burst_time;
    waiting_time[i] = start_time[i] - p[i].arrival_time;
    turnaround_time[i] = end_time[i] - p[i].arrival_time;
    avg_waiting_time += waiting_time[i];
    avg_turnaround_time += turnaround_time[i];
    avg_turnaround_time_by_bt += (float)turnaround_time[i]/p[i].burst_time;
  }
  cout << setw(10) << "Process" << setw(20) << "Arrival Time" << setw(20) << "Burst Time" << setw(20) << "Start Time" << setw(20) << "End Time" << setw(20) << "Waiting Time" << setw(20) << "Turnaround Time" << setw(20) << "TAT/BT" << endl;
  for (int i=0;i<n;i++) {
    cout << setw(10) << p[i].name << setw(20) << p[i].arrival_time << setw(20) << p[i].burst_time << setw(20) << start_time[i] << setw(20) << end_time[i] << setw(20) << waiting_time[i] << setw(20) << turnaround_time[i] << setw(20) << (float)turnaround_time[i]/p[i].burst_time << endl;
  }
  cout << "Average Waiting Time: " << avg_waiting_time/n << endl;
  cout << "Average Turnaround Time: " << avg_turnaround_time/n << endl;
  cout << "Average Turnaround Time/Burst Time: " << avg_turnaround_time_by_bt/n << endl;
}

void shortestJobFirst(Process *p, int n) {
  sort(p,p+n,compareBurstTime);
  int start_time[n], end_time[n], waiting_time[n], turnaround_time[n];
  float avg_waiting_time = 0, avg_turnaround_time = 0, avg_turnaround_time_by_bt = 0;
  start_time[0] = p[0].arrival_time;
  end_time[0] = start_time[0] + p[0].burst_time;
  waiting_time[0] = 0;
  turnaround_time[0] = end_time[0] - p[0].arrival_time;
  avg_waiting_time += waiting_time[0];
  avg_turnaround_time += turnaround_time[0];
  avg_turnaround_time_by_bt += (float)turnaround_time[0]/p[0].burst_time;
  for (int i=1;i<n;i++) {
    start_time[i] = end_time[i-1];
    end_time[i] = start_time[i] + p[i].burst_time;
    waiting_time[i] = start_time[i] - p[i].arrival_time;
    turnaround_time[i] = end_time[i] - p[i].arrival_time;
    avg_waiting_time += waiting_time[i];
    avg_turnaround_time += turnaround_time[i];
    avg_turnaround_time_by_bt += (float)turnaround_time[i]/p[i].burst_time;
  }
  cout << setw(10) << "Process" << setw(20) << "Arrival Time" << setw(20) << "Burst Time" << setw(20) << "Start Time" << setw(20) << "End Time" << setw(20) << "Waiting Time" << setw(20) << "Turnaround Time" << setw(20) << "TAT/BT" << endl;
  for (int i=0;i<n;i++) {
    cout << setw(10) << p[i].name << setw(20) << p[i].arrival_time << setw(20) << p[i].burst_time << setw(20) << start_time[i] << setw(20) << end_time[i] << setw(20) << waiting_time[i] << setw(20) << turnaround_time[i] << setw(20) << (float)turnaround_time[i]/p[i].burst_time << endl;
  }
  cout << "Average Waiting Time: " << avg_waiting_time/n << endl;
  cout << "Average Turnaround Time: " << avg_turnaround_time/n << endl;
  cout << "Average Turnaround Time/Burst Time: " << avg_turnaround_time_by_bt/n << endl;
}

int main() {
  int n,at,bt;
  string nm;
  cout << "Enter no. of processes: ";
  cin >> n;
  Process *p = new Process[n];

  for (int i=0;i<n;i++) {
    cout << "Enter process " << i+1 << " name: ";
    cin >> nm;
    cout << "Enter process " << i+1 << " arrival time: ";
    cin >> at;
    cout << "Enter process " << i+1 << " burst time: ";
    cin >> bt;
    p[i].name = nm;
    p[i].arrival_time = at;
    p[i].burst_time = bt;
  }

  char op;
  cout << "Enter 'f' for FCFS and 's' for SJF: ";
  cin >> op;

  if (op == 'f') {
    firstComeFirstServe(p,n);
  } else if (op == 's') {
    shortestJobFirst(p,n);
  } else {
    cout << "Invalid option" << endl;
  }
  
  return 0;
}
