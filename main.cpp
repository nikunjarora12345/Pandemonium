#include<iostream>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

using namespace std;

COORD coord={0,0};

void gotoxy(int x,int y){
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}



class player{
public:
    int hp,max_hp,attack,defence,level,exp=0,next_exp;
    player(int player_level){
        level = player_level;
        init();
    }
    void init(){
        next_exp = level*5+10;
        if(level>=10)
            exp = next_exp;
        max_hp = level*3+10;
        hp = max_hp;
        attack = level*3;
        defence = level*2;
    }
    void level_up(int previous_exp){
        if(level<10)
            level++;
        exp = previous_exp;
        init();
    }
    void exp_up(int value){
        if(level<10){
            exp += value;
            if(exp>=next_exp)
                level_up(exp-next_exp);
        }else{
            exp = next_exp;
        }
    }
    void hit(int damage){
        hp -= damage;
    }
    void heal(){
        hp += 20;
        if(hp>=max_hp)
            hp = max_hp;
    }
};

class enemy{
public:
    int hp,max_hp,attack,defence,level;
    enemy(int enemy_level){
        level = enemy_level;
        init();
    }
    void init(){
        max_hp = level*3+10;
        hp = max_hp;
        attack = level*3;
        defence = level*2;
    }
    void hit(int damage){
        hp -= damage;
    }
    void heal(){
        hp += 20;
        if(hp>=max_hp)
            hp = max_hp;
    }
};
int i,j,k;

