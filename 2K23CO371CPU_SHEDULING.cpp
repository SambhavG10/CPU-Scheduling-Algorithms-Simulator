#include <bits/stdc++.h>
using namespace std;
class process
{
public:
    string ID;
    int at;
    int burst;
    int burst1;
    int ct;
    int tat;
    int wt;
    int priority;

    process(string ID, int arrival_time, int burst_time, int priority)
    {
        this->ID = ID;
        this->at = arrival_time;
        this->burst = burst_time;
        this->burst1 = burst_time;
        this->priority = priority;
    }
};
ofstream outputfile("datafile_output.txt");
bool arrivalOrder(process p1, process p2)
{
    if (p1.at < p2.at)
        return 1;
    else if (p1.at == p2.at && p1.ID[1] < p2.ID[1])
        return 1;
    else
        return 0;
}
bool burstOrder(process p1, process p2)
{
    if (p1.burst < p2.burst)
        return 1;
    else if (p1.burst == p2.burst && p1.at < p2.at)
        return 1;
    else if (p1.priority == p2.priority && p1.at == p2.at && p1.ID[1] < p2.ID[1])
        return 1;
    else
        return 0;
}
bool priorOrder(process p1, process p2)
{
    if (p1.priority < p2.priority)
        return 1;
    else if (p1.priority == p2.priority && p1.at < p2.at)
        return 1;
    else if (p1.priority == p2.priority && p1.at == p2.at && p1.ID[1] < p2.ID[1])
        return 1;
    else
        return 0;
}
bool IdOrder(process p1, process p2)
{
    if (p1.ID[1] < p2.ID[1])
        return 1;
    else
        return 0;
}


pair<float, float> FCFS(vector<process> p, int disp)
{
    cout << "FCFS :" << "\n";
    outputfile << "FCFS :" << "\n";
    sort(p.begin(), p.end(), arrivalOrder);
    int avgtat = 0, avgwt = 0;
    int current_time = p[0].at + disp;
    int acurr = p[0].at + disp;
    // if (current_time < p[0].at)
    //     current_time = p[0].at;
    for (int i = 0; i < p.size(); i++)
    {
        if (p[i].at > acurr)
            current_time = p[i].at + disp;
        if (current_time / 10 == 0)
        {
            cout << "T" << current_time << " : " << p[i].ID << "(" << p[i].priority << ")" << "\n";
            outputfile << "T" << current_time << " : " << p[i].ID << "(" << p[i].priority << ")" << "\n";
        }
        else
        {
            cout << "T" << current_time << ": " << p[i].ID << "(" << p[i].priority << ")" << "\n";
            outputfile << "T" << current_time << ": " << p[i].ID << "(" << p[i].priority << ")" << "\n";
        }
        p[i].ct = current_time + p[i].burst;
        acurr = p[i].ct;
        current_time = p[i].ct + disp;

        p[i].tat = p[i].ct - p[i].at;
        avgtat += p[i].tat;

        p[i].wt = p[i].tat - p[i].burst;
        avgwt += p[i].wt;
    }
    sort(p.begin(), p.end(), IdOrder);

    cout << "\n"
         << "Process \tTurnaround time \tWaiting time" << endl;
    outputfile << "\n"
               << "Process \tTurnaround time \tWaiting time" << endl;
    for (int i = 0; i < p.size(); i++)
    {
        cout << p[i].ID << "\t\t" << p[i].tat << "\t\t\t" << p[i].wt << endl;
        outputfile << p[i].ID << "\t\t\t" << p[i].tat << "\t\t\t\t\t" << p[i].wt << endl;
    }
    cout << "\n";
    outputfile << "\n";
    return {(float)avgtat / p.size(), (float)avgwt / p.size()};
}
pair<float, float> SPN(vector<process> p, int disp)
{
    cout << "SPN :" << "\n";
    outputfile << "SPN :" << "\n";
    sort(p.begin(), p.end(), burstOrder);
    int mini = INT_MAX;
    for (int i = 0; i < p.size(); i++)
    {
        if (p[i].at < mini)
        {
            mini = p[i].at;
        }
    }

    int current_time = mini + disp;
    int acurr = mini + disp;
    int avgtat = 0, avgwt = 0;
    while (1)
    {
        int mark;
        for (int i = 0; i < p.size(); i++)
        {
            mark = 0;
            if (p[i].at <= acurr)
            {
                mark = 1;
                if (current_time / 10 == 0)
                {
                    cout << "T" << current_time << " : " << p[i].ID << "(" << p[i].priority << ")" << "\n";
                    outputfile << "T" << current_time << " : " << p[i].ID << "(" << p[i].priority << ")" << "\n";
                }
                else
                {
                    cout << "T" << current_time << ": " << p[i].ID << "(" << p[i].priority << ")" << "\n";
                    outputfile << "T" << current_time << ": " << p[i].ID << "(" << p[i].priority << ")" << "\n";
                }
                p[i].ct = current_time + p[i].burst;
                acurr = p[i].ct;
                current_time = p[i].ct + disp;

                p[i].tat = p[i].ct - p[i].at;
                avgtat += p[i].tat;
                p[i].wt = p[i].tat - p[i].burst;
                avgwt += p[i].wt;
                p[i].at = INT_MAX;
                break;
            }
        }
        if (mark == 0)
        {
            int l = 0;
            sort(p.begin(), p.end(), arrivalOrder);
            for (int i = 0; i < p.size(); i++)
            {

                if (p[i].at != INT_MAX)
                {

                    l = 1;
                    current_time = p[i].at + disp;
                    acurr = p[i].at;
                    sort(p.begin(), p.end(), burstOrder);
                    break;
                }
            }
            if (l == 0)
                break;
        }
    }

    sort(p.begin(), p.end(), IdOrder);
    cout << "\n"
         << "Process \tTurnaround time \tWaiting time" << endl;
    outputfile << "\n"
               << "Process \tTurnaround time \tWaiting time" << endl;
    for (int i = 0; i < p.size(); i++)
    {
        cout << p[i].ID << "\t\t" << p[i].tat << "\t\t\t" << p[i].wt << endl;
        outputfile << p[i].ID << "\t\t\t" << p[i].tat << "\t\t\t\t\t" << p[i].wt << endl;
    }
    cout << "\n";
    outputfile << "\n";

    return {(float)avgtat / p.size(), (float)avgwt / p.size()};
}

