#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
#include <cctype>

/****************************
 *
 * HEADER
 *
 * *** **********************/


const string rule_msg_1 = "The selected password must be at least eight characters long.";
const string rule_msg_2 = "The selected password must have at least one uppercase letter.";
const string rule_msg_3 = "The selected password must have at least one lowercase letter.";
const string rule_msg_4 = "The selected password must have at least one digit.";
const string rule_msg_5 = "The selected password must have at least one of special characters: [@,!,#,^,&,*,$]";
const string rule_msg_6 = "The selected password has been leaked.";
const string rule_msg_7 = "The selected password cannot contain a dictionary word.";



	
/****
 * Runs the main part of the program
 ****/


// this function checks if the string is 8 or greater 
bool passwordLengthCheck(string password)
{
  return(password.length() >= 8); // return true if it the conditional is true return false otherwise
}


/* this function checks if the string has 
uppercase letters */
bool uppercaseCheck(string password)
{
  int count = 0;
  for(int i = 0; i < password.length(); i++)
    {
      if(isupper(password[i]) > 0) // checks through each character of the string if there are uppercase letters
      {
        count++; // if there are uppercase letters, increase count by 1 
      }
    }
  if(count == 0) // if count is 0 then there are no uppercase letters
  {
    return false;
  }
  else // else if count has more than 0 then there are uppercase letters
  {
    return true;
  }
}


/* this function checks if the password has
lowercase letters or not */
bool lowercaseCheck(string password)
{
  int count = 0;
  for(int i = 0; i < password.length(); i++)
    {
      if(islower(password[i]) > 0) // checks through each character of the string if there are lowercase letters.
      {
        count++; // if there are lowercase letters add 1 to count
      }
    }
  if(count == 0) // if count is 0 then there are no lowercase letters
  {
    return false;
  }
  else // else if count is more than 0 then there are lowercase letters
  {
    return true;
  }
}


/* this function checks if the password has digits
or not */
bool digitCheck(string password)
{
  int count = 0;
  for(int i = 0; i < password.length(); i++)
    {
      if(isdigit(password[i]) == true) // loop checks if each character is a number or not
      {
        count++; // if there are numbers add 1 to count
      }
    }
  if(count == 0) // if count is 0 then there are no digits
  {
    return false;
  }
  {
    return true; // else if count is more than 0 then there are digits
  }
}


/* this function checks if the password has special characters 
or not */
bool specialCharacterCheck(string password)
{
  int count = 0;
  for(int i = 0; i < password.length(); i++)
  {
    if(password[i] == 64 || password[i] == 33 || password[i] == 35 // these integers are the ASCII values of the special characters
		|| password[i] == 94 || password[i] == 38 || password[i] == 42 // if there are special characters add 1 to count
		|| password[i] == 36)
		  {
      count++; // if there are special characters add 1 to count
      }
  }

  if(count == 0) // if count has nothing then there are no special characters.
  {
    return false;
  }
  else // if count has more than 0 than there are special characters.
  {
    return true;
  }
}

/* this function removes all special characters to use for 
rule 6 check */

string clean_string(string in) {
  string out = "";
  for(int i = 0; i < in.size(); i++) {
    if(in[i] == '@' || in[i] == '!' || in[i] == '#' || in[i] == '^' || in[i] == '&' || in[i] == '*' || in[i] == '$') // conditionals for special characters
    {
      out += ""; // if there are special characters, add nothing to the new string
    }
    else
    {
      out += tolower(in[i]); // if it is anything else, add it to the new string
    }
  }
  return out;
}


/* this function removes everything but alphabets
for rule 7 check */
string clean_string2(string in) {
  string out = "";
  for(int i = 0; i < in.size(); i++) {
    if(isalpha(in[i])) // if the character is an alphabet add it to the new string
    {
      out += tolower(in[i]);
    }
  }
  return out;
}


// compare function for rule 6 check
bool compare(string pass, vector<string> list)
{

  // sets the lowest and highest value for the binary check
  int low = 0;
  int high = list.size() - 1;

  pass = clean_string(pass); // runs clean_string for rule 6 check

  // binary check for the leaked passwords
  while(low <= high)
  {
    int mid = (low + high) / 2; // gets the middle index of the lowest and highest value in the binary search
    string str = clean_string(list.at(mid)); // runs clean_string for the leaked passwords FOR the found value of the binary search

    // If string at middle is substring of pass, then password is invalid
    if(pass.find(str) != string::npos)
    {
      return true;
      break;
    }
    else if(pass > str) // if the password is higher value than middle found string, chop off from the middle and continue up from there
    {
      low = mid + 1; // sets new value of low due to conditional
    }
    else // if the password is lower value than the middle found string, chop off from the middle and search from everything before the middle
    {
      high = mid - 1; // sets the new value of the highest to check due to conditonal.
    }
  }
  return false;
}


