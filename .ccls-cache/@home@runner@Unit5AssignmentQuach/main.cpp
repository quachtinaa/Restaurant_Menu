// Tina Quach
// COSC-1437-58002 - Dr.T
// Date: 04/25/2024
// menu-driven restaurant program
// Credit to Dr. T for making the outline and menu

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class MenuItem
{
  private:
    string name;
    double itemCost; 
    string desc; 
    char addLetter; 
    char removeLetter;
    int count;    
  public:
    MenuItem(){name = "Default Name", itemCost = 0.0, desc = "Default Description", addLetter = '\0', removeLetter = '\0', count = 0;} // default constructor

    // setters, mutators
    void setName(string n){name = n;}
    void setItemCost(double i){itemCost = i;}
    void setDesc (string d) {desc = d;}
    void setAddLetter (char a) {addLetter = a;}
    void setRemoveLetter (char r) {removeLetter = r;}
    void setCount (int c) {count = c;}

    // getters, accessors
    string getName() const {return name;}
    double getItemCost() const {return itemCost;}
    string getDesc() const {return desc;}
    char getAddLetter() const {return addLetter;}
    char getRemoveLetter() const {return removeLetter;}
    int getCount() const {return count;}

};

// prototypes
void populateMenu (vector<MenuItem> &entireMenu);
void showMenu (vector<MenuItem> &m);
void acceptOrder (vector<MenuItem> &m);
void printReceipt(vector<string> itemNames, double, double, double, double, double);


int main()

{
  // object of MenuItem class
  vector<MenuItem> wholeMenu; 
  
  populateMenu(wholeMenu); // put some default values in the menu
  showMenu(wholeMenu); // print the current data of the menu on screen 
  acceptOrder(wholeMenu); 
  
  return 0;
}

//function definitions
void populateMenu(vector<MenuItem> &entireMenu)
{
  //put some default values in our Menu
  const int numItems = 7; 
  MenuItem Item1; 
  MenuItem Item2;
  MenuItem Item3; 
  MenuItem Item4;
  MenuItem Item5;
  MenuItem Item6;
  MenuItem Item7;    

  entireMenu.push_back(Item1); //add to the end of list the Item1
  entireMenu.push_back(Item2); //add to the end of list the Item2
  entireMenu.push_back(Item3); //add to the end of list the Item3
  entireMenu.push_back(Item4); //add to the end of list the Item4
  entireMenu.push_back(Item5); //add to the end of list the Item5
  entireMenu.push_back(Item6); //add to the end of list the Item6
  entireMenu.push_back(Item7); //add to the end of list the Item7

  vector<string> defaultMenuNames = {"Green Tea", "Burrito", "Ramen", "Burger", "Coke-Cola", "Nachos", "Lemonade"}; 
  vector<char> defaultAddLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G'}; 
  vector<char> defaultRemoveLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g'}; 

  // add each item to the default list efficiently
  for(int i = 0; i < numItems; i++)
  {
    entireMenu[i].setName(defaultMenuNames[i]);
    entireMenu[i].setAddLetter(defaultAddLetters[i]);
    entireMenu[i].setRemoveLetter(defaultRemoveLetters[i]); 
    entireMenu[i].setItemCost(3.00 + i); // set a random starter cost for each item
    entireMenu[i].setCount(0); // initialze all counts to 0
    entireMenu[i].setDesc("delicious"); // set all default desc to "delicous"
  }

}

void showMenu(vector<MenuItem> &m)
{
  cout << fixed << setprecision(2); // set doubles to 2 decimal places
  cout << "Dr. T's Effcient Menu" << endl; 
  cout << "ADD  \tNAME \t COST \tREMOVE\tCOUNT\tDESC"<<endl; 
  for(int i = 0; i < m.size(); i++)
  {
    cout << m[i].getAddLetter() << ")" << setw(10) << m[i].getName() << setw(5) << "$" << m[i].getItemCost() << setw(5) << "(" << m[i].getRemoveLetter() << ")" << setw(7) << m[i].getCount() << setw(13) << m[i].getDesc() << endl; 
  
  }

}

