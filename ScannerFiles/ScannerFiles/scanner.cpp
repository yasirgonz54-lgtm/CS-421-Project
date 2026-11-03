#include<iostream>
#include<fstream>
#include<string>
#include<map>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 10 
//=====================================================

// --------- Two DFAs ---------------------------------

bool isvowel(char c)
{
  return (c=='a' || c=='e' || c=='i' || c=='o' || c=='u' ||
          c=='I' || c=='E');
}

bool isgroup_dwzyj(char c)
{
  return (c=='d' || c=='w' || c=='z' || c=='y' || c=='j');
}

bool isgroup_bghkmnpr(char c) //with n
{
  return (c=='b' || c=='g' || c=='h' || c=='k' || c=='m' ||
          c=='n' || c=='p' || c=='r');
}

bool isgroup_bghkmpr(char c) //without n
{
  return (c=='b' || c=='g' || c=='h' || c=='k' || c=='m' ||
          c=='p' || c=='r');
}

// WORD DFA 
// Done by: Carly Truong
bool word (string s)
{
  int state = 0;
  int charpos = 0;
  while (s[charpos] != '\0')
    {
      if (state == 0 && s[charpos] == 's') 
      {
        state = 1;
      }
      else if (state == 0 && s[charpos] == 't') 
      {
        state = 2;
      }
      else if (state == 0 && s[charpos] == 'c') 
      {
        state = 3;
      }
      else if (state == 0 && isgroup_dwzyj(s[charpos])) 
      {
        state = 4;
      }
      else if (state == 0 && isgroup_bghkmnpr(s[charpos])) 
      {
        state = 5;
      }
      else if (state == 0 && isvowel(s[charpos])) 
      {
        state = 6;
      }
      else if (state == 1 && isvowel(s[charpos])) 
      {
        state = 7;
      }
      else if (state == 1 && s[charpos] == 'h') 
      {
        state = 4;
      }
      else if (state == 2 && isvowel(s[charpos])) 
      {
        state = 7;
      }
      else if (state == 2 && s[charpos] == 's') 
      {
        state = 4;
      }
      else if (state == 3 && s[charpos] == 'h') 
      {
        state = 4;
      }
      else if (state == 4 && isvowel(s[charpos])) 
      {
        state = 7;
      }
      else if (state == 5 && isvowel(s[charpos])) 
      {
        state = 7;
      }
      else if (state == 5 && s[charpos] == 'y') 
      {
        state = 4;
      }
      else if (state == 6 && s[charpos] == 's') 
      {
        state = 1;
      }
      else if (state == 6 && isgroup_dwzyj(s[charpos])) 
      {
        state = 4;
      }
      else if (state == 6 && isgroup_bghkmpr(s[charpos])) 
      {
        state = 5;
      }
      else if (state == 6 && s[charpos] == 'c') 
      {
        state = 3;
      }
      else if (state == 6 && s[charpos] == 't') 
      {
        state = 2;
      }
      else if (state == 6 && s[charpos] == 'n') 
      {
        state = 8;
      }
      else if (state == 6 && isvowel(s[charpos])) 
      {
        state = 6;
      }
      else if (state == 7 && s[charpos] == 's') 
      {
        state = 1;
      }
      else if (state == 7 && s[charpos] == 't') 
      {
        state = 2;
      }
      else if (state == 7 && s[charpos] == 'c') 
      {
        state = 3;
      }
      else if (state == 7 && isgroup_dwzyj(s[charpos])) 
      {
        state = 4;
      }
      else if (state == 7 && isgroup_bghkmpr(s[charpos])) 
      {
        state = 5;
      }
      else if (state == 7 && s[charpos] == 'n') 
      {
        state = 8;
      }
      else if (state == 7 && isvowel(s[charpos])) 
      {
        state = 6;
      }
      else if (state == 8 && s[charpos] == 's') 
      {
        state = 1;
      }
      else if (state == 8 && s[charpos] == 't') 
      {
        state = 2;
      }
      else if (state == 8 && s[charpos] == 'c') 
      {
        state = 3;
      }
      else if (state == 8 && isgroup_dwzyj(s[charpos])) 
      {
        state = 4;
      }
      else if (state == 8 && isgroup_bghkmnpr(s[charpos])) 
      {
        state = 5;
      }
      else if (state == 8 && isvowel(s[charpos])) 
      {
        state = 7;
      }
      else 
      {
        return(false);
      }
      charpos++;
    }//end of while

  // where did I end up????
  if (state == 6 || state == 7 || state == 8)
    {
      return(true);  // end in a final state
    }
   else 
   {
     return(false);
   }
}

