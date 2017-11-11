/*  Name: Merna Addison
    Date: 9/24/17
    Email: merna.addison@gmail.com
 
    This program reads in information about baseball teams from three files and sorts and outputs it into easily read information.
    Specifically, it will output the World Series Winners by the year they won, as well as sort the teams by the League they belong
    to and sort them in descending order of how many world series wins they have had.
 
    I chose to do an array of the struct team because it seemed like an easier approach to organizing the team information and keeping
    it all together when manipulating the data. I chose the bubble sort method to sort the teams by the number of wins because I have
    used it before and am comfortable with it and it worked well in this program.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const int ARRAY_SIZE = 30;  // Array size

// Struct for team values
struct team{
    string teamName;
    string leagueName;
    int seriesWins;
}team[ARRAY_SIZE];  // Found this approach on forum cited below
                    // Cableguy414 (2009, July 2). Need to sort multiple arrays. http://www.cplusplus.com/forum/beginner/12317/

//Function prototype
void sortVectorWinning(vector<struct team>& team); // Sorts teams descending by num wins

int main()
{
    // Input file stream objects
    ifstream inWinners;
    ifstream inTeams;
    ifstream inLeague;
    
    // Variables
    const string AmLeague = "American League";
    const string NatLeague = "National League";
    vector<struct team>AmLgTeams;   // American leagues teams
    vector<struct team>NatLgTeams;  // National leauge teams
    int count;                    // counter for reading input
    string input;                   // Input for line from text file
    
    //Open files
    inTeams.open("Teams.txt");
    inLeague.open("Leagues.txt");
    inWinners.open("WorldSeriesWinners.txt");
    
    // Read in team names from Teams.txt into the struct vector "team" for "teamName"
    count = 0;
    while (getline(inTeams, input))
    {
        team[count].teamName = input;
        count++;
    }
    
    // Read in the league each team is in from Leagues.txt into struct vector "team" for "leagueName"
    count = 0;
    while (getline(inLeague, input))
    {
        team[count].leagueName = input;
        count++;
    }
    
    // This outputs the world series winners by year
    cout << "World Series Winners by year: " << endl;
    cout << "-----------------------------" << endl;
    count = 1903;
    while (getline(inWinners, input))
    {
        cout << count << " - " << input << endl;
        
        // This reads in the number of wins for each team from WorldSeriesWinners.txt into struct vector "team" for "seriesWins"
        for (int x = 0; x < ARRAY_SIZE; x++)
        {
            if(team[x].teamName == input){
                team[x].seriesWins++;
            }
        }
        count++;
    }
    
    // Output All Teams
    cout << "\nList of all teams: " << endl;
    cout <<   "------------------" << endl;
    for(int i = 0; i < ARRAY_SIZE; i++){
        if(team[i].teamName=="No Winner"){
            // do nothing so skip "no winner"
        }else{
            cout << team[i].teamName << endl;
        }
    }
    
    // Sort teams into leagues
    for (int x = 0; x < ARRAY_SIZE; x++){
        if(team[x].leagueName == NatLeague){
            NatLgTeams.push_back(team[x]);
        }else if(team[x].leagueName == AmLeague){
            AmLgTeams.push_back(team[x]);
        }else{ }// ignore any other input such as "No Winner"
    }
    
    // Output Teams in the National League
    cout << "\nNational League Teams: " << endl;
    cout <<   "----------------------" << endl;
    for(int i = 0; i < NatLgTeams.size(); i++){
        cout << NatLgTeams[i].teamName << endl;
    }

    // Output Teams in the American League
    cout << "\nAmerican League Teams: " << endl;
    cout <<   "----------------------" << endl;
    for(int i = 0; i < AmLgTeams.size(); i++){
        cout << AmLgTeams[i].teamName << endl;
    }
    
    // Output Teams in the National League Descending by most wins
    cout << "\nNational League Teams by most winning: " << endl;
    cout <<   "--------------------------------------" << endl;
    sortVectorWinning(NatLgTeams);
    for(int i = 0; i < NatLgTeams.size(); i++){
        cout << NatLgTeams[i].seriesWins << " World Series Wins " << NatLgTeams[i].teamName << endl;
    }
    
    // Output Teams in the American League
    cout << "\nAmerican League Teams by most winning: " << endl;
    cout <<   "--------------------------------------" << endl;
    sortVectorWinning(AmLgTeams);
    for(int i = 0; i < AmLgTeams.size(); i++){
        cout << AmLgTeams[i].seriesWins << " World Series Wins " << AmLgTeams[i].teamName << endl;
    }
    
    // Close Files
    inTeams.close();
    inLeague.close();
    inWinners.close();
    
    return 0;
}

// Bubble sort descending order for most wins
void sortVectorWinning(vector<struct team>& teamSort){
    bool swap;
    struct team temp;
    do{
        swap = false;
        for(int i = 0; i < teamSort.size()-1; i++){
            if(teamSort[i].seriesWins < teamSort[i+1].seriesWins){
                temp = teamSort[i];
                teamSort[i] = teamSort[i+1];
                teamSort[i+1] = temp;
                swap = true;
            }
        }
    }while(swap);
}
