#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 11
//=====================================================

// --------- Two DFAs ---------------------------------

//Reusable letters
string consonants = "bghkmnpr";
string consonantsOther = "djwyz";
string vowels = "aeiouIE";

/*
Done by: Ian M, Kyle H, Dylan K

Description: This function will determine if the character is in the string we pass as a parameter.
Parameters: 
character - is the character we are checking for in the str.
str - This is either the consonant, consonantOther, or vowels string that is searched through to find the character if its there.
Locals: NONE
Return: True if found, false if not found.
*/
bool checkCharInChars(char character, string str) {
  //looping through chars in character groups
  for(int i = 0; i<str.length();i++){
    //if the char passed in is in the character group, return true
    if(str[i] == character){
      return true;
    }
  }
  //otherwise return false
  return false;
}

// WORD DFA 
// Done by: Dylan Kral, Kyle Hawkins, Ian Murphy
// RE: (vowel | vowel n | consonant vowel| consonant vowel n | consonant-pair vowel | consonant-pair vowel n)^+

/* 
Q0 = 1       	qsa = 5
Qy = 2       	qt = 6
Qc = 3		q1q0 = 7
Qs = 4		q0qy = 8
*/


/*
Done by: Ian M, Kyle H, Dylan K

Description: This functions takes in a string s and determines if it qualifies as a valid word
Parameters: 
s - the string we are trying to validate
Locals:
state - the current state of the DFA
charpos - the pointer to the current char of the string s
Return: true is tue string is a word, false otherwise
*/
bool word (string s)
{
  //state is initally 1, charpos initially 0
  int state = 1;
  int charpos = 0;
  // replace the following todo the word dfa
  while (s[charpos] != '\0') 
    {
      //state 1 || Q0
      if (state == 1 && s[charpos] == 'c'){
        state = 3;//Qc    
      }
      else if (state == 1 && s[charpos] == 't'){
        state = 6;//Qt
      }
      else if(state == 1 && s[charpos] == 's')
      {
        state = 4;//Qs
      }
      else if (state == 1 && checkCharInChars(s[charpos], vowels))      
      {
        state = 7;//Q1Q0 
      }
      else if (state == 1 && checkCharInChars(s[charpos], consonantsOther))      {
        state = 5;//Qsa
      }
      else if (state == 1 && checkCharInChars(s[charpos], consonants)){
        state = 2;//Q
      }


      //state 2 || Qy  
      else if (state == 2 && s[charpos] == 'y'){ 
        state = 5;//Qsa
        
      }
      else if (state == 2 && checkCharInChars(s[charpos], vowels)){
        state = 7;//Q1Q0
        
      }


      //state 3 || Qc  
      else if (state == 3 && s[charpos] == 'h'){
        state = 5;//Qsa
         
      }

      //state 4 || Qs
      else if (state == 4 && s[charpos] == 'h'){
        state = 5;//Qsa
        
      }
      else if (state == 4 && checkCharInChars(s[charpos], vowels)){
        state = 7;//Q1Q0
      }

        
      else if (state == 5 && checkCharInChars(s[charpos],vowels)){
        state = 7;//Q1Q0
      }


      else if(state == 6 && checkCharInChars(s[charpos], vowels)){
        state = 7;//Q1Q0
      }
      else if(state == 6 && s[charpos] == 's'){
        state = 5;//Qsa
      }

        
      else if(state == 7 && s[charpos] == 'n'){
        state = 8;//Q0Qy
      }
      else if(state == 7 && checkCharInChars(s[charpos], vowels)){
        state = 7;//Q0Q1
      }
      else if(state ==7 && s[charpos] == 's'){
        state = 4;//Qs
      }
      else if(state == 7 && s[charpos] == 'c'){
        state = 3;//Qc
      }
      else if(state == 7 && s[charpos] == 't'){
        state = 6;//Qt
      }
      else if(state == 7 && checkCharInChars(s[charpos], consonants)){
        state = 2;//Qy
      }
      else if(state == 7 && checkCharInChars(s[charpos], consonantsOther)){
        state = 5;//Qsa
      }

      //state 8 || Q0Qy
      else if (state == 8 && checkCharInChars(s[charpos],consonants))
      {
        state = 2;//Qy
      }
      else if (state == 8 &&checkCharInChars(s[charpos],consonantsOther))
      {
        state = 5;//Qsa
      }
      else if (state == 8 && checkCharInChars(s[charpos],vowels))
      {
        state = 7;//Q1Q0
      }
      else if (state == 8 && s[charpos] == 's')
      {
        state = 4;//Qs
      }
      else if (state == 8 && s[charpos] == 't')
      {
        state = 6;//Qt
      }
      else if (state == 8 && s[charpos] == 'c')
      {
        state = 3;//Qsa
      }
      else
      {
	    return(false);
      }
      charpos++;
    }//end of while

  
  if (state == 1 || state == 7 || state == 8) return(true);  // end in a final state
   else return(false);
}


