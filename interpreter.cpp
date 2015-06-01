#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

#define T "T"
#define NIL "NIL"
#define CAR "CAR"
#define CDR "CDR"
#define CONS "CONS"
#define ATOM "ATOM"
#define EQ "EQ"

#undef _NULL
#define _NULL "NULL"

#define INT "INT"
#define PLUS "PLUS"
#define MINUS "MINUS"
#define TIMES "TIMES"
#define QUOTIENT "QUOTIENT"
#define REMAINDER "REMAINDER"
#define LESS "LESS"
#define GREATER "GREATER"
#define COND "COND"
#define QUOTE "QUOTE"
#define DEFUN "DEFUN"
#define TYPE_INT 1
#define TYPE_VAR 2
#define TYPE_SEXP 3
#define TYPE_ERROR 4



class S_EXP;

void destroy_S_EXP(S_EXP *sExpr);
S_EXP* apply(string f, S_EXP *sExpr, vector <S_EXP *> &aList);
bool CHECK_LENGTHS(S_EXP *sExpr1, S_EXP *sExpr2);
bool CHECK_Alist(string name, vector<S_EXP *> &aList, int &index);
bool CHECK_Dlist(string name, int &index);
S_EXP* RETURN_Dlist(string name);
void addPair(S_EXP *fpList, S_EXP *apList, vector <S_EXP *> &aList);
S_EXP* evlis(S_EXP *sExprList, vector<S_EXP *> &aList);
S_EXP* evcon(S_EXP *be, vector <S_EXP *> &aList);
S_EXP* eval(S_EXP *sExpr, vector <S_EXP *> &aList);
void create_tokens(string inputStr, vector<string> &expToken);
bool CHECK_Number(string str, int &value);
bool validateInputstring(string &s);
void myinterpreter(string input_str,char* outputfile);

class S_EXP
{
private:
 S_EXP *car, *cdr;
 int  type;
 int  intvalue;
 string strvalue;

public:

 S_EXP()
 {
  car = cdr = NULL;
  type = TYPE_SEXP;
  intvalue = 0;
  strvalue = "";
 }


 S_EXP(int n)
 {
  car = cdr = NULL;
  type = TYPE_INT;
  intvalue = n;
  strvalue = "";
 }


 S_EXP(const S_EXP &s)
 {
  if(s.car != NULL)
   car = s.car;
  if(s.cdr != NULL)
   cdr = s.cdr;
  intvalue = s.intvalue;
  strvalue = s.strvalue;
  type = s.type;
 }

 S_EXP(string s,int typ = TYPE_VAR)
 {
  car = cdr = NULL;
  type = typ;
  intvalue = 0;
  strvalue = s;
 }

 string getstrvalue()
 {
  return strvalue;
 }

 int getintvalue()
 {
  return intvalue;
 }

 int getType()
 {
  return type;
 }

 S_EXP error()
 {
  return S_EXP("Error");
 }

 bool CHECK_NIL()
 {
  return strvalue == NIL ? true: false;
 }

 S_EXP* RETURN_CAR()
 {
  return car;
 }

 S_EXP* RETURN_CDR()
 {
  return cdr;
 }

 void CONSTRUCT(S_EXP *s1, S_EXP *s2)
 {
  car = s1;
  cdr = s2;
  type = TYPE_SEXP;
  intvalue = 0;
  strvalue = "";
 }

 S_EXP RETURN_ATOM()
 {
  return (type == TYPE_INT || type == TYPE_VAR) ? S_EXP(T):S_EXP(NIL);
 }

 S_EXP eq(S_EXP *s1, S_EXP *s2)
 {
  if((!s1->RETURN_ATOM().CHECK_NIL()) && (!s2->RETURN_ATOM().CHECK_NIL())){
   if (  (s1->type == TYPE_VAR && s2->type == TYPE_VAR && s1->strvalue == s2->strvalue) ||
      (s1->type == TYPE_INT && s2->type == TYPE_INT && s1->intvalue == s2->intvalue))
    strvalue = T;
  else
    strvalue = NIL;
  }
  type = TYPE_VAR;
  return *this;
 }

