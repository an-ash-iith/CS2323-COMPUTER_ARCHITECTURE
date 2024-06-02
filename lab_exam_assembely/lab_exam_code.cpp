#include <iostream>
#include <bits/stdc++.h>

using namespace std;


string convert(char c)
{
    switch (c){

    case '0':
    return "0000";

    case '1':
    return "0001";

    case '2':
    return "0010";

    case '3':
    return "0011";

    case '4':
    return "0100";

    case '5':
    return "0101";

    case '6':
    return "0110";

    case '7':
    return "0111";
    
    case '8':
    return "1000";

    case '9':
    return "1001";

    case 'a':
    return "1010";

      case 'A':
    return "1010";

    case 'b':
    return "1011";

     case 'B':
    return "1011";

    case 'c':
    return "1100";

    case 'C':
    return "1100";

    case 'd':
    return "1101";

    case 'D':
    return "1101";

    case 'e':
    return "1110";

      case 'E':
    return "1110";

     case 'f':
    return "1111";

         case 'F':
    return "1111";

    }
    return "nan";
}


int binarytodecimal(string s,int sign)
{
  int n = s.size();

  int ans=0;

  int pos =1;

  if(s[0]=='0' || sign ==0 )
  {
  for (int i = n-1; i >=0; i--)
  {
    ans= ans+ (s[i]-'0')*pos;
    pos= pos*2;
  }
  }
  else
  {
  for (int i = n-1; i >0; i--)
  {
    ans= ans+ (s[i]-'0')*pos;
    pos= pos*2;
  }

  ans= ans - pos;
  }

  return ans;
}

int main()
{
    ifstream input("input.txt");

    vector<string> input1;
    string temp1;
    if(input.is_open()){

        while(getline(input,temp1))
        {
           input1.push_back(temp1);
        }
        input.close();
    }


// for (auto i: input1)
// {
//    cout<<i;
// }
// cout<<input1<<endl;
// cout<<endl;

//there may be multiple input in input.txt

string num1;
string num2;

bool sign1=0;
bool sign2=0;

int j=0;

for (int i = 0; i < input1[j].size(); i++)
{

    if(input1[j][i]==',')
    {
        sign1=true;
    }

    if(sign1==0)
    {
        num1=num1+input1[j][i];
    }

     if(sign2==1)
    {
        num2=num2+input1[j][i];
    }

        if(input1[j][i]==' ')
    {
        sign2=true;
    }
    
}

cout<<num1<<endl;
cout<<num2<<endl;

if(num1=="NAN" || num2=="nan" )
{
    cout<<num2<<endl;
    // break;
}

if(num2=="NAN" || num2=="nan")
{
    cout<<num1<<endl;
    // break;
}

  string num1_bin ;
  string num2_bin ;


  for (int i = 0; i < num1.size(); i++)
{
    // cout<<input2[0][i]<<" ";
   num1_bin= num1_bin + convert(num1[i]);
}

  for (int i = 0; i < num2.size(); i++)
{
    // cout<<input2[0][i]<<" ";
   num2_bin= num2_bin + convert(num2[i]);
}

cout<<num1_bin<<endl;
cout<<num2_bin<<endl;

char sign_num1= num1_bin[0];
string expp_num1=num1_bin.substr(1,8);
string frac_num1 = num1_bin.substr(8,23);

char sign_num2= num2_bin[0];
string expp_num2=num2_bin.substr(1,8);
string frac_num2 = num2_bin.substr(8,23);

cout<<expp_num1<<endl;
cout<<expp_num2<<endl;

int exp_num1=binarytodecimal(num1_bin.substr(1,8),0)-127;
// int frac_num1 =binarytodecimal(num2_bin.substr(8,23),0);

int exp_num2=binarytodecimal(num2_bin.substr(1,8),0)-127;
// int frac_num2 =binarytodecimal(num2_bin.substr(8,23),0);

cout<<exp_num1<<" "<<exp_num2<<endl;


int shifted=0;
if(exp_num1>exp_num2)
{
  shifted = exp_num1-exp_num2;

  if(shifted>23)
  {
    cout<<num1<<endl;
    //break
  }

string add1 =frac_num1.substr(shifted,23-shifted);
  for (int i = 0; i < shifted; i++)
  {
    add1='0'+add1;
  }
  



  
}
else
{
      if(shifted>23)
  {
    cout<<num2<<endl;
    //break
  }

shifted = exp_num2-exp_num1;

}


return 0;
}