/* 
PERIOD DFA 
Done by: Dylan Kral, Kyle Hawkins, Ian Murphy

RE: .

Description: This is simple function that determines if the character in the first position of the string is a period.
Parameters: 
s - The string we are checking to see if a period is present in the first position.
Locals: NONE
Return: True if a period is found, false otherwise.
*/
bool period (string s) {  // complete this
  //if first char of string is a period, return true
  if(s[0] == '.'){
    return true;
  }
  //otherwise return false
  else return
    (false);
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Dylan Kral, Kyle Hawkins, Ian Murphy

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR,VERB,VERBNEG,VERBPAST,VERBPASTNEG,IS,WAS,OBJECT,SUBJECT,DESTINATION,PRONOUN,CONNECTOR, WORD1, WORD2, PERIOD, EOFM};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {"ERROR", "VERB", "VERBNEG","VERBPAST","VERBPASTNEG","IS","WAS","OBJECT","SUBJECT","DESTINATION","PRONOUN","CONNECTOR","WORD1","WORD2","PERIOD","EOFM"}; 

vector<vector<string>> reservedWords = {{"masu"}, {"masen"}, {"mashita"}, {"masendeshita"}, {"desu"}, {"deshita"}, {"o"}, {"wa"}, {"ni"}, {"watashi", "anata", "kare", "kanojo", "sore"}, {"mata", "soshite", "shikashi", "dakara"}};


/*
Done by: Ian M, Kyle H, Dylan K

Description: Checks the reserved words list to see if the word passed in is valid.
Parameters:
word - string that is being checked.
Locals:
i - counter for the appropriate array within the reserved words list.
j - counter for within the array being chosen.
Return: if word is found, return the index + 1 so the type can be found in enum 
list.
if not found return -1 indicating the word was not in the list.
*/
int checkReserved(string& word){
  //looping through columns and rows of table
  for(int i = 0;i < reservedWords.size(); i++){
    for(int j = 0;j < reservedWords[i].size(); j++){
      //if cell is equal to passed in word, return the index of the row + 1 to get corresponding enum value
      if(reservedWords[i][j] == word){
        return i+1;
      }
    }
  }
  //return -1 if not found
  return -1;
}