 S_EXP CHECK_NULL()
 {
  return (strvalue == NIL) ? S_EXP(T):S_EXP(NIL);
 }

 S_EXP CHECK_INT()
 {
  return (type == TYPE_INT) ? S_EXP(T):S_EXP(NIL);
 }

 void RETURN_PLUS(S_EXP *s1, S_EXP *s2)
 {
  if(!s1->CHECK_INT().CHECK_NIL() && !s2->CHECK_INT().CHECK_NIL())
  {
   type = TYPE_INT;
   intvalue = s1->intvalue + s2->intvalue;
  }
  else
  {
   type = TYPE_VAR;
   strvalue = NIL;
  }
 }

 void RETURN_MINUS(S_EXP *s1, S_EXP *s2)
 {
  if(!s1->CHECK_INT().CHECK_NIL() && !s2->CHECK_INT().CHECK_NIL())
  {
   type = TYPE_INT;
   intvalue = s1->intvalue - s2->intvalue ;
  }
  else
  {
   type = TYPE_VAR;
   strvalue = NIL;
  }
 }

 void MULTIPLY(S_EXP *s1, S_EXP *s2)
 {
  if(!s1->CHECK_INT().CHECK_NIL() && !s2->CHECK_INT().CHECK_NIL())
  {
   intvalue = s1->intvalue * s2->intvalue ;
   type = TYPE_INT;
  }
  else
  {
   type = TYPE_VAR;
   strvalue = NIL;
  }
 }

 void RETURN_QUOTIENT(S_EXP *s1, S_EXP *s2)
 {
  if(!s1->CHECK_INT().CHECK_NIL() && !s2->CHECK_INT().CHECK_NIL() && s2->intvalue != 0)
  {
   type = TYPE_INT;
   intvalue = s1->intvalue / s2->intvalue ;
  }
  else
  {
   type = TYPE_VAR;
   strvalue = NIL;
  }
 }

 void RETURN_REMAINDER(S_EXP *s1, S_EXP *s2)
 {
  if(!s1->CHECK_INT().CHECK_NIL() && !s2->CHECK_INT().CHECK_NIL() && s2->intvalue != 0)
  {
   intvalue = s1->intvalue % s2->intvalue ;
   type = TYPE_INT;
  }
  else
  {
   strvalue = NIL;
   type = TYPE_VAR;
  }
 }

 void RETURN_LESS(S_EXP *s1, S_EXP *s2)
 {
  if(!s1->CHECK_INT().CHECK_NIL() && !s2->CHECK_INT().CHECK_NIL() && s1->intvalue < s2->intvalue)
   strvalue = T;
  else
   strvalue = NIL;

  type = TYPE_VAR;
 }

 void RETURN_GREATER(S_EXP *s1, S_EXP *s2)
 {
  if(!s1->CHECK_INT().CHECK_NIL() && !s2->CHECK_INT().CHECK_NIL() && s1->intvalue > s2->intvalue)
   strvalue = T;
  else
   strvalue = NIL;

  type = TYPE_VAR;
 }

 S_EXP CHECK_LIST()
 {
  if(!RETURN_ATOM().CHECK_NIL())
   return S_EXP(NIL);
  else if(CHECK_NIL())
   return S_EXP(T);
  else
   return cdr->CHECK_LIST();
 }

 S_EXP& operator=(const S_EXP &s)
 {
  if(s.car != NULL)
   car = s.car;
  if(s.cdr != NULL)
   cdr = s.cdr;
  intvalue = s.intvalue;
  strvalue = s.strvalue;
  type = s.type;
  return *this;
 }


