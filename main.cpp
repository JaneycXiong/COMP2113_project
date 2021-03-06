#include <iostream>
#include <cctype>
#include <string>
#include <iomanip>
#include "zuma.h"
#include "tfs.h"

using namespace std;


//map design & initilization

char map[13][13];

char map1[13][13] =
{
  '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
  '#', '=', ' ', 'G', 'R', 'G', ' ', ' ', ' ', ' ', ' ', ' ', '#',
  '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#',
  '#', '+', ' ', ' ', '^', ' ', '#', ' ', 'K', ' ', '#', ' ', '#',
  '#', ' ', 'S', 'K', '#', ' ', '#', ' ', '+', ' ', '#', ' ', '#',
  '#', '#', '^', '#', '#', ' ', '#', '#', '#', '^', '#', ' ', '#',
  '#', 'K', ' ', ' ', '#', ' ', '^', ' ', 'W', ' ', '#', ' ', '#',
  '#', ' ', 'S', 'K', '#', ' ', '#', '#', '#', '#', '#', ' ', '#',
  '#', '^', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
  '#', ' ', ' ', ' ', '#', '#', '^', '#', '#', '#', '^', '#', '#',
  '#', '+', ' ', 'K', '#', 'K', ' ', 'K', '#', 'K', ' ', 'K', '#',
  '#', '+', ' ', 'B', '^', ' ', '~', ' ', '^', ' ', ' ', '+', '#',
  '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'
};

char map2[13][13] =
{
  '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
  '#', '~', ' ', 'K', '#', '+', ' ', ' ', '#', ' ', ' ', 'S', '#',
  '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '^', ' ', '#', ' ', '#',
  '#', '^', '#', '^', '#', '#', '#', '#', '#', ' ', '#', ' ', '#',
  '#', ' ', '#', ' ', ' ', ' ', '^', ' ', ' ', 'R', '#', ' ', '#',
  '#', ' ', '#', 'K', ' ', ' ', '#', 'K', ' ', ' ', '#', ' ', '#',
  '#', ' ', '#', '#', '#', '^', '#', '#', '#', '^', '#', ' ', '#',
  '#', ' ', '#', 'R', ' ', ' ', '#', '+', ' ', ' ', '#', ' ', '#',
  '#', '^', '#', '#', '#', ' ', '#', ' ', ' ', 'B', '^', ' ', '#',
  '#', 'W', ' ', ' ', '#', '+', '#', 'K', ' ', ' ', '#', ' ', '#',
  '#', ' ', ' ', 'K', '#', '#', '#', '#', '#', '#', '#', ' ', '#',
  '#', ' ', '+', ' ', ' ', 'G', '^', ' ', ' ', ' ', ' ', '=', '#',
  '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'
};

char map3[13][13] =
{
  '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
  '#', '+', ' ', ' ', '#', 'R', ' ', ' ', '#', ' ', '^', ' ', '#',
  '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#',
  '#', ' ', '#', ' ', ' ', ' ', '#', 'G', ' ', ' ', '#', ' ', '#',
  '#', 'B', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#',
  '#', ' ', '#', ' ', '#', 'W', ' ', ' ', ' ', ' ', ' ', ' ', '#',
  '#', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', '#',
  '#', 'K', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#',
  '#', '#', '#', '^', '#', '#', '#', '#', '#', ' ', '#', 'K', '#',
  '#', ' ', '+', 'B', '#', '+', ' ', ' ', '^', ' ', '#', ' ', '#',
  '#', 'S', ' ', ' ', '#', ' ', 'B', ' ', '#', '#', '#', '#', '#',
  '#', ' ', 'E', ' ', '#', 'K', ' ', ' ', 'S', ' ', ' ', '~', '#',
  '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'
};


////initilize role information and monster information
struct gameRole{
  int blood;
  int bluekey;
  int coin;
};


struct gameRole role = {500,0,0};


struct monster
{
  int blood;
  int coin;
};


struct monster bat = {100,2};
struct monster wizzard = {300,3};
struct monster GreenHeadMonster = {20,1};
struct monster RedHeadMonster = {40,1};
struct monster Skeleton = {50,1};


// function prototype
bool bloodPK (monster);
void drawmap (char[13][13]);
int keyDown (gameRole &, char[13][13], char &, char &, int, int, int &, int &,
  int &, char &);
void keychange (char, int &, int &);
void print_role (gameRole);