void acceptOrder(vector<MenuItem> &m)
{
  char option = '\0'; // the user-selected menu item
  char tipChoice = '\0';
  double subtotal = 0.0;
  vector<string>itemNames;

  do
  {
    cout << "\nPlease choose an item (x to Exit): ";
    cin >> option; 

    for(int i = 0; i < m.size(); i++)
    {
      if (option == m[i].getAddLetter())
      {
        cout << "\nMenu Item " << m[i].getAddLetter() << " selected."; 
        m[i].setCount(m[i].getCount() + 1); // increment the count by 1
        cout << "\033[2J\033[1;1H"; //clear screen 
        cout << "\n1 UP on " << m[i].getName() << endl;
        subtotal += m[i].getItemCost(); // increment the subtotal by the cost of the item 
        showMenu(m); // show the updated menu
        cout << "\nSubtotal: $" << subtotal << endl;  
        itemNames.push_back(m[i].getName());
      }
      else if(option == m[i].getRemoveLetter())
      {
        cout << "\nRemove Item " << m[i].getRemoveLetter() << " selected."; 
        if(m[i].getCount() > 0) // subtract if and only if the count is > 0
        {
          m[i].setCount(m[i].getCount() - 1); // decrement the count by 1
          cout << "\033[2J\033[1;1H"; //clear screen 
          cout << "\n1 DOWN on " << m[i].getName() << endl;
          subtotal -= m[i].getItemCost(); // decrement the subtotal by the cost of the item
          showMenu(m); //show the updated menu
          cout << "\nSubtotal: $" << subtotal << endl;  
        }
        else // if item count >= 0 then can't remove
        {

            cout << "\nItem count must be > 0 to remove: " << m[i].getName() << endl;
        }
      }
      else if(
                option != m[i].getAddLetter() && 
                option != m[i].getRemoveLetter() &&
                option != 'x' &&
                option != 'X' 
            ) // test for all of my valid inputs
            {
              if(i == 0)
              {
                cout << "\nInvalid input (" << option << "). Please try again." << endl; 
              }  
            }
    }
  } while(option != 'x' && option != 'X'); 
  cout << "\nThank you for placing your order." << endl; 

  cout << "Would you like to tip? (Y/N): ";
  cin >> tipChoice;
  double tipAmount = 0.0;
  if (tipChoice == 'Y' || tipChoice == 'y')
  {
    cout << "\nHow much would you like to tip? (suggest 20% or more, enter in decimal): ";
    cin >> tipAmount;
  }

  char payment = '\0';
  double tipping = (subtotal * tipAmount);
  double tax = (subtotal * 0.0825);
  double amount = subtotal + tipping + tax;
  double tender = 0.0;
  
  // tipping/receipt
  cout << "\nYour total amount after tipping and taxes is " << amount << endl;
  cout << "\nWould you like to pay with cash or credit? (A for cash / R for credit): ";
  cin >> payment;
  if (payment == 'A' || payment == 'a')
  {
    cout << "\nPlease enter your cash amount: ";
    cin >> tender;

    if (tender >= amount)
    {
      cout << "Your change is $" << tender - amount << endl;
    }
    printReceipt(itemNames, subtotal, amount, tipping, tax, tipAmount);
  }
  else if (payment == 'R' || payment == 'r')
  {
    cout << "Processing Payment..." << endl;
    cout << "Your payment has been processed." << endl;
    printReceipt(itemNames, subtotal, amount, tipping, tax, tipAmount);
  }
  
}

void printReceipt(vector<string> itemNames, double subtotal, double amount, double tipping, double tax, double tipAmount)
{
  cout << "\n\nHere is your receipt! Thank you for coming, have an amazing day!" << endl;
  cout << "\n----------------------------" << endl;
  cout << "YOUR RECEIPT" << endl;

  // display items
  cout << "----------------------------" << endl;
  for (int j = 0; j < itemNames.size(); j++)
    {
    cout << itemNames[j] << endl;
    }

  // display money portion
  cout << "----------------------------" << endl;
  cout << "AMOUNT: " << amount << endl;
  cout << "Subtotal: " << subtotal << endl;
  cout << "Sales Tax: " << tax << endl;
  cout << "Tipping (" << tipAmount << "): " << tipping << endl;
}