 bool buildS_EXPObjStack(vector<S_EXP *> &sExprStack)
 {
  S_EXP *s_temp = NULL, *s = NULL,*s1 = NULL, *t[3]={NULL,NULL,NULL};
  int i = 0;
  bool blankspace = false;

  while(sExprStack.size() >= 1)
  {
   t[i] = sExprStack.back();

   sExprStack.pop_back();

   if(i == 0 && t[i]->strvalue == "(")
   { s = new S_EXP(NIL);
    sExprStack.push_back(s);
    delete t[0];
    break;
   }
   else if(i == 1 && t[i]->strvalue == "(")
   {  s = new S_EXP(NIL);
     s_temp = new S_EXP();
     s_temp->CONSTRUCT(t[0],s);
     sExprStack.push_back(s_temp);
     delete t[1];
     break;
   }
   else if(i ==2 && t[i]->strvalue == "(")
   {
    delete t[0];
    delete t[1];
    delete t[2];
    return false;
   }

   if(i % 3 == 2)
   { if( t[1]->strvalue == " " && !blankspace)
    {
      blankspace = true;
      s = new S_EXP(NIL);
      s1 = new S_EXP();
      s1->CONSTRUCT(t[0],s);
    }
    else if(t[1]->strvalue==".")
    { if ( sExprStack.size() >= 1 && sExprStack.back()->strvalue != "(")
      return false;
     s1 = t[0];
    }
    else if(blankspace)
     s1 = t[0];

    delete t[1];
    s_temp = new S_EXP();
    s_temp->CONSTRUCT(t[2],s1);
    if (sExprStack.size() >= 1 && sExprStack.back()->strvalue == "(")
    { sExprStack.pop_back();
     sExprStack.push_back(s_temp);
     break;
    }
    else
     sExprStack.push_back(s_temp);

   }

   i = (i+1)%3;
   if (i % 3 == 0)
    memset(t,0,3);
  }

  return true;
 }


 bool input(vector<string> varTokens)
 {
  vector<S_EXP *> expstack;
  S_EXP *temp1 = NULL;
  int value =0;
  bool token_error = false;
  for(unsigned int i=0; i < varTokens.size(); i++)
  {
   if(varTokens[i] == ")")
   {
    if(!buildS_EXPObjStack(expstack))
    {
     token_error = true;
     break;
    }
   }
   else
   {
    if(CHECK_Number(varTokens[i],value))
     temp1 = new S_EXP(value);
    else
     temp1 = new S_EXP(varTokens[i]);

    expstack.push_back(temp1);
   }
   if(token_error)
    break;
  }
  *this = (!token_error) && (expstack.size() > 0) ? *expstack.back(): error();
  return token_error;
 }


 void output(string &outputStr)
 {
  if((type == TYPE_VAR) || (type == TYPE_ERROR))
   outputStr = strvalue;
  else if(type == TYPE_INT)
  {
   char buf[10];
   sprintf(buf,"%d",intvalue);
   outputStr = buf;
  }
  else
  {
   outputStr = "(";
   string s1, s2;
   car->output(s1);
   outputStr += s1 + ".";
   cdr->output(s2);
   outputStr += s2 + ")";
  }
 }
};

vector<S_EXP *> dList;
S_EXP t(T);
S_EXP nil(NIL);

void destroy_S_EXP(S_EXP *sExpr)
{
 if (sExpr->getType() == TYPE_SEXP)
 {
  destroy_S_EXP(sExpr->RETURN_CAR());
  destroy_S_EXP(sExpr->RETURN_CDR());
  delete sExpr;
 }
 else
  delete sExpr;
}

bool CHECK_LENGTHS(S_EXP *sExpr1, S_EXP *sExpr2)
{
 if(sExpr1->CHECK_NIL())
  return (sExpr2->CHECK_NIL()) ? true : false;
 else
  return (sExpr2->CHECK_NIL()) ? false : CHECK_LENGTHS(sExpr1->RETURN_CDR(),sExpr2->RETURN_CDR());
 }

bool CHECK_Alist(string name, vector<S_EXP *> &aList, int &index)
{
 unsigned int l = aList.size();
 for(unsigned int i=0;i<l;i++)
 {
  if (aList[i]->RETURN_CAR()->getstrvalue() == name)
  {
   index =  i;
   return true;
  }
 }
 return false;
}