// ------------ Scanner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file
//Opens output file
ofstream file("translated.txt");
/* 
Scanner processes only one word each time it is called
Gives back the token type and the word itself
Done by: Ian M, Kyle H, Dylan K

Description: This function grabs the next token from the file and determines the the token type.
Parameters:
tt - Is the variable that gets assigned a token type based off the token read in from the file.
w - Is the string variable that gets assigned the token read in from the file.
Locals: NONE
Return: An interger indicated success or failure. 0 is successs. -1 is failure.
*/
int scanner(tokentype& tt, string& w)
{

  fin >> w;// ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.   
  //cout << "Scanner called using: " << w << endl;
  if (w == "eofm") {
    tt = EOFM;
    return 0;
  }
//2. Call the token functions (word and period) 
  else if (word(w)) {
    //if word is reserved
    if(checkReserved(w) != -1){
      //set tt to return from checkReserved(w)
      tt = (tokentype) checkReserved(w);
    }
    //if word ends in I or E, tt is WORD2
    else if(w[w.size()-1] == 'I'|| w[w.size()-1] == 'E'){
      tt = WORD2;
    }
    //otherwise tt is WORD1
    else {
      tt = WORD1;
    }
    return 0;
  }
  //if w is period, tt is PERIOD
  else if(period(w)) {
    tt = PERIOD;
    return 0;
  }
  else {  //Generate a lexical error message if both DFAs failed.
    tt = ERROR;//lexical error
    return -1;
  }
   //Let the tokentype be ERROR in that case.

}//the end of scanner


/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////





/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
       and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File parser.cpp written by Group Number: **
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------
tokentype  saved_token;
string  saved_lexeme;
bool token_available = false;

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  

