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
void printReceipt(vector<string> itemNames, vector<double> itemCosts, vector<MenuItem> m, double, double, double, double, double, char, double);


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

  vector<string> defaultMenuNames = {"Green Tea", "Lemonade", "Fruit Tart", "Calamari", "Veggie Wrap", "Fish Fillet", "Smoked Steak"}; 
  vector<char> defaultAddLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G'}; 
  vector<char> defaultRemoveLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  vector<string> defaultDescriptions = {"Refreshing beverage packed w/ antioxidants", "Tangy, sweet citrus drink", "Flaky pastry filled w/ fresh fruit and custard", "Crispy, golden squid rings w/ spicy mayo sauce", "Fresh veggies within a soft tortilla", "Seasoned fish fillet w/ tangy tartar sauce", "Premium steak w/ a side of mashed potatoes"};
  vector<double> defaultItemCosts = {3.25, 3.25, 5.50, 9.75, 11.75, 18.75, 20.75 };
  // add each item to the default list efficiently
  for(int i = 0; i < numItems; i++)
  {
    entireMenu[i].setName(defaultMenuNames[i]);
    entireMenu[i].setAddLetter(defaultAddLetters[i]);
    entireMenu[i].setRemoveLetter(defaultRemoveLetters[i]); 
    entireMenu[i].setItemCost(defaultItemCosts[i]); 
    entireMenu[i].setCount(0); // initialze all counts to 0
    entireMenu[i].setDesc(defaultDescriptions[i]);
  }

}

void showMenu(vector<MenuItem> &m)
{
  cout << fixed << setprecision(2); // set doubles to 2 decimal places
  cout << "\t\t\t\t\t\t\t\t\t LETTUCE EAT" << endl; 
  cout << "--------------------------------------------------------------------------------------" << endl;
  cout << "ADD  \tNAME \t  COST\tREMOVE\tCOUNT\t DESC"<<endl; 
  for(int i = 0; i < m.size(); i++)
  {
    cout << m[i].getAddLetter() << ")" << setw(13) << m[i].getName() << setw(3) << "$" << m[i].getItemCost();
    if (m[i].getRemoveLetter() == 'a' || m[i].getRemoveLetter() == 'b' || m[i].getRemoveLetter() == 'c' || m[i].getRemoveLetter() == 'd')
    {
      cout << setw(4) << "(" << m[i].getRemoveLetter() << ")";
    }
    else if (m[i].getRemoveLetter() == 'e' || m[i].getRemoveLetter() == 'f' || m[i].getRemoveLetter() == 'g')
    {
      cout << setw(3) << "(" << m[i].getRemoveLetter() << ")";
    }
    cout << setw(5) << m[i].getCount() << "      " << m[i].getDesc() << endl; 
  
  }

}

void acceptOrder(vector<MenuItem> &m)
{
  char option = '\0'; // the user-selected menu item
  char tipChoice = '\0';
  double subtotal = 0.0;
  vector<string>itemNames;
  vector<double>itemCosts;

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
        itemCosts.push_back(m[i].getItemCost());
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

  cout << "\nWould you like to tip 20% or more? (Y/N): ";
  cin >> tipChoice;
  double tipAmount = 0.0;
  if (tipChoice == 'Y' || tipChoice == 'y')
  {
    cout << "\nEnter tip amount (in decimal): ";
    cin >> tipAmount;
  }

  char payment = '\0';
  double tipping = (subtotal * tipAmount);
  double tax = (subtotal * 0.0825);
  double amount = subtotal + tipping + tax;
  double tender = 0.0;
  
  // tipping/receipt
  cout << "\nYour total amount after tipping and taxes is " << amount << endl;
  cout << "\nWould you like to pay with cash or credit card? (A for cash / R for credit): ";
  cin >> payment;
  if (payment == 'A' || payment == 'a')
  {
    cout << "\nPlease enter your cash amount: ";
    cin >> tender;

    if (tender >= amount)
    {
      cout << "\nYour change is $" << tender - amount << endl;
    }
    printReceipt(itemNames, itemCosts, m, subtotal, amount, tipping, tax, tipAmount, payment, tender);
  }
  else if (payment == 'R' || payment == 'r')
  {
    cout << "Processing Payment..." << endl;
    cout << "Your payment has been processed." << endl;
    printReceipt(itemNames, itemCosts, m, subtotal, amount, tipping, tax, tipAmount, payment, tender);
  }
  
}

void printReceipt(vector<string> itemNames, vector<double> itemCosts, vector<MenuItem> m, double subtotal, double amount, double tipping, double tax, double tipAmount, char payment, double tender)
{
  cout << "\n\nHere is your receipt! Thank you for coming, have an amazing day!" << endl;
  cout << "\n----------------------------" << endl;
  cout << "YOUR RECEIPT" << endl;

  // display items
  cout << "----------------------------" << endl;
  for (int j = 0; j < itemNames.size(); j++)
    {
    cout << itemNames[j] << setw(20) << itemCosts[j] << endl;
    }

  // display money portion
  cout << "----------------------------" << endl;
  cout << "AMOUNT: " << amount << endl;
  cout << "Subtotal: " << subtotal << endl;
  cout << "Sales Tax: " << tax << endl;
  cout << "Tipping (" << tipAmount << "): " << tipping << endl;
  cout << "----------------------------" << endl;
  if (payment == 'A')
  {
    cout << "CASH" << setw(20) << tender << endl;
    cout << "----------------------------" << endl;
    cout << "Change Due" << setw(20) << tender - amount << endl;
  }
  else if (payment == 'R')
  {
    cout << "CREDIT CARD" << setw(24) << amount << endl;
    cout << "************1234" << endl;
    cout << "----------------------------" << endl;
    cout << "Change Due" << setw(18) << "$0.00" << endl;
  }
}