bool CHECK_Dlist(string name, int &index)
{

 for (unsigned int i = 0 ; i < dList.size(); i++)
 {
  if (dList[i]->RETURN_CAR()->getstrvalue() == name)
  {
   index = i;
   return true;
  }
 }
 return false;
}

S_EXP* RETURN_Dlist(string name)
{
 int index = -1;
 if(CHECK_Dlist(name, index))
  return dList[index]->RETURN_CDR();
 else
  return &nil;
}

void addPair(S_EXP *fpList, S_EXP *apList, vector<S_EXP *> &aList)
{
 if( fpList != NULL && apList != NULL &&
     fpList->getType() == TYPE_SEXP  &&
  apList->getType() == TYPE_SEXP )
 {

  while(!fpList->CHECK_NIL() && !apList->CHECK_NIL())
  {
   S_EXP *a = new S_EXP(*fpList->RETURN_CAR());
   S_EXP *d = new S_EXP(*apList->RETURN_CAR());
   S_EXP *tp = new S_EXP();
   tp->CONSTRUCT(a, d);
   aList.push_back(tp);
   fpList = fpList->RETURN_CDR();
   apList = apList->RETURN_CDR();
  }
 }
}


S_EXP* apply(string f, S_EXP *sExpr, vector <S_EXP *> &aList)
{
 S_EXP *sOut = NULL;

 if(sExpr->getType() == TYPE_ERROR)
  sOut = sExpr;
 else
 {
  if(sExpr->getType() != TYPE_SEXP)
  { sOut = new S_EXP("Invalid list of parameters",TYPE_ERROR);
   return sOut;
  }

  if(f == CAR)    sOut =  sExpr->RETURN_CAR()->RETURN_CAR();
  else if(f == CDR)  sOut =  sExpr->RETURN_CAR()->RETURN_CDR();
  else if(f == ATOM)     sOut =  new S_EXP(sExpr->RETURN_CAR()->RETURN_ATOM());
  else if(f == _NULL)  sOut =  new S_EXP(sExpr->RETURN_CAR()->CHECK_NULL());
  else if(f == INT)  sOut =  new S_EXP(sExpr->RETURN_CAR()->CHECK_INT());
  else if(f.length() > 0)
  {
   if( (f == EQ) || (f == LESS) ||(f == GREATER)|| (f == CONS) ||
    (f == PLUS)|| (f == MINUS)||(f == TIMES)||(f == QUOTIENT)||(f == REMAINDER))
   {
    if(sExpr->RETURN_CDR()->RETURN_CDR()->CHECK_NIL())
    {
     sOut = new S_EXP();
     if(f == EQ)     sOut->eq(sExpr->RETURN_CAR(), sExpr->RETURN_CDR()->RETURN_CAR());
     else if(f == LESS)   sOut->RETURN_LESS(sExpr->RETURN_CAR(), sExpr->RETURN_CDR()->RETURN_CAR());
     else if(f == GREATER)  sOut->RETURN_GREATER(sExpr->RETURN_CAR(), sExpr->RETURN_CDR()->RETURN_CAR());
     else if(f == PLUS)   sOut->RETURN_PLUS(sExpr->RETURN_CAR(), sExpr->RETURN_CDR()->RETURN_CAR());
     else if(f == MINUS)   sOut->RETURN_MINUS(sExpr->RETURN_CAR(), sExpr->RETURN_CDR()->RETURN_CAR());
     else if(f == TIMES)   sOut->MULTIPLY(sExpr->RETURN_CAR(), sExpr->RETURN_CDR()->RETURN_CAR());
     else if(f == QUOTIENT)  sOut->RETURN_QUOTIENT(sExpr->RETURN_CAR(), sExpr->RETURN_CDR()->RETURN_CAR());
     else if(f == REMAINDER)  sOut->RETURN_REMAINDER(sExpr->RETURN_CAR(), sExpr->RETURN_CDR()->RETURN_CAR());
     else if(f == CONS)   sOut->CONSTRUCT(sExpr->RETURN_CAR(), sExpr->RETURN_CDR()->RETURN_CAR());
    }
    else
     sOut = new S_EXP("Invalid Number of Arguments",TYPE_ERROR);
   }
   else
   {
    S_EXP *fb = RETURN_Dlist(f);
    if(fb!= NULL && !fb->CHECK_NIL())
    {
     if(CHECK_LENGTHS(fb->RETURN_CAR(),sExpr))
     {
      addPair(fb->RETURN_CAR(), sExpr, aList);
      S_EXP *t = eval(fb->RETURN_CDR()->RETURN_CAR(),aList);
      sOut =  new S_EXP(*t);
      destroy_S_EXP(t);
     }
     else
      sOut = new S_EXP("Invalid Number of Arguments",TYPE_ERROR);
    }
    else
      sOut = new S_EXP("Invalid function body",TYPE_ERROR);
   }
  }
  else
   sOut = new S_EXP("Invalid Function Name", TYPE_ERROR);
 }

 return sOut;
}


