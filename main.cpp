#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void distboard(int value)
{
    int valleft=value;
    string vals[9];
    for(int n=8;n>=0;n--) //The space on the board
    {
        bool found = false;
        if(valleft>0) //Some optomizatio nif it has already found all of the values
        {
            for(int nn=2;nn>0;nn--) //Checking multipliers for base 3
            {
                if(valleft >=nn*pow(3,n))
                {
                    if(nn==1)
                    {
                        vals[n]="X";
                    }
                    if(nn==2)
                    {
                        vals[n]="O";
                    }
                    found=true;
                    valleft = valleft - nn*pow(3,n);
                }
            }
        }
        if(found==false)
        {
            vals[n]=" "; //Adding in space if nothing is found
        }
    }
    cout << "[" << vals[0] << " " << vals[1] << " " << vals[2] << "]" << endl;
    cout << "[" << vals[3] << " " << vals[4] << " " << vals[5] << "]" << endl;
    cout << "[" << vals[6] << " " << vals[7] << " " << vals[8] << "]" << endl;
    return;
}
void explode(string& str, int index,double probs[][9])
{
    string delimiter = ",";
    int strleng = str.length();
    int delleng = delimiter.length();
    int i=0;
    int k=0;
    int numfound=0;
    while( i<strleng )
    {
        int j=0;
        while (i+j<strleng && j<delleng && str[i+j]==delimiter[j])
            j++;
        if (j==delleng)//found delimiter
        {
            stringstream ss;
            ss << str.substr(k, i-k);
            double output;
            ss >> output;
            probs[index][numfound]=output;
            numfound++;
            i+=delleng;
            k=i;
        }
        else
        {
            i++;
        }
    }
    stringstream ss2;
    ss2 << str.substr(k, i-k);
    double output2;
    ss2 >> output2;
    probs[index][numfound]=output2;
    return;
}
void savefile(double probs[][9], int width, int height)
{
    ofstream save;
    save.open("probs.txt");
    for(int n=0;n<width;n++)
    {
        for(int nn=0;nn<height;nn++)
        {
            stringstream ss;
            ss << probs[n][nn];
            double out;
            ss >> out;
            save << out;
            if(nn != height-1)
            {
                save << ",";
            }
        }
        if(n != width-1)
        {
            save << endl;
        }
    }
    save.close();
    return;
}
int choosemove(double probrow[])
{
    double sum=0;
    double pstart[9];
    double pend[9];
    for(int n=0;n<9;n++)
    {

        pstart[n]=sum;
        sum = sum + probrow[n];
        pend[n]=sum;
    }
    srand((unsigned)time(NULL));
    double rval=((double)rand()/(double)RAND_MAX) * sum;
    int retval=-1;
    for(int n=0;n<9;n++)
    {
        if(rval >= pstart[n] & rval < pend[n])
        {
            retval=n;
            break;
        }
    }
    return retval;
}
void playgame(double probs[][9])
{
}
int main()
{
    const int WIDTH = pow(3,9);
    const int HEIGHT = 9;
    double probs[WIDTH][HEIGHT];
    for(int n=0;n<WIDTH;n++)
    {
        for(int nn=0;nn<HEIGHT;nn++)
        {
            probs[n][nn]=1.0;
        }
    }
    ifstream probfile("probs.txt");

    string line;
    if(probfile.is_open())
    {
        int n = 0;
        while(probfile.good())
        {
            getline(probfile,line);
            explode(line,n,probs);
            n++;
        }
    }else
    {
        savefile(probs, WIDTH, HEIGHT);
    }
    bool end=false;
    cout << "Please type a command, or type 'help' if you do not know what to do." << endl;
    while(end==false)
    {
        string com;
        cout << endl;
        cout << ">";
        cin >> com;
        if(com == "help")
        {
            cout << "Help Menu:"<<endl;
            cout << "help - Displays this menu" <<endl;
            cout << "exit - Exits the program safely." <<endl;
            cout << "save - Saves the current probability data into file" <<endl;
            cout << "play - Has the computer play a game against you" <<endl;
            cout << "While playing a game, these are the values to enter for each slot:"<<endl;
            cout << "[1,2,3]" <<endl;
            cout << "[4,5,6]" <<endl;
            cout << "[7,8,9]" <<endl;
        }else if (com == "exit")
        {
            end=true;
        }else if (com=="save")
        {
            savefile(probs,WIDTH,HEIGHT);
        }else if(com=="play")
        {
            playgame(probs);
        }
    }

    return 0;
}
