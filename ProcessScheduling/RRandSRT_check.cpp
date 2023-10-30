#include <bits/stdc++.h>

using namespace std;

struct Process {
    string name;
    int arr_time,
        svc_time,
        act_svc_time,
        start_time,
        end_time,
        resp_time,
        wait_time,
        ta_time;
    float normta_time;
};

void roundRobin(vector<Process> processes) {
    vector<Process> temp = processes;
    int quantum;
    cout << "Enter quantum value: ";
    cin >> quantum;
    cout << endl;
    cout << setw(10) << "Name" << setw(10) << "Arrival" << setw(10) << "Service" << endl;
    for (Process process : temp) {
        cout << setw(10) << process.name << setw(10) << process.arr_time << setw(10) << process.svc_time << endl;
        process.start_time = INT_MAX;
    }
    cout << endl;
    int curr_time = 0;
    while (1) {
        bool done = true;
        for (int i=0; i<temp.size();i++) {
            if (temp[i].svc_time > 0) {
                done = false;
                if (temp[i].arr_time <= curr_time) {
                    if (temp[i].start_time == INT_MAX) temp[i].start_time = curr_time;
                    if (temp[i].svc_time > quantum) {
                        curr_time += quantum;
                        temp[i].svc_time -= quantum;
                    } else {
                        curr_time += temp[i].svc_time;
                        temp[i].svc_time = 0;
                        temp[i].end_time = curr_time;
                    }
                }
            }
        }
        if (done == true) break;
    }
    for (int i=0; i<temp.size();i++) {
        temp[i].resp_time = temp[i].start_time - temp[i].arr_time;
        temp[i].ta_time = temp[i].end_time - temp[i].arr_time;
        temp[i].wait_time = temp[i].ta_time - temp[i].act_svc_time;
        temp[i].normta_time = (float) temp[i].ta_time/temp[i].act_svc_time;
    }
    cout << setw(10) << "Name" << setw(10) << "Arrival" << setw(10) << "Service" << setw(10) << "Start" << setw(10) << "End"
         << setw(10) << "Response" << setw(10) << "Waiting" << setw(10) << "TAT" << setw(10) << "Norm TAT" << endl;
    for (Process process: temp) {
        cout << setw(10) << process.name << setw(10) << process.arr_time << setw(10) << process.act_svc_time
        << setw(10) << process.start_time << setw(10) << process.end_time << setw(10) << process.resp_time
        << setw(10) << process.wait_time << setw(10) << process.ta_time << setw(10) << process.normta_time << endl;
    }
}

bool compareRemainingTime(Process p1, Process p2) {
    return p1.svc_time < p2.svc_time;
}

void shortestRemainingTimeFirst(vector<Process> processes) {
    vector<Process> temp = processes;
    sort(temp.begin(), temp.end(), compareRemainingTime);
    int curr_time = 0;
    for (int i=0; i<temp.size();i++) {
        if (temp[i].arr_time <= curr_time) {
            temp[i].start_time = curr_time;
            curr_time += temp[i].svc_time;
            temp[i].end_time = curr_time;
        }
    }
    for (int i=0; i<temp.size();i++) {
        temp[i].resp_time = temp[i].start_time - temp[i].arr_time;
        temp[i].ta_time = temp[i].end_time - temp[i].arr_time;
        temp[i].wait_time = temp[i].ta_time - temp[i].act_svc_time;
        temp[i].normta_time = (float) temp[i].ta_time/temp[i].act_svc_time;
    }
    cout << setw(10) << "Name" << setw(10) << "Arrival" << setw(10) << "Service" << setw(10) << "Start" << setw(10) << "End"
         << setw(10) << "Response" << setw(10) << "Waiting" << setw(10) << "TAT" << setw(10) << "Norm TAT" << endl;
    for (Process process: temp) {
        cout << setw(10) << process.name << setw(10) << process.arr_time << setw(10) << process.act_svc_time
        << setw(10) << process.start_time << setw(10) << process.end_time << setw(10) << process.resp_time
        << setw(10) << process.wait_time << setw(10) << process.ta_time << setw(10) << process.normta_time << endl;
    }
}

int main() {
    cout << "Enter no. of processes: ";
    int n; cin >> n;
    vector<Process> p;
    for (int i=0;i<n;i++) {
        Process newp;
        cout << "Process " << i+1 << " details: "<<endl;
        cout << "Enter process name: ";
        cin >> newp.name;
        cout << "Enter arrival time: ";
        cin >> newp.arr_time;
        cout << "Enter burst time: ";
        cin >> newp.svc_time;
        newp.act_svc_time = newp.svc_time;
        p.push_back(newp);
    }
    
    roundRobin(p);
    return 0;
}