S_EXP* evlis(S_EXP *sExprList, vector<S_EXP *> &aList)
{
 S_EXP *sExpr = NULL;

 if(sExprList == NULL)
  sExpr = new S_EXP("Invalid List of Arguments",TYPE_ERROR);
 else if (!sExprList->RETURN_ATOM().CHECK_NIL())
  sExpr = sExprList;
 else
 {
   sExpr = new S_EXP();

   S_EXP *a = new S_EXP(*eval(sExprList->RETURN_CAR(),aList));
   if(a != NULL && a->getType() == TYPE_ERROR)
     return a;

   S_EXP *d = NULL;
  if(!sExprList->RETURN_CDR()->CHECK_NIL())
   {
    d = new S_EXP(*evlis(sExprList->RETURN_CDR(),aList));
    if(d !=NULL && d->getType() == TYPE_ERROR)
     return d;
   }
   else
    d = new S_EXP(NIL);

   sExpr->CONSTRUCT(a,d);
 }
 return sExpr;
}


S_EXP* evcon(S_EXP *be, vector <S_EXP *> &aList)
{
 if(be->CHECK_NIL())
  return be;
 else if(!eval(be->RETURN_CAR()->RETURN_CAR(),aList)->CHECK_NIL() )
  return eval(be->RETURN_CAR()->RETURN_CDR()->RETURN_CAR(),aList);
 else
  return evcon(be->RETURN_CDR(), aList);
}


S_EXP* eval(S_EXP *sExpr, vector<S_EXP *> &aList)
{
  string fName;
  S_EXP *sExprOut = NULL;
  int found = -1;

  if (sExpr== NULL)
   sExprOut = new S_EXP("Invalid s-expression", TYPE_ERROR);
  else if(sExpr->CHECK_NIL())
   sExprOut = sExpr;
  else if(!sExpr->RETURN_ATOM().CHECK_NIL())
  {
   if (!sExpr->CHECK_INT().CHECK_NIL() || sExpr->getstrvalue() == T || sExpr->getstrvalue() == NIL)
    sExprOut = sExpr;
   else if (CHECK_Alist(sExpr->getstrvalue(), aList, found))
    sExprOut = new S_EXP(*aList[found]->RETURN_CDR());
   else
    sExprOut = new S_EXP("Unbound Identifier", TYPE_ERROR);

  }
  else if(!sExpr->RETURN_CAR()->RETURN_ATOM().CHECK_NIL())
  {
   fName =  sExpr->RETURN_CAR()->getstrvalue();
   if( fName == "")
    sExprOut = new S_EXP("Invalid Input", TYPE_ERROR);
   else if(fName == "DEFUN")
   {
    int index = -1;
    if(CHECK_Dlist(sExpr->RETURN_CDR()->RETURN_CAR()->getstrvalue(), index))
      sExprOut = new S_EXP("Function Redefined", TYPE_ERROR);
    else
    {
     S_EXP *temp = new S_EXP(*sExpr->RETURN_CDR());
     dList.push_back(temp);
     sExprOut = new S_EXP(sExpr->RETURN_CDR()->RETURN_CAR()->getstrvalue());
    }
   }
   else if(fName == "COND")
   {
    S_EXP *temp = evcon(sExpr->RETURN_CDR(),aList);
    sExprOut =  new S_EXP(*temp);
    destroy_S_EXP(temp);
   }
   else if(fName == "QUOTE")
   {
    sExprOut =  new S_EXP(*sExpr->RETURN_CDR()->RETURN_CAR());
   }
   else
   {
    if(fName == "ATOM")
    {
     if(sExpr->RETURN_CDR()->RETURN_CDR()->RETURN_ATOM().getstrvalue() == "NIL")
      sExprOut = new S_EXP("Invalid input", TYPE_ERROR);
     else{
     S_EXP *temp  = evlis(sExpr->RETURN_CDR(),aList);
     S_EXP *temp1 = apply(fName, temp, aList);
     sExprOut = new S_EXP(*temp1);}
      return sExprOut;
    }
    S_EXP *temp  = evlis(sExpr->RETURN_CDR(),aList);
    if(temp->getType() == TYPE_ERROR)
     sExprOut =  new S_EXP(*temp);
    else
    {
     S_EXP *temp1 = apply(fName, temp, aList);
     sExprOut =  new S_EXP(*temp1);
    }
   }
  }
  else
   sExprOut = new S_EXP("Invalid Input", TYPE_ERROR);

  return sExprOut;
}


