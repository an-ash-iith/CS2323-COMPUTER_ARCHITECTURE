#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// function return 0 if no hazard ..it will return 1 when 1 NOPE added (essentially NOPE will just be added before curent instruction)
// it will return 2 if two nopes add
bool isdig(char p)
{
  if(p>='0' && p<='9')
  return true;

  else
  return false;
}

int checkhazard(string s1, string s2, string s3)
{

  // initiate with value that is not a register number say -1
  int destination = -2;
  int src1 = -1;
  int src2 = -1;
  int i;
  int count = 3; // track record of register to be read

  // if(load instruction)

  if (s3[0] = 's' && s3[1] == 'd')
  {
    for (i = 0; i < s3.size(); i++)
    {
      if (s3[i] == 'x')
      {
        if (count == 3)
        {
           if(i<s3.size()-2 && isdig(s3[i+2]) )
        {
          src1= (s3[i+1]-'0')*10+(s3[i+2]-'0');
        }
        else
          src1 = s3[i + 1]-'0';
        }

        if (count == 2)
        { 
          if(i<s3.size()-2 && isdig(s3[i+2]) )
        {
          src2= (s3[i+1]-'0')*10+(s3[i+2]-'0');
        }
        else
          src2 = s3[i + 1]-'0';
        }
        count--;
      }
    }
  }

   else if (s3[0] == 'l' && s3[1] == 'd')
  {
    for (i = 0; i < s3.size(); i++)
    {
      if (s3[i] == 'x')
      {
        if (count == 2)
        { 
        if(i<s3.size()-2 && isdig(s3[i+2]) )
        {
          src1= (s3[i+1]-'0')*10+(s3[i+2]-'0');
        }
        else
          src1 = s3[i + 1]-'0';
          break;
        }
        
        count--;
      }
    }
  }
  // if (not load instruction)
  else
  {
    for (i = 0; i < s3.size(); i++)
    {
      if (s3[i] == 'x') // lower case x as naming of regisgter
      {
        if (count == 2)
        {
          if(i<s3.size()-2 && isdig(s3[i+2]) )
        {
          src1= (s3[i+1]-'0')*10+(s3[i+2]-'0');
        }
        else
          src1 = s3[i + 1]-'0';
        }

        if (count == 1)
        {
           if(i<s3.size()-2 && isdig(s3[i+2]) )
        {
          src2= (s3[i+1]-'0')*10+(s3[i+2]-'0');
        }
        else
          src2 = s3[i + 1]-'0';
        }
        count--;
      }
    }
  }


//checking for s2

  // sir told there is no dependence of sd to ld // so ld cant contribute to the destination

  // not sd indtruction

  if (s2[0] != 's' ||  s2[1] != 'd')
  {
    for (int i = 0; i < s2.size(); i++)
    {
      // if function is not store

      if (s2[i] == 'x') // lower case x as naming of regisgter
      {
         if(i<s2.size()-2 && isdig(s2[i+2]) )
        {
          destination= (s2[i+1]-'0')*10+(s2[i+2]-'0');
        }
        else
    
        destination = s2[i + 1]-'0';
        break;
      }
    }
  }

  if( destination == src1 || destination == src2)
  {
    return 1;
  }

  return 0;

}

int main()
{

  vector<string> inst;
  int i = 0;
  // int b;
  string str;
  int cycle=0;

cout<<"Enter the number of instruction"<<endl;
  int inst_num;
  cin>>inst_num;

  //  while(scanf(%d,b)!==1)
 
  for(i=0;i<inst_num;i++)
  {
    getline(cin, str);

    inst.push_back(str);

  }

  int n = inst.size();

  string s1, s2, s3;

  s1 = "nop";
  s2 = inst[0];

  cout << s2 << endl;
  cycle= cycle+1;

  for (int i = 1; i < n; i++)
  {

    s3 = inst[i];
    // with forwarding

    //only chances to add nops is when previous instruction is ld because there will be nothing of other memory instruction sd
    //rest will lead to no NOPS either forwarding or not
    if(s2[0]!='l' || s2[1]!='d')
    {
      s1 = s2;
      s2 = s3;
      cout<<s3<<endl;
      cycle=cycle+1;
      continue;
    }

    if (checkhazard(s1, s2, s3) == 1)
    {
      cout << "nop" << endl << s3 << endl;
      s1 = "";
      s2 = s3;
      cycle=cycle+2;
    }

    else
    {
      s1 = s2;
      s2 = s3;
      cout<<s3<<endl;
      cycle=cycle+1;
    }
  }
  cout<<cycle+4 <<" cycles"<<endl;

  return 0;
}