pair<float, float> PP(vector<process> p, int disp){
    cout << "PP :" << "\n";
    outputfile << "PP :" << "\n";
    sort(p.begin(), p.end(), priorOrder);
    int mini = INT_MAX;
    for (int i = 0; i < p.size(); i++)
    {
        if (p[i].at < mini)
        {
            mini = p[i].at;
        }
    }
    int avgtat = 0, avgwt = 0;
    int curr = mini + disp;
    int acurr = mini;
    int idx = -1;
    while (1)
    {
        int mark = 0;

        for (int i = 0; i < p.size(); i++)
        {
            if (p[i].at <= acurr)
            {
                if (idx != i)
                {
                    if (curr / 10 == 0)
                    {
                        cout << "T" << curr << " : " << p[i].ID << "(" << p[i].priority << ")" << "\n";
                        outputfile << "T" << curr << " : " << p[i].ID << "(" << p[i].priority << ")" << "\n";
                    }
                    else
                    {
                        cout << "T" << curr << ": " << p[i].ID << "(" << p[i].priority << ")" << "\n";
                        outputfile << "T" << curr << ": " << p[i].ID << "(" << p[i].priority << ")" << "\n";
                    }
                }

                if (idx == i)
                    curr = curr - disp;
                idx = i;
                mark = 1;

                p[i].burst1 -= 1;
                if (p[i].burst1 == 0)
                {
                    p[i].ct = curr + 1;

                    p[i].tat = p[i].ct - p[i].at;
                    avgtat += p[i].tat;
                    p[i].wt = p[i].tat - p[i].burst;
                    avgwt += p[i].wt;
                    p[i].at = INT_MAX;
                }
                acurr = curr + 1;
                curr = acurr + disp;
                break;
            }
        }
        if (mark == 0)
        {
            int l = 0;
            sort(p.begin(), p.end(), arrivalOrder);
            for (int i = 0; i < p.size(); i++)
            {

                if (p[i].at != INT_MAX)
                {
                    l = 1;
                    curr = p[i].at + disp;
                    acurr = p[i].at;
                    sort(p.begin(), p.end(), priorOrder);
                    break;
                }
            }
            if (l == 0)
                break;
        }
    }
    sort(p.begin(), p.end(), IdOrder);
    cout << "\n"
         << "Process \tTurnaround time \tWaiting time" << endl;
    outputfile << "\n"
               << "Process \tTurnaround time \tWaiting time" << endl;
    for (int i = 0; i < p.size(); i++)
    {
        cout << p[i].ID << "\t\t" << p[i].tat << "\t\t\t" << p[i].wt << endl;
        outputfile << p[i].ID << "\t\t\t" << p[i].tat << "\t\t\t\t\t" << p[i].wt << endl;
    }
    cout << "\n";
    outputfile << "\n";

    return {(float)avgtat / p.size(), (float)avgwt / p.size()};
}