void create_tokens(string inputStr, vector<string> &expToken)
{
  int l = inputStr.length();
  for(int i = 0; i < l; i++)
  {
   string temp = " ";
   if(inputStr[i] == '(' || inputStr[i] == ')' || inputStr[i] == '.')
   {
    if((inputStr[i] ==  ')' || inputStr[i] ==  '.') && (expToken.size() > 0 && expToken.back() == " "))
     expToken.pop_back();

    if((inputStr[i] ==  ')' || inputStr[i] ==  '.') && (expToken.size() > 0 && expToken.back() == "."))
    {
     expToken.push_back("Invalid");
     break;
    }

    temp[0] = inputStr[i];
    expToken.push_back(temp);

    if((inputStr[i] ==  '(' || inputStr[i] ==  '.') && inputStr[i+1] == ' ')
    {
     i++;
     while(inputStr[i] ==  ' ')
      i++;
      i--;
    }
   }
   else if(inputStr[i] == ' ')
   {
    temp[0] = inputStr[i];
    expToken.push_back(temp);
    while(inputStr[i] ==  ' ') i++;
    i--;
   }
   else if((inputStr[i] >= 'A' && inputStr[i] <= 'Z') || (inputStr[i] >= '0' && inputStr[i] <= '9') || inputStr[i] == '-' || inputStr[i] == '+')
   {
    int k = 1;
    temp[0] = inputStr[i++];
    while (i < l && ((inputStr[i] >= 'A' && inputStr[i] <= 'Z') || (inputStr[i] >= '0' && inputStr[i] <= '9')))
    {
     if (( temp[0] >= '0' && temp[0] <= '9' ) || temp [0] == '-' || temp[0] == '+')
     {
      if (inputStr[i] >= 'A' && inputStr[i] <= 'Z')
      {
        expToken.push_back("Invalid");
        break;
      }
     }
     temp.push_back(inputStr[i++]);
     k++;
     if(k > 10)
        {
      expToken.push_back("Invalid");
      break;
     }
      }
    i--;
    if(expToken.size() > 0 && expToken.back() == "Invalid")
     break;
    expToken.push_back(temp);
   }
   else
   {
     expToken.push_back("Invalid");
    break;
   }
  }

  if(expToken.back() != "Invalid")
    expToken.push_back("Valid");
}

bool CHECK_Number(string str, int &value)
{
  bool bNeg = false;
  bool bpos = false;
  unsigned int i;
  unsigned int len = str.size();
  value = 0;
  for (i=0; i<len; i++)
  {
       if(i == 0 && str[0] == '-')
    {
     bNeg = true;
     continue;
    }
    if(i == 0 && str[0] == '+')
    {
     bpos = true;
     continue;
    }
    if(!(str[i] >= '0' && str[i] <= '9'))
     return false;
    else
     value = value*10 + (str[i] - '0');
  }

  if(bNeg)
   value *= -1;
  else if(bpos)
   value *= 1;

  return true;
}