// Type of error: Match fails
// Done by: Dylan Kral
void syntaxerror1(string lexeme, tokentype token){    
  cout << "SYNTAX ERROR1: expected " << tokenName[token] << " but found " << lexeme << endl;
  exit(1);
}
// Type of error: Switch Default
// Done by: Dylan Kral
void syntaxerror2(string lexeme, tokentype token){
  cout << "SYNTAX ERROR2: unexpected " << lexeme << " found in " << tokenName[token] << endl;
  exit(1);
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme


// next_token(void)
//    HOW: checks first to see if the token_available flag is false.
//                If so, saved_token gets scanner() result.
//                and the flag is set true.
//    A token is grabbed but is not eaten up.
//    Returns the saved_token
//   
// Purpose:  Looks ahead to see what token comes next from the scanner.
// Done by: Ian Murphy
tokentype next_token(){
  string word;
   if (!token_available)   // if there is no saved token yet
   { 
       scanner(saved_token, word);    // call scanner to grab a new token
       saved_lexeme = word;
     //cout<<"Saved Token: "<<tokenName[saved_token]<<endl; 
                                                   // saved_token is the token type and 
       // saved_lexeme is the word that is read in
       token_available = true;                              // mark that fact that you have saved it

       if (saved_token == ERROR)
       { 
            syntaxerror1(saved_lexeme, saved_token);
       }
   }
   
   return saved_token;    // return the saved token

}


//match(expected)
//  Checks and eats up the expected token.
//  HOW: checks to see if expected is different from next_token()
//              and if so, generates a syntax error and handles the error
//              else token_available becomes false (eat up) and returns true.

// Purpose: checks to see if expected is different from next_token()
// Done by: Ian Murphy
bool match(tokentype expected) {  
      if (next_token() != expected)   // mismatch has occurred with the next token+
   {
        // calls a syntax error function here to generate a syntax error message here and do recovery
        syntaxerror2(saved_lexeme, expected);
   }
   else  // match has occurred
   {
        token_available = false;
        cout << "Matched " << tokenName[expected] << endl;                 // eat up the token
        return true;                        // say there was a match
   }
  
  return false;
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

void story();
void sentence();
void after_subject();
void after_noun();
void after_object();
void noun();
void verb();
void be();
void tense();

//string filename;


// Grammar: <story> ::= <s> {<s>}
// Done by: Ian Murphy
void story(){
  bool done = false;
  cout << "Processing <story>" << endl;
  
  sentence();
  while(!done){
    switch(next_token()){
      case tokentype::CONNECTOR:
        sentence();
        break;
      case tokentype::WORD1:
        sentence();
        break;
      case tokentype::PRONOUN:
        sentence();
        break;
      case tokentype::EOFM:
        cout << "Successfully parsed <story>" << endl;
        done = true;
        break;
      default:
        syntaxerror2(saved_lexeme,saved_token);
    }
    
  }
}

 string saved_E_word;
 bool getEword(string& save_E_word);
 void gen(const string&);
// Grammar:  <s> ::= [CONNECTOR  #getEword# #gen(“CONNECTOR”)#]<noun> #getEword# SUBJECT #gen(“ACTOR”)# <after subject>
// Done by: Ian Murphy
void sentence(){
  cout<<"Processing <sentence>"<<endl;
  if (next_token() == tokentype::CONNECTOR){
    match(tokentype::CONNECTOR);
    getEword(saved_E_word);
    gen("CONNECTOR");
  }
  noun();
  getEword(saved_E_word);
  match(tokentype::SUBJECT);
  gen("ACTOR");
  after_subject();
}


// Grammar: <after subject> :: = <verb> #getEword# #gen(“ACTION”)# <tense> #gen(“TENSE”)#   PERIOD | <noun> #getEword# <after noun>
// Done by: Ian Murphy
void after_subject(){
  cout<<"Processing <after subject>"<<endl;
  switch(next_token()){
    case tokentype::WORD2:
      verb();
      getEword(saved_E_word);
      gen("ACTION");
      tense();
      gen("TENSE");
      match(tokentype::PERIOD);
      break;
    case tokentype::WORD1:
      noun();
      getEword(saved_E_word);
      after_noun();
      break;
    case tokentype::PRONOUN:
      noun();
      getEword(saved_E_word);
      after_noun();
      break;
    default:
      syntaxerror2(saved_lexeme, saved_token);
  }
}


// Grammar: <after noun> ::= <be> #gen(“DESCRIPTION”)# #gen(“TENSE”)# PERIOD | DESTINATION  #gen(“TO”)#  <verb> #getEword# #gen(“ACTION”)# <tense>  #gen(“TENSE”)# PERIOD | OBJECT #gen(“OBJECT”) <after object>
// Done by: Dylan Kral
void after_noun(){
  cout<<"Processing <after noun>"<<endl;
  switch(next_token()){
    case tokentype::IS:
      be();
      gen("DESCRIPTION");
      gen("TENSE");
      match(tokentype::PERIOD);
      break;
    case tokentype::WAS:
      be();
      gen("DESCRIPTION");
      gen("TENSE");
      match(tokentype::PERIOD);
      break;
    case tokentype::DESTINATION:
      match(tokentype::DESTINATION);
      gen("TO");
      verb();
      getEword(saved_E_word);
      gen("ACTION");
      tense();
      gen("TENSE");
      match(tokentype::PERIOD);
      break;
    case tokentype::OBJECT:
      match(tokentype::OBJECT);
      gen("OBJECT");
      after_object();
      break;
    default:
      syntaxerror2(saved_lexeme, saved_token);
  }
}


// Grammar: <after object> ::= <verb> #getEword# #gen(“ACTION”)# <tense> #gen(TENSE)# PERIOD |<noun> #getEword# DESTINATION #gen(“TO”)  <verb> #getEword# #gen(“ACTION”)#  <tense> #gen(“TENSE”)# PERIOD
// Done by: Dylan Kral
void after_object(){
  cout<<"Processing <after_object>"<<endl;
  switch(next_token()){
    case tokentype::WORD2:
      verb();
      getEword(saved_E_word);
      gen("ACTION");
      tense();
      gen("TENSE");
      match(tokentype::PERIOD);
      break;
    case tokentype::WORD1:
      noun();
      getEword(saved_E_word);
      match(tokentype::DESTINATION);
      gen("TO");
      verb();
      getEword(saved_E_word);
      gen("ACTION");
      tense();
      gen("TENSE");
      match(tokentype::PERIOD);
      break;
    case tokentype::PRONOUN:
      noun();
      getEword(saved_E_word);
      match(tokentype::DESTINATION);
      gen("TO");
      verb();
      getEword(saved_E_word);
      tense();
      gen("TENSE");
      match(tokentype::PERIOD);
      break;
    default:
      syntaxerror2(saved_lexeme, saved_token);
  }
}


// Grammar: <noun> ::= WORD1 | PRONOUN
// Done by: Dylan Kral
void noun(){
  cout<<"Processing <noun>"<<endl;
  switch(next_token()){
    case tokentype::WORD1:
      match(tokentype::WORD1);
      break;
    case tokentype::PRONOUN:
      match(tokentype::PRONOUN);
      break;
    default:
      syntaxerror2(saved_lexeme, saved_token);
  }
}

// Grammar: <verb> ::= WORD2
// Done by: Kyle Hawkins
void verb(){
  cout<<"Processing <verb>"<<endl;
  match(tokentype::WORD2);
  
}

// Grammar: <be> ::= IS | WAS
// Done by: Kyle Hawkins
void be(){
  cout<<"Processing <be>"<<endl;
  switch(next_token()){
    case tokentype::IS:
      match(tokentype::IS);
      break;
    case tokentype::WAS:
      match(tokentype::WAS);
      break;
    default:
      syntaxerror2(saved_lexeme, saved_token);
  }
}

// Grammar: <tense> := VERB_PAST  | VERB_PASTNEG | VERB | VERB_NEG
// Done by: Kyle Hawkins
void tense(){
  cout<<"Processing <tense>"<<endl;
  switch(next_token()){
    case tokentype::VERBPAST:
      match(tokentype::VERBPAST);
      break;
    case tokentype::VERBPASTNEG:
      match(tokentype::VERBPASTNEG);
      break;
    case tokentype::VERB:
      match(tokentype::VERB);
      break;
    case tokentype::VERBNEG:
      match(tokentype::VERBNEG);
      break;
    default:
      syntaxerror2(saved_lexeme, saved_token);
  }
}



/* INSTRUCTION:  copy your parser.cpp here
   cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/

//=================================================
// File translator.cpp written by Group Number: **
//=================================================

// ----- Additions to the parser.cpp ---------------------


map<string, string> dictionary;
// Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: ** 


// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result   
//                 in saved_E_word
//  Done by: Dylan Kral
bool getEword(string& save_E_word){
  if(dictionary.count(saved_lexeme)){
    saved_E_word = dictionary[saved_lexeme];
    return true;
  }
  else{
    saved_E_word = saved_lexeme;
    return false;
  }
}


//- using the line type,
// sends a line of an IR to translated.txt
// (saved_E_word or saved_token is used)
//  Done by: Ian Murphy
void gen(const string& line_type)
{
  if(line_type != "TENSE"){
    string output = line_type + ": " + saved_E_word;
    file << output << endl;  
  }
  else{
    string output = line_type + ": " + tokenName[saved_token];
    file << output << endl << endl;
  }
  
}                 

// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 

// ** Each non-terminal function should be calling
//    getEword and/or gen now.


// ---------------- Driver ---------------------------

// The final test driver to start the translator
// Done by:  Kyle Hawkins
int main()
{
  //** opens the lexicon.txt file and reads it into Lexicon
  //** closes lexicon.txt 

  //** opens the output file translated.txt
  string filename;
  string inFile;
  fstream infin;

  //Gets lexicon file name
  cout << "Enter the lexicon file name: ";
  cin >> filename;
  infin.open(filename.c_str());

  //Populating dictionary with values from lexicon.txt
  string japaneseWord;
  string englishWord;
  
  while(infin >> japaneseWord){
    infin >> englishWord;
    dictionary[japaneseWord] = englishWord;
  }
  infin.close();

  
  //Opens input file
  cout << "Enter the input file name: ";
  cin >> inFile;
  fin.open(inFile.c_str());

  //Call to story
  story();

  //Closes input and output files
  fin.close();
  
  //** calls the <story> to start parsing
  //** closes the input file 
  //** closes traslated.txt
 
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