// compare function for rule 7 check
bool compare2(string pass, vector<string> list)
{
  // sets the lowest and highest value for the binary check
  int low = 0;
  int high = list.size() - 1;

  pass = clean_string2(pass); // runs clean_string for rule 7 check

  // binary check for the dictionary words
  while(low <= high)
  {
    int mid = (low + high) / 2; // gets the middle index of the lowest and highest value in the binary search
    string str = clean_string2(list.at(mid)); // runs clean_string2 for the dictionary word found from binary search

    // If string at middle is substring of pass, then password is invalid
    if(pass.find(str) != string::npos) 
    {
      return true;
      break;
    }
    else if(pass > str) // if the password is higher value than middle found string, chop off from the middle and continue up from there
    {
      low = mid + 1; // sets new value of low due to conditional
    }
    else  // if the password is lower value than the middle found string, chop off from the middle and search from everything before the middle
    {
      high = mid - 1; // sets the new value of the highest to check due to conditonal.
    }
  }
  return false;
}

int run(string leaked_password_file, string english_word_file)
{
  /* lines 234 to 253 opens the files of the leaked passwords and the dictionary words.
  then creates a vector and while the file is NOT empty, add the words / passwords
  into their respective vectors */
  ifstream leakedPass;
  leakedPass.open(leaked_password_file);

  ifstream dictionaryWords;
  dictionaryWords.open(english_word_file);

  string word;

  vector<string> leakedPasswords;
  vector<string> dictionary;

  while(getline(leakedPass, word))
  {
    leakedPasswords.push_back(word);
  }

  while(getline(dictionaryWords, word))
  {
    dictionary.push_back(word);
  }
  //


  string userPassword;
  cout << "Enter password: ";
  cin >> userPassword;
  int count = 0; // conditional for accepted passwords and unacceptable passwords.

  if(passwordLengthCheck(userPassword) == false) { // runs passwordLengthCheck and if it is false, output msg1, else add 1 to count
    cout << rule_msg_1 << endl;
  } else {
    count++;
  }

  if(uppercaseCheck(userPassword) == false) { // runs uppercaseCheck and if it is false, output msg2, else add 1 to count
    cout << rule_msg_2 << endl;
  } else {
    count++;
  }

  if(lowercaseCheck(userPassword) == false) { // runs lowercaseCheck and if it is false, output msg3, else add 1 to count
    cout << rule_msg_3 << endl;
  } else {
    count++;
  }

  if(digitCheck(userPassword) == false) { // runs digitCheck and if it is false, output msg4, else add 1 to count
    cout << rule_msg_4 << endl;
  } else {
    count++;
  }

  if(specialCharacterCheck(userPassword) == false) { // runs specialCharacterCheck and if it is false, output msg5, else add 1 to count
    cout << rule_msg_5 << endl;
  } else {
    count++;
  }

  if(compare(userPassword, leakedPasswords) == true) { // runs compare and if it is true, output msg6 as well as password rejected
    cout << rule_msg_6 << endl;
    cout << "Password rejected!" << endl;
    return 0;
  }

  if(compare2(userPassword, dictionary) == true) // runs compare2 and if it is true, output msg7 as well as password rejected
  {
    cout << rule_msg_7 << endl;
    cout << "Password rejected!" << endl;
    return 0;
  }

  if(count == 5) { // if count is 5 then output password accepted else output password rejected
    cout << "Password accepted!" << endl;
  } else {
    cout << "Password rejected!" << endl;
  }

  return 0;
}

int main() {
	/** Change the address of the files appropriatly based on your local machine.
	 * This main function will be replaced during testing. Do not add any line of code to the main function 
	 **/
	string leaked_password_file = "alleged-gmails.txt"; //change this based on the location of the file on your machine
	string english_word_file = "dictionary-words.txt"; //change this based on the location of the file on your machine
	run(leaked_password_file, english_word_file);
	return 0;	
}