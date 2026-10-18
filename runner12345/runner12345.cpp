#include <iostream>
using namespace std;

class Competitor
{
protected:
    string name;
    int speed;
    int jumpheight;
    int distance;
    bool eliminated;
public:
    int run()
    {
        cout << name << " runs\n\n";
        distance++;
        return speed;
    }
    int jump()
    {
        cout << name << " jumps\n\n";
        distance++;
        return jumpheight;
    }
public:
    Competitor(string n, int s, int j)
    {
        name = n;
        speed = s;
        jumpheight = j;
        distance = 0;
        eliminated = false;
    }
    string getName()
    {
        return name;
    }
    int getDistance()
    {
        return distance;
    }
    bool isEliminated()
    {
        return eliminated;
    }
    void eliminate()
    {
        eliminated = true;
    }
};

class Human : public Competitor
{
public:
    Human(string n, int s, int j) : Competitor(n, s, j) {};
};

class Cat : public Competitor
{
public:
    Cat(string n, int s, int j) : Competitor(n, s, j) {};
};

class Robot : public Competitor
{
public:
    Robot(string n, int s, int j) : Competitor(n, s, j) {};
};

class Obstacle
{
protected:
    string name;
public:
    virtual bool getPast(Competitor* c) = 0;
    string getName()
    {
        return name;
    }
};
class Treadmill : public Obstacle
{
    int length;
public:
    Treadmill(int l)
    {
        length = l;
        name = "Treadmill";
    }
    virtual bool getPast(Competitor* c)
    {
        if (c->run() < length)
        {
            c->eliminate();
            return false;
        }
        else return true;
    }
};
class Wall : public Obstacle
{
    int height;
public:
    Wall(int h)
    {
        height = h;
        name = "Wall";
    }
    virtual bool getPast(Competitor* c)
    {
        if (c->jump() < height)
        {
            c->eliminate();
            return false;
        }
        else return true;
    }
};


int main()
{
    int runnercount = 3;
    Competitor** runners = new Competitor*[runnercount];
    runners[0] = new Human("Human",5,3);
    runners[1] = new Cat("Cat", 7, 5);
    runners[2] = new Robot("Robot", 3, 6);

    int distance = 4;
    Obstacle** obst = new Obstacle * [distance];
    obst[0] = new Wall(1);
    obst[1] = new Treadmill(3);
    obst[2] = new Treadmill(5);
    obst[3] = new Wall(5);
    for (int i = 0; i < distance; i++)
    {
        for (int j = 0; j < runnercount; j++)
        {
            if (i == runners[j]->getDistance() && !runners[j]->isEliminated()) // если участник перед препятствием, и он ещё не выбыл
            {
                if (obst[i]->getPast(runners[j]))
                {
                    cout << runners[j]->getName() << " got past " << obst[i]->getName() << " at distance " << i << endl << endl;
                }
                else cout << runners[j]->getName() << " didn't get past " << obst[i]->getName() << " at distance " << i << " (ELIMINATED)\n\n";
            }
        }
    }

    //конец
    for (int j = 0; j < runnercount; j++)
    {
        if (!runners[j]->isEliminated())
        {
            cout << runners[j]->getName() << " got to the end (FINISHED)\n\n";
        }
    }
    
    for (int i = 0; i < runnercount; i++)
    {
        delete runners[i];
    }
    delete[] runners;
    for (int i = 0; i < distance; i++)
    {
        delete obst[i];
    }
    delete[] obst;
}
