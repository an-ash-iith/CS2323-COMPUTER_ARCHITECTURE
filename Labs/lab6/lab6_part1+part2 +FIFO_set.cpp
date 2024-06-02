#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
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

string binarytohexadecimal(string s)
{
    string ans;
    ans="0x";
    int n= s.size();

    int full = n/4;
    int remainder= n%4;
    int digit=0;
    
    int count=1;
    int sign=0;

    if(remainder!=0)
    {
        for(int i=remainder-1;i>=0;i--)
        {
         digit= digit+ (s[i]-'0')*count;
         count=count*2;
        }

        sign=remainder;
        
        ans=ans+to_string(digit);
    }

  

    for (int i = sign; i <n ; i+=4)
    {
       		string str = s.substr(i,4);
		if (!str.compare("0000"))
		{
			ans = ans + "0";
		}
		else if (!str.compare("0001"))
		{
			ans = ans + "1";
		}
		else if (!str.compare("0010"))
		{
			ans = ans + "2";
		}
		else if (!str.compare("0011"))
		{
			ans = ans + "3";
		}
		else if (!str.compare("0100"))
		{
			ans = ans + "4";
		}
		else if (!str.compare("0101"))
		{
			ans = ans + "5";
		}
		else if (!str.compare("0110"))
		{
			ans = ans + "6";
		}
		else if (!str.compare("0111"))
		{
			ans = ans + "7";
		}
		else if (!str.compare("1000"))
		{
			ans = ans + "8";
		}
		else if (!str.compare("1001"))
		{
			ans = ans + "9";
		}
		else if (!str.compare("1010"))
		{
			ans = ans + "A";
		}
		else if (!str.compare("1011"))
		{
			ans = ans + "B";
		}
		else if (!str.compare("1100"))
		{
			ans = ans + "C";
		}
		else if (!str.compare("1101"))
		{
			ans = ans + "D";
		}
		else if (!str.compare("1110"))
		{
			ans = ans + "E";
		}
		else if (!str.compare("1111"))
		{
			ans = ans + "F";
		}
		else
		{
			continue;
		}
    }
   
    return ans;

}


bool check_tag(string s1 ,string s2)
{
    if(s1.size()!=s2.size())
    return false;

    else
    {
        for (int i = 0; i < s1.size(); i++)
        {
            if(s1[i]!=s2[i])
            {
                return false;
            }
        }

        return true;
        
    }
}


int main()
{

//taking config as input---Example config file:
// 32168
// 16
// 8
// LRU
//WT
ifstream f1("f1.txt");

    vector<string> input1;
    string temp1;
    if(f1.is_open()){

        while(getline(f1,temp1))
        {
           input1.push_back(temp1);
        }
        f1.close();
    }

for(auto it :input1)
 cout<<it<< endl;
   
int cache_size;
int block_size;
int associativity;

string replace_pol;
string write_pol;

cache_size = stoi(input1[0]);
block_size = stoi(input1[1]);
associativity= stoi(input1[2]);
replace_pol = input1[3];
write_pol  = input1[4];

   
    ifstream input("input.txt");
    vector<string>input2;
    string temp2;
    while (getline(input, temp2)) {
       input2.push_back(temp2);
    }

    for(auto it :input2)
     cout<<it<< endl;



// no of block will be cache size/block size

int no_block = cache_size/block_size;

int no_set= ceil(no_block/associativity);

int offset_bits=log2(block_size);

float index_bits= ceil(log2(no_set));  //ceil function because some input may not be multiple of 2 as in our first input
//but it will required as it exceeds the lower bound of index

int tag_bits= 32-(index_bits+offset_bits);





//******************part 1 + part 2 *******************//
//direct mapping -----**********note in direct mapping any policy have no effect 
if(associativity==1)
{
    cout<<"DIRECT MAP IN"<<endl;
//this is the cache we are making and it will take a string will store the tag bit of index
vector<string> my_cache(no_set,"nan"); 
int check_hit=-1;

int length1= input2.size();
 for (int j = 0; j < length1; j++)
 {


char mode = input2[j][0];

  string address ;

  for (int i = 5; i < 13; i++)
{
    // cout<<input2[0][i]<<" ";
   address= address + convert(input2[j][i]);
}

// cout<<input<<endl;
// cout<<address<<endl;

string offset=address.substr(32-offset_bits,offset_bits);
string index=address.substr(tag_bits,index_bits);
string tag=address.substr(0,tag_bits);

//cout<<" "<<tag<<" "<<index<<" "<<" "<<offset<<endl;

//lets change the index into a decimal format
int index_in_dec= binarytodecimal(index,0);

if(my_cache[index_in_dec]=="nan")
{
    // cout<<"miss"<<endl;
    check_hit=0;
    my_cache[index_in_dec]=tag;

}

else if(check_tag(tag,my_cache[index_in_dec])==true)
{
    // cout<<"hit"<<endl;
     check_hit=1;
}
else
{
cout<<",Miss ,"<<endl;
 check_hit=0;
my_cache[index_in_dec]=tag;
}


cout<<"Address: "<<binarytohexadecimal(address)<<", Set: "<<binarytohexadecimal(index);

if(check_hit==1)
cout<<" ,Hit, ";

else
cout<<" ,Miss, ";

cout<<"tag "<<binarytohexadecimal(tag);

cout<<endl;
 }
return 0;
}



//******************************FIFO SET ASDOCIATIVITY******************************//

if(replace_pol=="FIFO")
{

    cout<<"FIFO IN"<<endl;
queue<string> my_cache[no_set];



 for (int k = 0; k <no_set; k++)
 {
    for (int m = 0; m < associativity; m++)
    {
        
        my_cache[k].push("nan");
    }
   
 }
 

int check_hit=-1;
int length1= input2.size();



 for (int j = 0; j < length1; j++)
 {

char mode = input2[j][0];

  string address ;

  for (int i = 5; i < 13; i++)
{
    // cout<<input2[0][i]<<" ";
   address= address + convert(input2[j][i]);
}

// cout<<input<<endl;
// cout<<address<<endl;

string offset=address.substr(32-offset_bits,offset_bits);
string index=address.substr(tag_bits,index_bits);
string tag=address.substr(0,tag_bits);


int index_in_dec= binarytodecimal(index,0);

vector<string> reserve;

for (int t = 0; t < associativity; t++)
{
  if(check_tag(tag,my_cache[index_in_dec].front())==true)
{
    // cout<<"hit"<<endl;
     check_hit=1;
}

reserve.push_back(my_cache[index_in_dec].front());
my_cache[index_in_dec].pop();
}

for (int t = 0; t < associativity; t++)
{
  my_cache[index_in_dec].push(reserve[t]);
}

if(check_hit!=1)
{

// cout<<",Miss ,"<<endl;
 check_hit=0;
 my_cache[index_in_dec].push(tag);
 my_cache[index_in_dec].pop();
}

cout<<"Address: "<<binarytohexadecimal(address)<<", Set: "<<binarytohexadecimal(index);

if(check_hit==1)
cout<<" ,Hit, ";

else
cout<<" ,Miss, ";

cout<<"tag "<<binarytohexadecimal(tag);

cout<<endl;
 }

return 0;
}
 
return 0;
}