//main function of the game
int main()
{
  cout<<"Welcome! You enter an amazing world.  You have to go through 3 maps and finish 3 games to escape."<<endl;
  cout<<"You should find 'E' to enter the final game"<<endl;
  cout<<"Use the w(up) a(left) s(down) d(right) keys to move the character in the map. "<<endl;
    cout<< "You can choose fighting with Monsters by inputing 'Y' when you meet them. Whether you can defeat it depends bloods of you two. If you can defeat them, you will get corresponding coins"<<endl;
  cout<<"You need to pay attention to the keys in the map and collect them to open the door."<<endl;

  cout<<"Characters represent following items:"<<endl;

  cout<<"'E': Enter the final game"<<endl;
  cout<<"'#': wall"<<endl;
  cout<<" : road"<<endl;
  cout<<"^: blue door"<<endl;
  cout<<"'K': blue key"<<endl;
  cout<<"'+': Adding 150 blood"<<endl;
  cout<<"Monsters:'character' {blood, coin} "<<endl;
  cout<<"GreenHeadMonster:'G' {20,1} "<<endl;
  cout<<" RedHeadMonster:'R'  {40,1} "<<endl;
  cout<<"Skeleton :'S'{50,1} "<<endl;
  cout<<"Bat :'B'{100,2} "<<endl;
  cout<<"wizzard: 'W' {300,3} "<<endl;

  cout<<"At the beginning, you have 500 blood:"<<endl;
  int level;
  char userKey;
  int keyi, keyj;

  char if357;
  char play = 'y';

  // if the player doesn't want to play again after he dies, end the loop
  // if the player wants to play again then start the game from beginning
  while (play == 'y')
  {
    //need to reinitilize map and role after the player plays again

    level = 1;
    char die = 'n';
    int x = 11;
    int y = 6;

    gameRole role = {500, 0, 0};

    //map1[13][13] = ;
    //map2[13][13] = ;
    //map3[13][13] = ;

    // if the player dies ends the loop
    // each iteration take 1 userkey, to determine the direction
    while (die != 'y')
    {
      switch ( level )
      {
        // when the player is at different levels, use map1, map2, map3 as
        // corresponding array variables

        case 1:
          // take userkey as direction
          // change map1, role information, location of the role accordingly

          drawmap (map1);
          cout << "Input which direction to go: ";
          cin >> userKey;
          userKey = tolower(userKey);
          keychange (userKey, keyi, keyj);
          keyDown (role, map1, die, play, keyi, keyj, x, y, level, if357);
          print_role(role);
          break;

        case 2:
          // take userkey as direction
          // change map2, role information, location of the role accordingly

          drawmap (map2);
          cout << "Input which direction to go: ";
          cin >> userKey;
          userKey = tolower(userKey);
          keychange (userKey, keyi, keyj);
          keyDown (role, map2, die, play, keyi, keyj, x, y, level, if357);
          print_role(role);
          break;

        case 3:
          // take userkey as direction
          // change map, role information, location of the role accordingly

          drawmap (map3);
          cout << "Input which direction to go: ";
          cin >> userKey;
          userKey = tolower(userKey);
          keychange (userKey, keyi, keyj);
          keyDown (role, map3, die, play, keyi, keyj, x, y, level, if357);
          print_role(role);
          break;
      }
    }

    play = tolower(play);
  }





  return 0;
}


bool bloodPK(gameRole &role, monster mons)
{ // PK, determine if the player can defeat a certain monster
  role.blood = role.blood  - mons.blood;

  // cannot defeat, player die
  if(role.blood <= 0)
  {
    return false;
  }
  // can defeat, get some coins correspondingly
  else
  {
    role.coin = role.coin + mons.coin;
    return true;
  }

}


void drawmap(char map[13][13])
{
  //draw map line by line
  int i,j;
  for (i = 0; i < 13; i++){
    cout << endl;
    for (j = 0; j < 13; j++)
    {cout << setw(2) << map[i][j];}
  }
  cout << "\n" << endl;
}


void print_role(gameRole role)
{
  //print role information
  cout << "\nblood: " << role.blood << endl;
  cout << "bluekey: " << role.bluekey << endl;
  cout << "coin: " << role.coin << endl;
}


