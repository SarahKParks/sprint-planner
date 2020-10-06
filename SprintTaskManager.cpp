
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Ticket
{
    public:
        int ticket_id;
        int team;
        string priority_str;
        int priority_int;
        string task;
        int sprint_id;
        
        Ticket(int id, int t, string p, string m)
        {
            ticket_id = id;
            team = t;
            priority_str = p;
            task = m;
            
            if(p.compare("HIGH") == 0)
                priority_int = 2;
            else if(p.compare("MED") == 0)
                priority_int = 1;
            else
                priority_int = 0;
        }       
};

void assignSprintID(vector<Ticket> &list, int num_sprints, int num_tickets)
{
    int sprint_assigner = 0;
    int current_team = 0;
    int ticket_counter = 0;
    
    // while there are still tickets left
    while(ticket_counter < num_tickets) 
    {
        // while in the same team
        while(ticket_counter < num_tickets && current_team == list.at(ticket_counter).team) 
        {
            /* sprint assignment is limited if there are too many tickets for a single team with the given number 
               of sprints */
            if(sprint_assigner < num_sprints)
            {
                list.at(ticket_counter).sprint_id = sprint_assigner;
                sprint_assigner++;
                ticket_counter++;
            }
            else
            {
                list.at(ticket_counter).sprint_id = num_sprints;
                ticket_counter++; 
            }   
        }
        current_team++;
        sprint_assigner = 0;  
    }
}

void printTicketList(vector<Ticket> list, int num_sprints)
{
    for(unsigned int i = 0; i < list.size(); i++)
    {
        cout << list.at(i).ticket_id << "/ " 
             << list.at(i).task << "/ " 
             << list.at(i).team << "/ "
             << list.at(i).priority_str; 
        
        // determine if a sprint was assigned
        if(list.at(i).sprint_id != num_sprints)
        {
            cout <<  "/ " << list.at(i).sprint_id << endl;
        }
        else
        {
            cout << endl;
        }    
    }
}


int main()
{
    // ticket list info
    int num_teams;
    int num_sprints;
    int num_tickets;
    
    // values for current ticket
    int current_ticket_id;
    string current_task;
    int assigned_team;
    string current_priority_string;
    
    // reading in tickets
    
    cin >> num_teams >> num_sprints >> num_tickets;
    
    string value;
    string total_task;
    
    vector<Ticket> teamTasks;
    
    for (int i = 0; i < num_tickets; i++) 
    {
        // read ticket id
        getline(cin, value, ' ');
        current_ticket_id = stoi(value);
        
        // read task; Needed to account for '/' character being used in task description.
        getline(cin, value, ' ');
        total_task = "";
        while(value.substr(value.length() - 1, value.length()).compare("/") != 0)
        {
            total_task += value;
            total_task += " ";
            getline(cin, value, ' ');
        }
        total_task += value.substr(0, value.length() - 1);
        current_task = total_task;
        
        // read team
        getline(cin, value, '/');
        assigned_team = stoi(value);
        
        cin >> current_priority_string;
        
        Ticket current_ticket(current_ticket_id, assigned_team, current_priority_string, current_task);

        teamTasks.push_back(current_ticket);
    }
    
    /* Using lambda functions with sort to organize vector.
       Have to account for previous sorting with each new sort. */
    
    // sort by priority
    sort(teamTasks.begin(), teamTasks.end(), [](const Ticket& lhs, const Ticket& rhs)
    {
        if(rhs.priority_int == lhs.priority_int && rhs.ticket_id > lhs.ticket_id)
            return true;
        else if(rhs.priority_int < lhs.priority_int)
            return true;
        else
            return false;
    });
    
    
    //sort by teams
    sort(teamTasks.begin(), teamTasks.end(), [](const Ticket& lhs, const Ticket& rhs)
    {
        if(lhs.team == rhs.team && lhs.priority_int > rhs.priority_int)
            return true;
        else if(lhs.team == rhs.team && lhs.priority_int == rhs.priority_int && lhs.ticket_id < rhs.ticket_id)
            return true;
        else if(lhs.team < rhs.team)
            return true;
        else
            return false;
    });
    
    assignSprintID(teamTasks, num_sprints, num_tickets);
    
    // sort by ticket_id
    sort(teamTasks.begin(), teamTasks.end(), [](const Ticket& lhs, const Ticket& rhs)
    {
        return lhs.ticket_id < rhs.ticket_id;
    });
    
    // sort by sprint ID
    sort(teamTasks.begin(), teamTasks.end(), [](const Ticket& lhs, const Ticket& rhs)
    {
        if(lhs.sprint_id == rhs.sprint_id && lhs.ticket_id < rhs.ticket_id)
            return true;
        else if(lhs.sprint_id < rhs.sprint_id)
            return true;
        else
            return false;
    });
    
    printTicketList(teamTasks, num_sprints);
    
    return 0;
}