pair<float, float> PRR(vector<process> p, int disp){
    cout << "PRR :" << "\n";
    outputfile << "PRR :" << "\n";
    sort(p.begin(), p.end(), arrivalOrder);
    int avgtat = 0, avgwt = 0;
    vector<process *> temp;
    int curr = p[0].at + disp;
    int acurr = p[0].at + disp;
    int idx = -1;
    int j = 0;
    for (int i = 0; i < p.size(); i++){
        if (p[i].at <= p[0].at){
            temp.push_back(&p[i]);
            j++;
        }
    }

    for (int i = 0; i < temp.size(); i++){
        if (temp[i]->priority == 0 || temp[i]->priority == 1 || temp[i]->priority == 2){
            if (idx != temp[i]->ID[1] - '0'){
                if (curr / 10 == 0)
                {

                    cout << "T" << curr << " : " << temp[i]->ID << "(" << temp[i]->priority << ")" << "\n";
                    outputfile << "T" << curr << " : " << temp[i]->ID << "(" << temp[i]->priority << ")" << "\n";
                }
                else
                {
                    cout << "T" << curr << ": " << temp[i]->ID << "(" << temp[i]->priority << ")" << "\n";
                    outputfile << "T" << curr << ": " << temp[i]->ID << "(" << temp[i]->priority << ")" << "\n";
                }
            }

            if (idx == temp[i]->ID[1] - '0')
            {
                curr -= disp;
            }
            idx = temp[i]->ID[1] - '0';
            temp[i]->burst1 -= 4;
            int u = 4;
            if (temp[i]->burst1 < 0)
                u = 4 + temp[i]->burst1;
            if (j != p.size())
            {
                for (int k = j; k < p.size(); k++)
                {
                    if (p[k].at >= curr && p[k].at <= curr + u || p[k].at <= curr)
                    {
                        temp.push_back(&p[k]);
                        j++;
                    }
                }
            }

            if (temp[i]->burst1 <= 0)
            {
                int u = 4;
                if (temp[i]->burst1 < 0)
                    u = 4 + temp[i]->burst1;
                temp[i]->ct = curr + u;

                temp[i]->tat = temp[i]->ct - temp[i]->at;
                avgtat += temp[i]->tat;
                temp[i]->wt = temp[i]->tat - temp[i]->burst;
                avgwt += temp[i]->wt;
                temp[i]->at = INT_MAX;
                acurr = curr + u;
                curr = acurr + disp;
            }
            else if (temp[i]->burst1 != 0)
            {
                temp.push_back(temp[i]);
                acurr = curr + 4;
                curr = acurr + disp;
            }
            if (i == temp.size() - 1 && j != p.size())
            {
                if (p[j].at != INT_MAX)
                {
                    temp.push_back(&p[j]);
                    if (p[j].at > acurr)
                    {
                        curr = p[j].at + disp;
                        acurr = p[j].at;
                    }
                    j++;
                }
            }
        }
        else
        {
            if (idx != temp[i]->ID[1] - '0')
            {
                if (curr / 10 == 0)
                {
                    cout << "T" << curr << " : " << temp[i]->ID << "(" << temp[i]->priority << ")" << "\n";
                    outputfile << "T" << curr << " : " << temp[i]->ID << "(" << temp[i]->priority << ")" << "\n";
                }
                else
                {
                    cout << "T" << curr << ": " << temp[i]->ID << "(" << temp[i]->priority << ")" << "\n";
                    outputfile << "T" << curr << ": " << temp[i]->ID << "(" << temp[i]->priority << ")" << "\n";
                }
            }
            if (idx == temp[i]->ID[1] - '0')
            {
                curr -= disp;
            }
            idx = temp[i]->ID[1] - '0';
            temp[i]->burst1 -= 2;
            int u = 2;
            if (temp[i]->burst1 < 0)
                u = 2 + temp[i]->burst1;
            if (j != p.size())
            {
                for (int k = j; k < p.size(); k++)
                {
                    if (p[k].at >= curr && p[k].at <= curr + u || p[k].at <= curr)
                    {
                        temp.push_back(&p[k]);
                        j++;
                    }
                }
            }
            if (temp[i]->burst1 <= 0)
            {
                int u = 2;
                if (temp[i]->burst1 < 0)
                    u = 2 + temp[i]->burst1;
                temp[i]->ct = curr + u;

                temp[i]->tat = temp[i]->ct - temp[i]->at;
                avgtat += temp[i]->tat;
                temp[i]->wt = temp[i]->tat - temp[i]->burst;
                avgwt += temp[i]->wt;
                temp[i]->at = INT_MAX;
                acurr = curr + u;
                curr = acurr + disp;
            }
            else if (temp[i]->burst1 != 0)
            {
                temp.push_back(temp[i]);
                acurr = curr + 2;
                curr = acurr + disp;
            }
            if (i == temp.size() - 1 && j != p.size())
            {
                if (p[j].at != INT_MAX)
                {
                    temp.push_back(&p[j]);
                    if (p[j].at > acurr)
                    {
                        curr = p[j].at + disp;
                        acurr = p[j].at;
                    }
                    j++;
                }
            }
        }
    }
    sort(p.begin(), p.end(), IdOrder);
    cout << "\n"
         << "Process \tTurnaround time \tWaiting time" << endl;
    outputfile << "\n"
               << "Process \tTurnaround time \tWaiting time" << endl;
    for (int i = 0; i < p.size(); i++)
    {
        cout << p[i].ID << "\t\t" << p[i].tat << "\t\t\t" << p[i].wt << endl;
        outputfile << p[i].ID << "\t\t\t" << p[i].tat << "\t\t\t\t\t" << p[i].wt << endl;
    }
    cout << "\n";
    outputfile << "\n";

    return {(float)avgtat / p.size(), (float)avgwt / p.size()};
}

