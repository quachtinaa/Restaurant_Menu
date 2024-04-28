//From: http://stackoverflow.com/questions/514420/how-to-validate-numeric-input-c 
// for input validation

#include <ios>  
#include <iostream> 
#include <string>
#include <sstream>

using namespace std;

// function prototypes
int validateInt(int &);
double validateDouble(double &);
string validateString(string &);
char validateChr(char &);

template <typename T>
T getValidatedInput()
{
    // Get input of type T
    T result;
    cin >> result;

    // Check if the failbit has been set, meaning the beginning of the input
    // was not type T. Also make sure the result is the only thing in the input
    // stream, otherwise things like 2b would be a valid int.
    if (cin.fail() || cin.get() != '\n')
    {
        // Set the error state flag back to goodbit. If you need to get the input
        // again (e.g. this is in a while loop), this is essential. Otherwise, the
        // failbit will stay set.
        cin.clear();

        // Clear the input stream using and empty while loop.
        while (cin.get() != '\n')
            ;

        // Throw an exception. Allows the caller to handle it any way you see fit
        // (exit, ask for input again, etc.)
        throw ios_base::failure("Invalid input.");
    }

    return result;
}

//Function Definitions

// function to validate if input is an integer
int validateInt(int &intInput)
{
  while (true)
    {

        try
        {
            intInput = getValidatedInput<int>();
        }
        catch (exception e)
        {
            cerr << e.what() << endl;
            continue;
        }

        break;
    }

    return intInput; 
}

// function to validate if input is a double
double validateDouble(double &doubleInput)
{
  while (true)
    {

        try
        {
            doubleInput = getValidatedInput<double>();
        }
        catch (exception e)
        {
            cerr << e.what() << ": Invalid input."<< endl;
            continue;
        }

        break;
    }

    return doubleInput; 
}

// function to validate if input is string
string validateString(string &stringInput)
{
    while (true) 
    {

        try
        {
            stringInput  = getValidatedInput<string>();
        }
        catch (exception e)
        {
            cerr << e.what() << ": Invalid input."<< endl;
            continue;
        }

        break;
    }

    return stringInput; 
}

// function to validate if input is char
char validateChar(char &charInput)
{ 
    while (true)
    {

        try
        {
            charInput = getValidatedInput<char>();
        }
        catch (exception e)
        {
            cerr << e.what() << ": Invalid input."<< endl;
            continue;
        }

        break;
    }

    return charInput; 
}