int match(player &p,enemy &e){
    while(p.hp>0&&e.hp>0){
        system("cls");
        gotoxy(1,0);
        cout<<"hp : ";
        for(i=0;i<p.hp*20/p.max_hp;i++)
            cout<<"*";
        gotoxy(26,0);
        cout<<"("<<p.hp<<"/"<<p.max_hp<<")";

        gotoxy(1,1);
        cout<<"exp : ";
        for(i=0;i<p.exp*20/p.next_exp;i++)
            cout<<"*";
        gotoxy(27,1);
        cout<<"("<<p.exp<<"/"<<p.next_exp<<")";

        gotoxy(1,2);
        cout<<"level : "<<p.level;

        gotoxy(1,3);
        cout<<"attack : "<<p.attack;

        gotoxy(1,4);
        cout<<"defence : "<<p.defence;

        gotoxy(0,5);
        for(i=0;i<80;i++)
            cout<<"#";

        gotoxy(0,20);
        for(i=0;i<80;i++)
            cout<<"#";

        gotoxy(45,21);
        cout<<"defence : "<<e.defence;

        gotoxy(45,22);
        cout<<"attack : "<<e.attack;

        gotoxy(45,23);
        cout<<"level : "<<e.level;

        gotoxy(45,24);
        cout<<"hp : ";
        for(i=0;i<e.hp*20/e.max_hp;i++)
            cout<<"*";
        gotoxy(70,24);
        cout<<"("<<e.hp<<"/"<<e.max_hp<<")";

        gotoxy(1,6);
        cout<<"Please choose an action : 1.Attack\t2.Defend\t3.Heal\n";
        int pm;
        pm = getch();
        pm -= 48;
        int em;
        if(e.hp<e.max_hp/2){
            srand (time(NULL));
            em = rand()%3+1;
        }else{
            srand (time(NULL));
            em = rand()%2+1;
        }
        switch(pm){
        case 1:
            gotoxy(1,10);
            cout<<"Attack";
            gotoxy(65,10);
            if(em==1){
                cout<<"Attack";
                int damage = p.attack - e.attack;
                if(damage>0){
                    p.hit(2);
                    gotoxy(1,15);
                    cout<<"hp : -2";
                    e.hit(damage);
                    gotoxy(65,15);
                    cout<<"hp : -"<<damage;
                }else if(damage<0){
                    p.hit(0-damage);
                    gotoxy(1,15);
                    cout<<"hp : -"<<0-damage;
                    e.hit(2);
                    gotoxy(65,15);
                    cout<<"hp : -2";
                }else{
                    e.hit(2);
                    p.hit(2);
                    gotoxy(1,15);
                    cout<<"hp : -2";
                    gotoxy(65,15);
                    cout<<"hp : -2";
                }
            }
            else if(em==2){
                cout<<"Defend";
                int damage = p.attack - e.defence;
                if(damage>0){
                    e.hit(p.attack);
                    p.hit(2);
                    gotoxy(1,15);
                    cout<<"hp : -2";
                    gotoxy(65,15);
                    cout<<"hp : -"<<p.attack;
                }else if(damage<0){
                    p.hit(0-damage);
                    gotoxy(1,15);
                    cout<<"hp : -"<<0-damage;
                    e.hit(2);
                    gotoxy(65,15);
                    cout<<"hp : -2";
                }else{
                    e.hit(2);
                    p.hit(2);
                    gotoxy(1,15);
                    cout<<"hp : -2";
                    gotoxy(65,15);
                    cout<<"hp : -2";
                }
            }else{
                cout<<"Heal";
                e.heal();
                gotoxy(65,15);
                cout<<"hp : +20";
                e.hit(p.attack);
                gotoxy(65,16);
                cout<<"hp : -"<<p.attack;
            }
            break;
        case 2:
            gotoxy(1,10);
            cout<<"Defend";
            gotoxy(65,10);
            if(em==1){
                cout<<"Attack";
                int damage = p.defence - e.attack;
                if(damage>0){
                    p.hit(2);
                    gotoxy(1,15);
                    cout<<"hp : -2";
                    e.hit(damage);
                    gotoxy(65,15);
                    cout<<"hp : -"<<damage;
                }else if(damage<0){
                    p.hit(e.attack);
                    gotoxy(1,15);
                    cout<<"hp : -"<<e.attack;
                    e.hit(2);
                    gotoxy(65,15);
                    cout<<"hp : -2";
                }else{
                    e.hit(2);
                    p.hit(2);
                    gotoxy(1,15);
                    cout<<"hp : -2";
                    gotoxy(65,15);
                    cout<<"hp : -2";
                }
            }
            else if(em==2){
                cout<<"Defend";
            }else{
                cout<<"Heal";
                e.heal();
                gotoxy(65,15);
                cout<<"hp : +20";
            }
            break;
        case 3:
            gotoxy(1,10);
            cout<<"Heal";
            gotoxy(65,10);
            if(em==1){
                cout<<"Attack";
                p.heal();
                gotoxy(1,15);
                cout<<"hp : +20";
                p.hit(e.attack);
                gotoxy(1,16);
                cout<<"hp : -"<<e.attack;
            }
            else if(em==2){
                cout<<"Defend";
                p.heal();
                gotoxy(1,15);
                cout<<"hp : +20";
            }else{
                cout<<"Heal";
                p.heal();
                gotoxy(1,15);
                cout<<"hp : +20";
                e.heal();
                gotoxy(65,15);
                cout<<"hp : +20";
            }
            break;
        default:
            gotoxy(1,10);
            cout<<"Confused";
            gotoxy(65,10);
            if(em==1){
                cout<<"Attack";
                p.hit(e.attack);
                gotoxy(1,15);
                cout<<"hp: -"<<e.attack;
            }else if(em==2){
                cout<<"Defend";
            }else{
                cout<<"Heal";
                e.heal();
                gotoxy(65,15);
                cout<<"hp : +20";
            }
            break;
        }
        getch();
    }
    if(p.hp<=0){
        system("cls");
        gotoxy(40,12);
        cout<<"You lose...";
        getch();
        return 0;
    }else if(e.hp<=0){
        system("cls");
        gotoxy(40,12);
        cout<<"You win...";
        if(p.exp+(e.level-p.level)+20 >= p.next_exp && p.level<10){
            gotoxy(40,14);
            cout<<"Congratulations, you level up...";
        }
        p.exp_up((e.level-p.level)+20);
        gotoxy(40,13);
        cout<<"exp : +"<<(e.level-p.level)+20;
        getch();
        return 1;
    }
}