int keyDown (gameRole &role, char map[13][13], char &die, char &play, int keyi,
  int keyj, int &i, int &j, int &level, char &if357)
{
  //take userkey as direction, change map, role location, role information

  char YorN;
  switch ( map[i + keyi][j + keyj] )
  {
    case ' ':
    // place to go is empty
      map[i][j] = ' ';
      map[i + keyi][j + keyj] = '~';
      i = i + keyi;
      j = j + keyj;
      break;

    case '=':
    // go upstairs
      int point;
      cout << "Welcome to zuma game!" << endl;
      cout << "You should input balls as less as you can. The less ball you use, the more coins you will get."<<endl;
      zuma_main(point);
      if (point > 0) {
        role.coin += 2;
        cout << "You got 2 coins." << endl;
      }
      level += 1;
      i = i + keyi;
      j = j + keyj;

      break;

    case 'K':
    //key
      map[i][j] = ' ';
      map[i + keyi][j + keyj] = '~';
      role.bluekey++;
      i = i + keyi;
      j = j + keyj;
      break;

    case '^':
    // door need key to open
      if (role.bluekey > 0){
        map[i][j] = ' ';
        map[i + keyi][j + keyj] = '~';
        i = i + keyi;
        j = j + keyj;
        role.bluekey--;
      }
      else {
        cout << "You need to collect keys.";}

      break;

    case '+':
      //add blood
      role.blood += 100;
      map[i][j] = ' ';
      map[i + keyi][j + keyj] = '~';
      i = i + keyi;
      j = j + keyj;
      break;

    case 'B':
      //meet bat
      cout << "You meet the bat, fight it or not？";
      cin >> YorN;
      YorN = tolower(YorN);
      if (YorN == 'y') {
        //PK with bat
        if (bloodPK(role, bat))
        {
          cout << "You beat it" << endl;
          map[i][j] = ' ';
          map[i + keyi][j + keyj] = '~';
          i = i + keyi;
          j = j + keyj;
        }
        else
        {
          die = 'y';
          cout << "You die, play again? ";
          cin >> play;
        }
      }
      break;

    case 'W':
      //meet wizzard
      cout << "You meet the wizzard, fight it or not？";
      cin >> YorN;
      YorN = tolower(YorN);
      if (YorN == 'y') {
      //PK with wizzard
        if (bloodPK(role, wizzard))
        {
          cout << "You beat it" << endl;
          map[i][j] = ' ';
          map[i + keyi][j + keyj] = '~';
          i = i + keyi;
          j = j + keyj;
        }
        else
        {
          die = 'y';
          cout << "You die, input 'y' to play again";
          cin >> play;
        }
      }
      break;

    case 'R':
      //meet red head monster
      cout << "You meet the red head monster, fight it or not？";
      cin >> YorN;
      YorN = tolower(YorN);
      if (YorN == 'y') {
        //PK with red monster
        if (bloodPK(role, RedHeadMonster))
        {
          cout << "You beat it" << endl;
          map[i][j] = ' ';
          map[i + keyi][j + keyj] = '~';
          i = i + keyi;
          j = j + keyj;
        }
        else
        {
          die = 'y';
          cout << "You die, play again? ";
          cin >> play;
        }
      }
      break;

    case 'G':
      //meet green head monster
      cout << "You meet the green head monster, fight it or not？";
      cin >> YorN;
      YorN = tolower(YorN);
      if (YorN == 'y') {
        //PK with green head monster
        if (bloodPK(role, GreenHeadMonster))
        {
          cout << "You beat it" << endl;
          map[i][j] = ' ';
          map[i + keyi][j + keyj] = '~';
          i = i + keyi;
          j = j + keyj;
        }
      else
        {
          die = 'y';
          cout << "You die, play again? ";
          cin >> play;
        }
      }
      break;

    case 'S':
    //meet Skeleton
      cout << "You meet the Skeleton, fight it or not？";
      cin >> YorN;
      YorN = tolower(YorN);
      if (YorN == 'y') {
        //PK with Skeleton
        if (bloodPK(role, Skeleton))
        {
          cout << "You beat it" << endl;
          map[i][j] = ' ';
          map[i + keyi][j + keyj] = '~';
          i = i + keyi;
          j = j + keyj;
        }
        else
        {
          die = 'y';
          cout << "You die, play again? ";
          cin >> play;
        }
      }
      break;

    case 'E':
    //check if the player wants to enter 357 game
      cout << "You find the final challenge, input 'y' to fight with the BOSS!!";
      cin >> if357;
      if (if357 == 'y') {
        die = 'y';
        play = 'n';
      }
      // if the player wants to enter 357 game

        // player play 357 game for many times, each time the player uses a coin
        while (role.coin > 0  && role.coin <99){
          cout<<"Now, you have "<<role.coin<<" coins."<<endl;
          cout<<"You have to win the game within "<<role.coin<<" games. Otherwise you will lose."<<endl;
          // if player wins the 357 game, final SUCCESS
          if (tfs()) {
            cout << "You have achieved final SUCCESS" << endl;

            role.coin=100;
            return 0;
          }
          else {
            cout << "Play 357 game again." << endl;

            role.coin--;
          }
        }

        // after used all the coins and didn't win 357 game
        if (role.coin == 0)
          {cout << "You lost the 357 game. But you have been a brave warrior!!!" << endl;}


  }
  return 0;
}


// determine how the user location change for each direction
// e.g. if go left, i-1, j doesn't change, then keyi = -1, keyj = 0
void keychange (char userKey, int &keyi, int &keyj)
{
  switch (userKey)
  {
    case 'a':
     keyi = 0;
     keyj = -1;
     break;

    case 'd':
      keyi = 0;
      keyj = 1;
      break;

    case 'w':
      keyi = -1;
      keyj = 0;
      break;

    case 's':
      keyi  = 1;
      keyj = 0;
      break;
  }

}