int main()
{string input;
cout<<"File must be in same folder in which code is running\nOutput file will generate with name datafile_output.txt in same folder \nEnter File Name (Format= file_name.txt) you want to read ";
cin>>input;
    ifstream myfile(input);
    if(!myfile.is_open()){
    cout<<"File name is not there";
    return 1;

    }

    string line, line1;
    int disp = 0, flag = 0;
    vector<string> pid;
    vector<int> arrival;
    vector<int> bt;
    vector<int> prior;

    while (getline(myfile, line))
    {
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == ':')
            {
                disp = line[i + 2] - '0';
                flag = 1;
                break;
            }
        }
        if (flag == 1)
            break;
    }

    while (getline(myfile, line))
    {
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == ':')
            {
                string s;
                for (int j = i + 2; j < line.size(); j++)
                    s.push_back(line[j]);
                pid.push_back(s);
                getline(myfile, line);
                for (int i = 0; i < line.size(); i++)
                {
                    if (line[i] == ':')

                    {
                        string s1;
                        for (int j = i + 2; j < line.size(); j++)
                            s1.push_back(line[j]);
                        arrival.push_back(stoi(s1));
                        getline(myfile, line);
                        for (int i = 0; i < line.size(); i++)
                        {
                            if (line[i] == ':')
                            {
                                string s2;
                                for (int j = i + 2; j < line.size(); j++)
                                    s2.push_back(line[j]);
                                bt.push_back(stoi(s2));

                                getline(myfile, line);
                                for (int i = 0; i < line.size(); i++)
                                {
                                    if (line[i] == ':')
                                    {
                                        string s3;
                                        for (int j = i + 2; j < line.size(); j++)
                                            s3.push_back(line[j]);
                                        prior.push_back(stoi(s3));

                                        break;
                                    }
                                }
                                break;
                            }
                        }
                        break;
                    }
                }
                break;
            }
        }
    }

    myfile.close();
    vector<process> p;
    for (int i = 0; i < pid.size(); i++)
    {
        process processes(pid[i], arrival[i], bt[i], prior[i]);
        p.push_back(processes);
    }
    pair<float, float> fc, sp, pp, pr;

    fc = FCFS(p, disp);
    sp = SPN(p, disp);
    pp = PP(p, disp);
    pr = PRR(p, disp);
    cout << "Summary" << "\n";
    cout << "Algorithm \tAverage Turnaround Time \tAverage Waiting Time" << "\n";

    cout << "FCFS" << "\t\t" << fixed << setprecision(2) << fc.first << "\t\t\t\t" << fixed << setprecision(2) << fc.second << "\n";
    cout << "SPN" << "\t\t" << fixed << setprecision(2) << sp.first << "\t\t\t\t" << fixed << setprecision(2) << sp.second << "\n";
    cout << "PP" << "\t\t" << fixed << setprecision(2) << pp.first << "\t\t\t\t" << fixed << setprecision(2) << pp.second << "\n";
    cout << "PRR" << "\t\t" << fixed << setprecision(2) << pr.first << "\t\t\t\t" << fixed << setprecision(2) << pr.second;
    cout << "\n";
    outputfile << "Summary" << "\n";
    outputfile << "Algorithm \tAverage Turnaround Time \tAverage Waiting Time" << "\n";

    outputfile << "FCFS" << "\t\t" << fixed << setprecision(2) << fc.first << "\t\t\t\t\t\t" << fixed << setprecision(2) << fc.second << "\n";
    outputfile << "SPN" << "\t\t\t" << fixed << setprecision(2) << sp.first << "\t\t\t\t\t\t" << fixed << setprecision(2) << sp.second << "\n";
    outputfile << "PP" << "\t\t\t" << fixed << setprecision(2) << pp.first << "\t\t\t\t\t\t" << fixed << setprecision(2) << pp.second << "\n";
    outputfile << "PRR" << "\t\t\t" << fixed << setprecision(2) << pr.first << "\t\t\t\t\t\t" << fixed << setprecision(2) << pr.second;

    outputfile.close();

    return 0;
}
