#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <queue>
using namespace std;

//valid bit is necessary as we will check the tag and if tag matches then valid bit is 1 and thus we process the data
//else we will make our valid bit as 0 then take the address and load one block from memory and update its tag bit
//when you will load 
//dirty bit is necessary for writing in the memory or not when we update the data in cache then we make the dirty bit as 1
//and thus we have to update to the memory
//in write back policy when the block replaced then data is updated in the memory.

//in fifo policy you have to store time counter for each address in block
//in LRU this first decide the minimum counter of the memory and then replace any of the minimum counter as random is there thus uses combined LRU + RANDOM

//first implement for read in tcode then implement for write in the code and later combine both as there implementation are independent from each other

//read should be iimplemented on FIFO policy it means a time stamp is needed for each block in the "set"

//if its associativity is 1 then no replacement policy will be there.

// here you not need to store the data for cache implementation as (offset + index+ tag + valid bit) for the given block --if this address found then then hit else replace 
//the tag bit and change valid bit to 1 rest thing will be same 

//valid bit will be 0 always when any block haven been initialized else 1

//remeber 32 bit address is there 
//binary implementaion should be done for the given hex and then at last again output should be in hex so binarytohex and ehxto binary function should be there

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

float index_bits= ceil(log2(no_set));  
int tag_bits= 32-(index_bits+offset_bits);

//  vector<queue<string>> input2(no_set);

if(replace_pol=="LRU")
{
  cout<<"LRU"<<endl;
vector<string> my_cache[no_set];


 for (int k = 0; k <no_set; k++)
 {
    for (int m = 0; m < associativity; m++)
    {
        
        my_cache[k].push_back("nan");
    }
   
 }
 


int length1= input2.size();
int rescent_index[no_set];

for (int i = 0; i < no_set; i++)
{
    rescent_index[i] =-1;
}


 for (int j = 0; j < length1; j++)
 {

int check_hit=-1;
char mode = input2[j][0];

  string address ;

  for (int g = 5; g < 13; g++)
{
    // cout<<input2[0][i]<<" ";
   address= address + convert(input2[j][g]);
}

// cout<<input<<endl;
// cout<<address<<endl;

string offset=address.substr(32-offset_bits,offset_bits);
string index=address.substr(tag_bits,index_bits);
string tag=address.substr(0,tag_bits);


int index_in_dec= binarytodecimal(index,0);

for (int t = 0; t < associativity; t++)
{

if(check_tag(tag,my_cache[index_in_dec][t])==true)
{
    // cout<<"hit"<<endl;
     check_hit=1;
     rescent_index[index_in_dec] = t;
     break;
}
  
}


if(check_hit!=1)
{

// cout<<",Miss ,"<<endl;
 my_cache[index_in_dec].erase(my_cache[index_in_dec].begin() + rescent_index[index_in_dec]);
 my_cache[index_in_dec].push_back(tag);
rescent_index[index_in_dec]= associativity-1;
check_hit=0;
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