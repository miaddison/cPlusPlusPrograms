/*
    Name: Merna Addison
    Date: 9/29/17
    email: merna.addison@gmail.com
    Course: Advanced c++
    Week 5: Programming assignment 3 
    Description: This program allows a user to input a stocks three year high, three year low, and three current prices. The program then determines if stock prices are going up or going down. The program then finds the next fibonacci number beyond the high and beyond the low. Then if the price is going up, it determines if the current price is within 20% of next higher fibonacci. Then if the price is going down, it determines if the current price is within 20% of next lower fibonacci. If the price is stable, it determines if the current price is within 20% of the next higher or lower fibonacci numbers. The program will output to sell the stock when it reaches the high fibonacci number if the current is within 20%, to buy the stock when it reaches the low fibonacci number if the current is within 20%, and to hold if neither applies.
*/

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <numeric>
using namespace std;

// The beginning an ending points for the Fibonacci array
const int maxInput = 1500;
const int minInput = 1;

//Functions
int fib(int num);
bool verifyInput(int inputNum);
void outputFib(int lowFib, int highFib);
void lowThresOutput(int lowFib);
void highThresOutput(int highFib);

int main()
{
    double twentyPercentDiff = .80;
    int fibonacci = 0;
    int highFib = 0;
    int lowFib = 0;
    int number = minInput;
    double threeYearHigh = 0;
    double threeYearLow = 0;
    double current = 0;
    string msg = "";
    bool fibFlag = false;
    bool inputValid = false;
    bool priceDown = false;
    bool priceUp = false;
    bool lowThreshold = false;
    bool highThreshold = false;
    vector<int>fibArray;
    vector <double> recentPrices;
    
    // Output directions and have user input the highest stock price over three years repeats until valid data entered
    while(!inputValid){
        cout << "Please enter the highest value of the stock over the last three years: " << endl;
        cout << "(Must be a number between 1 and 1500.)" << endl;
        cin >> threeYearHigh;
        inputValid = verifyInput(threeYearHigh);    // input verification
    }
    
    // Output directions and have user input the lowest stock price over three years repeats until valid data entered
    inputValid = false;
    while(!inputValid){
        cout << "Please enter the lowest value of the stock over the last three years: " << endl;
        cout << "(Must be a number between 1 and 1500.)" << endl;
        cin >> threeYearLow;
        inputValid = verifyInput(threeYearLow);     // input verification
    }
    
    // Output directions and have user input the current stock price repeats until valid data entered
    /*
    inputValid = false;
    while(!inputValid){
        cout << "Please enter the current value of the stock: " << endl;
        cout << "(Must be number between 1 and 1500.)" << endl;
        cin >> current;
        inputValid = verifyInput(current);      // input verification
    }
     */
    
    // Have user enter in last few stock prices repeat until valid data entered for all three last price entered remains the "current"
    cout << "Enter the 3 most recent stock prices(oldest to newest): " << endl;
    cout << "(Must be number between 1 and 1500.)" << endl;
    for(int i = 0; i < 3; i++){
        inputValid = false;
        while(!inputValid){
            cin >> current;
            inputValid = verifyInput(current);  //input verification
            if(!inputValid){ // output which number needs re-entered
                if(i == 0)
                    msg = "oldest";
                else if(i == 1)
                    msg = "middle";
                else
                    msg = "latest";
                cout << "Enter the " << msg << " of the three most recent stock prices: " << endl;
                cout << "(Must be number between 1 and 1500.)" << endl;
            }else{
                recentPrices.push_back(current);
            }
        }
    }
   
    // output recent prices array to check
    /*for(int i = 0; i < recentPrices.size(); i++){
        cout << recentPrices[i] << endl;
    }*/
    
    // if recent prices going up (2nd higher than first and third higher or same as first, or third higher than first and ignore second if lower)
    if((recentPrices[0]<recentPrices[1] && recentPrices[0]<=recentPrices[2]) || (recentPrices[0]<recentPrices[2])){
        //cout << "Prices are going up." << endl;   // testing
        priceUp = true;
    }// if recent prices going down (2nd lower than first and third lower or same as first, or third lower than first and ignore second if higher)
    else if((recentPrices[0]>recentPrices[1] && recentPrices[0]>=recentPrices[2]) || (recentPrices[0]>recentPrices[2])){
        //cout << "Prices are going down." << endl; //testing
        priceDown = true;
    }else{
        //cout << "Prices are stable." << endl; //testing
    }
    
    // Runs recursive fibonacci function to populate an array with the sequence chose a do while to get next number after 1500
    do{
        fibonacci = fib(number);
        fibArray.push_back(fibonacci);
        //cout<<"Fibonacci("<<number<<") = "<<fibonacci<<"\n"; // testing fibonacci sequence was correct
        number++;
    }while(fibonacci <= maxInput);
    
    /*for(int i = 0; i < fibArray.size(); i++){     // testing to ensure fibonacci array was correct
        cout << fibArray[i] << endl;
    }*/
    
    // find the fibonacci number that is the next highest to the three year high for the stock
    for(int i = 0; i < fibArray.size(); i++){
        if(fibArray[i] > threeYearHigh && !fibFlag){
            highFib = fibArray[i];
            //cout <<highFib << endl;   // testing
            fibFlag = true;
        }
    }
    
    // find the fibonacci number that is the next lowest to the three year low for the stock
    fibFlag = false;
    for(long i = fibArray.size()-1; i >= 0; i--){
        if(fibArray[i] < threeYearLow && !fibFlag){
            lowFib = fibArray[i];
            //cout <<lowFib << endl;    // testing
            fibFlag = true;
        }
    }
    
    // if within 20% of next highest fib number flag highThreshold true
    if(current/highFib >= twentyPercentDiff){
        highThreshold = true;
    }
    
    // if within 20% of next lowest fib flag lowThreshold true
    if(lowFib/current >= twentyPercentDiff){
        lowThreshold = true;
    }
    
    // check if within 20% threshold to buy or sell depending
    if(priceUp){ // check next next highest fib if price is up
        outputFib(lowFib, highFib);
        cout << "Prices are moving upwards and the current price is " << current << "." << endl;
        if(highThreshold){ // if within 20% of next highest fib number
            //cout << "current: " << current <<  " 20% threshold: " << (highFib-twentyPercentDiff) << endl; // testing
            highThresOutput(highFib);
        }else{ // if not within 20% of next highest fib number
            cout << "This is not within the 20% of the next higher fibonacci number." << endl;
            cout << "Hold on this stock for now." << endl;
        }
    }else if(priceDown){ // check next next lowest fib if price is going down
        outputFib(lowFib, highFib);
        cout << "Prices are moving downwards and the current price is " << current << "." << endl;
        if(lowThreshold){ // if within 20% of next lowest fib
            //cout << "Most Current: " << current <<  " 20% threshold: " << (lowFib + twentyPercentDiff) << endl;   // testing
            lowThresOutput(lowFib);
        }else{ // if not within 20% of next lowest fib
            cout << "This is not within the 20% of the next lower fibonacci number." << endl;
            cout << "Hold on this stock for now." << endl;
        }
    }else{ // if prices stable
        outputFib(lowFib, highFib);
        cout << "Prices are steady and the current price is " << current << "." << endl;
        if(highThreshold){ // if within 20% of next highest fib number
            //cout << "current: " << current <<  " 20% threshold: " << (highFib-twentyPercentDiff) << endl; // testing
            highThresOutput(highFib);
        }
        if(lowThreshold){ // if within 20% of next lowest fib
            //cout << "Most Current: " << current <<  " 20% threshold: " << (lowFib + twentyPercentDiff) << endl;   // testing
            lowThresOutput(lowFib);
        }else{
            cout << "The current price is not within the 20% of the next higher or lower fibonacci number." << endl;
            cout << "Hold for now and re-evaluate when the price changes." << endl;
        }
    }
    return 0;
}

// Recursive Fibonacci function
int fib(int num){
    if(num==0||num==1){
        return num;
    }else{
        return (fib(num-2)+fib(num-1));
    }
}

// Function to verify that the user input a stock price between 1 and 1500
bool verifyInput(int inputNum){
    if(inputNum>=minInput && inputNum<=maxInput){
        return true;
    }else{
        // clears error (ex. if string entered)
        cin.clear();
        // removes any bad data that was entered
        cin.ignore(INT_MAX, '\n');
        return false;
    }
}

//Output the high and low fibonacci numbers
void outputFib(int lowFib, int highFib){
    cout << "The next highest fibonacci number is " << highFib << endl;
    cout << "The next lowest fibonacci number is " << lowFib << endl;
}

//output directions for current within 20% of lowfib
void lowThresOutput(int lowFib){
    cout << "This is within 20% of the next lower fibonacci number of " << lowFib << "." << endl;
    cout << "We advise that you buy this stock if it reaches " << lowFib << "." << endl;
}

//output directions for current within 20% of highfib
void highThresOutput(int highFib){
    cout << "This is within 20% of the next higher fibonacci number of " << highFib << "." << endl;
    cout << "We advise that you sell this stock if it reaches " << highFib << "." << endl;
}
