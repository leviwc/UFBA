#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
struct Task {
    int id, niceValue, cpuNeeded, vRuntime, realRuntime;
    bool runable;
    Task() {}
    Task(int id, int niceValue, int cpuNeeded, int vRuntime, int realRuntime) {
        this->niceValue = niceValue;
        this->cpuNeeded = cpuNeeded;
        this->vRuntime = vRuntime;
        this->realRuntime = realRuntime;
        this->id = id;
        this->runable = true;
    }
    bool isOver() { return realRuntime >= cpuNeeded; }
    void addRuntime(int t) {
        vRuntime += (t * ((niceValue + 21) / 39.0));
        realRuntime += t;
    }
    bool operator<(const Task& t) const {
        return (this->vRuntime < t.vRuntime);
    }
};
struct CFS {
    multiset<Task> rbTree;
    Task current;
    int timeSlice, minGranularity;
    bool runningTask;
    CFS(int timeSlice) {
        this->timeSlice = timeSlice;
        minGranularity = 4;
        runningTask = false;
    }
    int min_vruntime() {
        if (rbTree.empty()) return 0;
        return rbTree.begin()->vRuntime;
    }
    void addTask(int niceValue, int cpuNeeded, int id) {
        rbTree.insert(Task(id, niceValue, cpuNeeded, min_vruntime(), 0));
    }
    int getNext() {
        int qt = 0;
        if (runningTask) {
            if (!current.isOver()) {
                rbTree.insert(current);
            } else {
                cout << "finished task: " << current.id << endl;
            }
            runningTask = false;
        }
        if (!rbTree.empty()) {
            runningTask = true;
            current = *(rbTree.begin());
            qt = max(timeSlice / (int)rbTree.size(), minGranularity);
            cout << "running: " << current.id
                 << " virtualRuntime: " << current.vRuntime
                 << " realRuntime :" << current.realRuntime
                 << " cpuNeeded :" << current.cpuNeeded << " for " << qt
                 << " ms" << endl;
            current.addRuntime(qt);
            rbTree.erase(rbTree.begin());
            usleep(qt * 1000);
        }
        return qt;
    }
};
struct Process {
    int start, niceValue, cpuNeeded, id;
    Process() {}
    bool operator<(const Process& t) const { return (this->start < t.start); }
};
void runCFS(vector<Process> process) {
    sort(process.begin(), process.end());
    CFS scheduler = CFS(2000);
    int time = 0;
    int at = 0;
    while (true) {
        while (at < process.size() and time >= process[at].start) {
            scheduler.addTask(process[at].niceValue, process[at].cpuNeeded,
                              process[at].id);
            cout << "process :" << process[at].id << " added" << endl;
            at++;
        }
        time += scheduler.getNext();
        if (!scheduler.runningTask) {
            if (at == process.size()) {
                break;
            } else {
                usleep((process[at].start - time) * 1000);
                time = process[at].start;
            }
        }
    }
}
int main() {
    int n;
    cin >> n;
    vector<Process> process;
    for (int i = 0; i < n; i++) {
        Process aux;
        cin >> aux.start >> aux.niceValue >> aux.cpuNeeded;
        aux.id = i + 1;
        process.push_back(aux);
    }
    runCFS(process);
}