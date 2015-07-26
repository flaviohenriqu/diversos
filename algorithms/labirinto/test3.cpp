#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

const string RIGHT("right");
const string LEFT("left");
const string UP("up");
const string DOWN("down");
const string AHEAD("ahead");

const string labyrinth[8][8] = {{"RD",    "LR",    "LRD",    "LRD",    "LRD",    "LR",    "LD",    "D"},
 {"UD",    "R",    "LUD",    "U",    "UD",    "D",    "RUD",    "LU"},
 {"UD",    "D",    "U",    "D",    "UD",    "UD",    "U",    "D"},
 {"UD",    "UD",    "RD",    "LU",    "U",    "RUD",    "LRD",    "LUD"},
 {"UD",    "UD",    "LU",    "LRD",    "LRD",    "LU",    "UD",    "U"},
 {"UD",    "RU",    "LR",    "LUD",    "UD",    "D",    "RU",    "LD"},
 {"UD",    "RD",    "LR",    "LU",    "U",    "RUD",    "LD",    "UD"},
 {"RU",    "LRU",    "LR",    "LRU",    "LR",    "LU",    "U",    "U"}};

void Move(const string &direction, string &head, int &x, int &y);
void TurnAround(string &head);
bool CanIgo(const string &direction, string &head, int &x, int &y);

int main(int argc, char *argv[])
{
string head = DOWN;

int xPosition = 0;
int yPosition = 0;
int xEndPosition = 7;
int yEndPosition = 7;

while(((xPosition != xEndPosition) || (yPosition != yEndPosition)))
{
 if (CanIgo(RIGHT, head, xPosition, yPosition) == true)
 {
 cout<<"RIGHT"<<endl;
 cout<<"HEAD: "<<head<<endl;
 Move(RIGHT, head, xPosition, yPosition );
 cout<<"XY POSITION: "<<xPosition<<", "<<yPosition<<endl;
 cout<<"HEAD: "<<head<<endl<<endl;
 }
 else if (CanIgo(AHEAD, head, xPosition, yPosition) == true)
 {
 cout<<"AHEAD"<<endl;
 cout<<"HEAD: "<<head<<endl;
 Move(AHEAD, head, xPosition, yPosition);
 cout<<"XY POSITION: "<<xPosition<<", "<<yPosition<<endl;
 cout<<"HEAD: "<<head<<endl<<endl;
 }
 else if (CanIgo(LEFT, head, xPosition, yPosition) == true)
 {
 cout<<"LEFT"<<endl;
 cout<<"HEAD: "<<head<<endl;
 Move(LEFT, head, xPosition, yPosition);
 cout<<"XY POSITION: "<<xPosition<<", "<<yPosition<<endl;
 cout<<"HEAD: "<<head<<endl<<endl;
 }
 else
 {
 TurnAround(head);
 }
}

cout<<"X POSITION: "<<xPosition<<", Y POSITION: "<<yPosition<<endl<<endl;

 return EXIT_SUCCESS;
}

void Move(const string &direction, string &head, int &x, int &y)
{
 if(head == DOWN)
 {
 if(direction == AHEAD) { head = DOWN;y++;}
 if(direction == RIGHT) { head = LEFT; x--;}
 if(direction == LEFT) { head = RIGHT; x++;}
 }
 else if(head == UP)
 {
 if(direction == AHEAD) y--;
 if(direction == RIGHT) { head = RIGHT; x++;}
 if(direction == LEFT) { head = LEFT; x--;}
 }
 else if(head == RIGHT)
 {
 if(direction == AHEAD) x++;
 if(direction == RIGHT) { head = DOWN; y++;}
 if(direction == LEFT) { head = UP; y--;}
 }
 else if(head == LEFT)
 {
 if(direction == AHEAD) x--;
 if(direction == RIGHT) { head = UP; y--;}
 if(direction == LEFT) { head = DOWN; y++;}
 }
 return;
 }

void TurnAround(string &head)
{
 if (head == UP) {head = DOWN; return;}
 if (head == DOWN) {head = UP; return;}
 if (head == RIGHT) {head = LEFT; return;}
 if (head == LEFT) {head = RIGHT; return;}
 }

bool CanIgo(const string &direction, string &head, int &x, int &y)
{
 string str1 (labyrinth[y][x]);
 string str2;

////
 if(head == DOWN)
 {
 if(direction == AHEAD) str2 = 'D';
 if(direction == RIGHT) str2 = 'L';
 if(direction == LEFT) str2 = 'R';
 }
 else if(head == UP)
 {
 if(direction == AHEAD) str2 = 'U';
 if(direction == RIGHT) str2 = 'R';
 if(direction == LEFT) str2 = 'L';
 }
 else if(head == RIGHT)
 {
 if(direction == AHEAD) str2 = 'R';
 if(direction == RIGHT) str2 = 'D';
 if(direction == LEFT) str2 = 'U';
 }
 else if(head == LEFT)
 {
 if(direction == AHEAD) str2 = 'L';
 if(direction == RIGHT) str2 = 'U';
 if(direction == LEFT) str2 = 'D';
 }

 string::size_type loc = str1.find( str2, 0 );
 if( loc != string::npos )
 {
 return true;
 }
 else
 {
 return false;
 }
 }