// PERIOD DFA 
// Done by: Carly Truong
bool period (string s)
{  
	int state = 0;
	int charpos = 0;
  while (s[charpos] != '\0')
    {
      if (state == 0 && s[charpos] == '.') 
      {
        state = 1;
      }
      else 
      {
        return(false);
      }
      charpos++;
    }//end of while

  if (state == 1)
    {
      return(true);  // end in a final state
    }
   else 
   {
     return(false);
   }
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Yasir Gonzalez

// ** Update the tokentype to be ERROR, WORD1, WORD2, PERIOD, EOFM, etc.
enum tokentype {ERROR,
  WORD1,
  WORD2,
  VERB,
  VERBNEG,
  VERBPAST,
  VERBPASTNEG,
  IS,
  WAS,
  OBJECT,
  SUBJECT, 
  DESTINATION,
  PRONOUN,
  CONNECTOR,
  PERIOD,
  EOFM};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {"ERROR", 
  "WORD1",
  "WORD2",
  "VERB",
  "VERBNEG",
  "VERBPAST",
  "VERBPASTNEG",
  "IS",
  "WAS",
  "OBJECT",
  "SUBJECT",
  "DESTINATION",
  "PRONOUN",
  "CONNECTOR",
  "PERIOD",
  "EOFM"
}; 

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** Your scanner should work without any additional files.

map<string, tokentype> reservedWords ={//hardcodded map for words
  {"masu", VERB},
  {"masen", VERBNEG},
  {"mashita", VERBPAST},
  {"masendeshita", VERBPASTNEG},
  {"desu", IS},
  {"deshita", WAS},
  {"o", OBJECT},
  {"wa", SUBJECT},
  {"ni", DESTINATION},
  {"watashi", PRONOUN},
  {"anata", PRONOUN},
  {"kare", PRONOUN},
  {"kanojo", PRONOUN},
  {"sore", PRONOUN},
  {"mata", CONNECTOR},
  {"soshite", CONNECTOR},
  {"shikashi", CONNECTOR},
  {"dakara", CONNECTOR}
};
// ------------ Scanner and Driver ----------------------- 


// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: 
void scanner(tokentype& tt, string& w)
{
  cin >> w;
  // 1. If it is eofm, return right now.   
  if (w == "eofm"){
    tt = EOFM;
    return;
  }
  /*  
  2. Call the token functions (word and period) 
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.
  */
  if (word(w)){
    if(reservedWords.find(w) != reservedWords.end()){
      tt = reservedWords[w];
    }
  /*
  3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.
*/
    else{
      char lastChar = w[w.length()-1];

      if(lastChar == 'I' || lastChar == 'E'){
        tt = WORD2;
      }
      else{
        tt = WORD1;
      }
    }
  }
/*
  4. Return the token type & string  (pass by reference)
  */
 else if(period(w)){//if PERIOD DFA accepts the string
  tt = PERIOD;
 }
 else{//String is not in neither DFA
  tt = ERROR;
  //cout << "Lexical error: " << w << endl;
 }
}//the end of scanner



// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
int main()
{
  tokentype thetype;
  string theword; 

  // the loop continues until eofm is returned.
   while (true)
    {
       scanner(thetype, theword);  // call the scanner which sets
                                   // the arguments  
       if (theword == "eofm") break;  // stop now

      cout << "Word: " << theword << " Type: " << tokenName[thetype]  << endl;
    }

}// end