bool validateInputstring(string &inputStr)
{
  int l = inputStr.length();
  int paranthesescount = 0;
  int flag = 0;
  int x;
  for(int i = 0; i < l; i++)
  {
   if(inputStr[i] == '(')
   {
    paranthesescount++;
    flag = 1;
   }
   else if(inputStr[i] == ')')
    paranthesescount--;

   if((inputStr[i] == '\n') || (inputStr[i] == '\t') || (inputStr[i] == '\r'))
    inputStr[i] = ' ';

   if((inputStr[i] == '.') && (flag == 0))
    return false;

   x = i + 1;
   if((inputStr[i] >= 'A' && inputStr[i] <= 'Z') || (inputStr[i] >= '0' && inputStr[i] <= '9'))
   {
    if(inputStr[x] == ' ')
    {
     while(inputStr[x] == ' ')
     {
      x++;
     }
     if((inputStr[x] >= 'A' && inputStr[x] <= 'Z') || (inputStr[x] >= '0' && inputStr[x] <= '9'))
     {
      if(flag == 0)
       return false;
     }
    }
   }

   if(!(inputStr[i] >= 'A' && inputStr[i] <= 'Z') && !(inputStr[i] >= '0' && inputStr[i] <= '9') && (inputStr[i] != '.') && (inputStr[i] != '(') && (inputStr[i] != ')') && (inputStr[i] != ' ') && (inputStr[i] != '-') && (inputStr[i] != '+'))
     return false;
  }
  if(paranthesescount != 0)
   return false;
  while(inputStr[l-1] == ' ')
  {
   inputStr.erase(l-1);
   l--;
  }
  return true;
}

void myinterpreter(string input_str,char* x_file){

  //vector<string> inputString = inputstring;
  string outputString;
  vector<string> variableTokens;
  S_EXP *sExpr,*sExprEval;
  char *outputfile = x_file;
  ofstream writefile(outputfile,ios::app);

  vector<S_EXP*> aList;


  if(validateInputstring(input_str))
  {
   create_tokens(input_str, variableTokens);
   if(variableTokens.back() == "Invalid")
   {
    cout << "\n Error: The input is invalid \n\n";
   }
   else
   {
    variableTokens.pop_back();
    sExpr = new S_EXP();
    if(!sExpr->input(variableTokens))
    {
     sExpr->output(outputString);
     if(outputString != "Error")
     {
      cout << "\n\nInput lisp S-Expression in dotted notation:\n" << outputString;
      sExprEval = eval(sExpr, aList);
      sExprEval->output(outputString);
      if(sExprEval->getType() != TYPE_ERROR)
       cout << "\n\nThe Evaluated S-Expression  in dotted notation is:\n" << outputString<<"\n";
      else
      {
       cout << "\n\nError: " << outputString;
      }
     }
     else
     {
      cout << "\nError: The input is invalid \n\n";
     }
    }
    else
    {
     cout << "\nError: The input is invalid \n\n";
    }
   }
  }
  else
  {
   cout << "\nError: The input is invalid \n\n";
  }

  input_str.clear();
  aList.clear();
  variableTokens.clear();

 if (writefile.is_open())
   {
   writefile << outputString;
   }
 else
   {
     cout << "Unable to open writing file ";

   }

}


int main(int argc, char* argv[])
{

string line,outputString,input_str;
//vector<string> inputString;
char* xfile;
ifstream myfile (argv[1]);
xfile = argv[2];
char c;


  if (!myfile.is_open())
    {
      cout << "Unable to open read file";
    }
  else
    {
    while ( getline (myfile,line) )
      {
        //cout<<line;
        for(int i=0;i<line.size();i++){
          c = toupper(line[i]);

          input_str.push_back(c);
          if(c == 59 ){

            input_str.erase(input_str.length()-1,1);
            myinterpreter(input_str,xfile);
            }
      }
    }
    myfile.close();
}
}