void intro(){
    system("cls");
    gotoxy(20,10);
    cout<<"Welcome to the Pandemonium";
    gotoxy(20,11);
    cout<<"By :- Nikunj Arora";
    gotoxy(20,12);
    cout<<"Press any key to enter...";
    getch();
    system("cls");
    gotoxy(35,1);
    cout<<"Rules";
    gotoxy(1,5);
    cout<<"1.This game is played by 2 players.";
    gotoxy(1,7);
    cout<<"2.Each player can choose the starting level of their character. They will get  initial points accordingly";
    gotoxy(1,10);
    cout<<"3.Both the players now decide the total number of opponents to face.";
    gotoxy(1,12);
    cout<<"4.Then each player will choose the number of opponents to face in their\nrespective turns.";
    gotoxy(1,15);
    cout<<"5.The level of opponents appearing will be purely random.";
    gotoxy(1,17);
    cout<<"6.If the player manages to defeat all the opponents chosen by them, the points get added up.";
    gotoxy(1,20);
    cout<<"7.If the player loses even 1 fight, all the opponents they defeated in the\ncurrent turn will be negated.";
    gotoxy(30,24);
    cout<<"Press any key to continue...";
    getch();
}

int main(){
    intro();
    system("cls");
    int level[2];
    for(i=0;i<2;i++){
        while(level[i]<1 || level[i]>10){
            system("cls");
            gotoxy(1,12);
            cout<<"More is the level of your player, easier is the game but less is the fun...";
            gotoxy(1,10);
            cout<<"Select the level for your player "<<i+1<<" (1 to 10) : ";
            cin>>level[i];
        }
    }
    player p1(level[0]);
    player p2(level[1]);
    system("cls");
    int enemies,points1=20-(p1.level*2),points2=20-(p2.level*2),fight,el,result=0;
    gotoxy(1,10);
    cout<<"Enter the total number of enemies : ";
    cin>>enemies;
    while(enemies>0){
        p1.hp = p1.max_hp;
        p2.hp = p2.max_hp;
        for(k=0;k<2;k++){
            system("cls");
            gotoxy(1,1);
            cout<<"Player 1 points : "<<points1;
            gotoxy(60,1);
            cout<<"Player 2 points : "<<points2;
            gotoxy(35,1);
            cout<<"Player "<<k+1;
            gotoxy(1,24);
            cout<<"Enemies remaining : "<<enemies;
            gotoxy(1,12);
            cout<<"Enter the number of opponents you want to fight : ";
            cin>>fight;
            if(enemies-fight < 0){
                system("cls");
                gotoxy(1,10);
                cout<<"How can you fight "<<fight<<" number of opponents when only "<<enemies<<" are left...";
                gotoxy(1,12);
                cout<<"Utilize your turn to learn some maths...";
                getch();
                continue;
            }
            for(j=0;j<fight;j++){
                system("cls");
                gotoxy(20,11);
                cout<<"Enemy "<<j+1;
                gotoxy(20,12);
                cout<<"Press any key to begin...";
                getch();
                srand (time(NULL));
                el = rand()%10 + 1;
                enemy e(el);
                if(k==0)
                    result = match(p1,e);
                else if(k==1)
                    result = match(p2,e);
                if(result==0)
                    break;
                else if(result==1)
                    continue;
            }
            if(result==1){
                if(k==0){
                    points1 += fight;
                    enemies -= fight;
                    if(enemies==0)
                        break;
                }else if(k==1){
                    points2 += fight;
                    enemies -= fight;
                    if(enemies==0)
                        break;
                }
            }
        }
    }
    system("cls");
    gotoxy(35,10);
    if(points1 > points2)
        cout<<"Player 1 wins...";
    else if(points1 < points2)
        cout<<"Player 2 wins...";
    else
        cout<<"It's a draw...";
    gotoxy(35,12);
    cout<<"Thanks for playing...:)";
    getch();
}
