#include<iostream>
#include<vector>
using namespace std;
#define MAXCastMembers 20
#define MAXCrewMembers 10
#define MAX 40

class Exception
{
    public:
    string a;
    Exception(string a)
    {
        this->a=a;
    }
    void displayError()
    {
        cout<<"Error :"<<a<<endl;
    }
};

class Person
{
    public:
    string name;
    int age;
    string gender;
    Person()
    {}
    Person(string name,int age,string gender)
    {
        this->name=name;
        this->age=age;
        this->gender=gender;
    }
    virtual void display()
    {
        cout<<"Name: "<<name<<" Age: "<<age<<" Gender: "<<gender<<endl;
    }
};


class Audience:public Person
{
    public:
    int seatNo=0;
    float ratingsGiven;
    static int AudienceCount;
    Audience()
    {}
    Audience(string name,int age,string gender):Person(name,age,gender)
    {
        this->ratingsGiven=0;
        AudienceCount++;
    }
    void display()
    {
        Person::display();
        cout<<"Seat No: "<<seatNo<<" Ratings given to Drama: "<<ratingsGiven<<endl;
    }
    static Audience searchSeat(int n,Audience a[MAX])
    {
        for(int i=0;i<AudienceCount;i++)
        {
            if(a[i].seatNo==n)
            {
                return a[i];
            }
        }
    }
};
int Audience::AudienceCount=0;


class CastMember:public Person
{
    public:
    int exp;
    float rating;
    int salary;
    static int CastMemberCount;
    CastMember()
    {}
    CastMember(string name,int age,string gender,int exp,float rating,int salary):Person(name,age,gender)
    {
        this->exp=exp;
        this->rating=rating;
        this->salary=salary;
        CastMemberCount++;
    }
    virtual void display()
    {
        Person::display();
        cout<<"Experience in years: "<<exp<<" Ratings: "<<rating<<" Salary: "<<salary<<endl;
    }
    virtual int HikeSalary(int percent)
    {
        salary=salary+salary*percent/100;
        return salary;
    }
    void HikeRating()
    {
        rating=rating+0.5;
    }
};
int CastMember::CastMemberCount=0;


class CrewMember:public Person
{
    public:
    string Designation;
    int exp;
    int earningsFromShow;
    static int CrewMemberCount;
    CrewMember()
    {}
    CrewMember(string name,int age,string gender,string Designation,int exp,int earningsFromShow):Person(name,age,gender)
    {
        this->Designation=Designation;
        this->exp=exp;
        this->earningsFromShow=earningsFromShow;
        CrewMemberCount++;
    }
    void display()
    {
        Person::display();
        cout<<"Designation: "<<Designation<<" Experience in Years: "<<exp<<" Earnings From One Show: "<<earningsFromShow<<endl;
    }
};
int CrewMember::CrewMemberCount=0;


class Actor:public CastMember
{
    public:
    int screenOnTime;
    string actorType;
    Actor()
    {}
    Actor(string name,int age,string gender,int exp,float rating,int salary,int screenOnTime,string actorType):CastMember(name,age,gender,exp,rating,salary)
    {
        this->screenOnTime=screenOnTime;
        this->actorType=actorType;
    }
    void display()
    {
        CastMember::display();
        cout<<"ScreenOnTime: "<<screenOnTime<<" Actor Type: "<<actorType<<endl;
    }
    int HikeSalary(int percent)
    {
        int sal=salary;
        int oldHike=CastMember::HikeSalary(percent);
        cout<<oldHike<<endl;
        if(actorType=="Main")
            salary=screenOnTime*10+oldHike;
        else
            salary=screenOnTime*5+oldHike;
    }
};


class Musician:public CastMember
{
    public:
    int noOfSongs;
    Musician()
    {}
    Musician(string name,int age,string gender,int exp,float rating,int salary,int noOfSongs):CastMember(name,age,gender,exp,rating,salary)
    {
        this->noOfSongs=noOfSongs;
    }
    void display()
    {
        CastMember::display();
        cout<<"No of Songs: "<<noOfSongs<<endl;
    }
    int HikeSalary(int percent)
    {
        int oldHike=CastMember::HikeSalary(percent);
        salary=oldHike+noOfSongs*20;
    }
};


class Ticket
{
    public:
    int ticketNo;
    int seatNo;
    string audName;
    int flag=0;
    static int TicketCount;
    Ticket(){}
    Ticket(int ticketNo,int seatNo)
    {
        this->ticketNo=ticketNo;
        this->seatNo=seatNo;
        TicketCount++;
    }
    void BuyTicket(string aa)
    {
        if(flag==0)
        {
        this->audName=aa;
        flag=1;
        }
        else
        {
            cout<<"Seat already Occupied"<<endl;
        }
    }
    void cancelTicket()
    {
        flag=0;
        this->audName="";
    }
    void display()
    {
        cout<<"Ticket Number: "<<ticketNo<<" Seat Number: "<<seatNo<<endl;
        if(flag==0)
        {
            cout<<"Not issued"<<endl;
        }
        else
        {
            cout<<"issued to :"<<audName<<endl;
        }
    }
};
int Ticket::TicketCount=0;

class Drama
{
    private:
    Drama(string DramaName,int cost)
    {
        this->DramaName=DramaName;
        this->cost=cost;
    }
    Drama(){}
    public:
    static Drama instance;
    static string DramaName;
    float Rating=0;
    static int cost;
    Ticket ticket[MAX];
    Audience aud[MAX];
    CastMember *cast[MAXCastMembers];
    CrewMember crew[MAXCrewMembers];
    static Drama& get(string a,int b)
    {
        DramaName=a;
        cost=b;
        return instance;
    }

    void displayRating()
    {
        float sum=0;
        for(int i=0;i<Audience::AudienceCount;i++)
        {
            sum=sum+(aud[i]).ratingsGiven;
        }
        Rating=sum/(float)Audience::AudienceCount;
        cout<<"Drama Rating is "<<Rating<<endl;
    }
    void CalculateTotalEarning()
    {
        cout<<Audience::AudienceCount*cost<<endl;
    }
    void issueTicket(int number,string aname)
    {
        for(int i=0;i<Ticket::TicketCount;i++)
        {
            if(ticket[i].seatNo==number)
            {
                ticket[i].BuyTicket(aname);
            }
        }
        for(int i=0;i<Audience::AudienceCount;i++)
        {
            if(aud[i].name==aname)
            {
                aud[i].seatNo=number;
            }
        }
    }
    void cancelTicket(int number,string name)
    {
        for(int i=0;i<Ticket::TicketCount;i++)
        {
            if(ticket[i].seatNo==number)
            {
                ticket[i].cancelTicket();
            }
        }
        for(int i=0;i<Audience::AudienceCount;i++)
        {
            if(aud[i].name==name)
            {
                aud[i].seatNo=0;
            }
        }
    }
    void addActor(string name,int age,string gender,int exp,float rating,int salary,int screenOnTime,string actorType)
    {
        if(CastMember::CastMemberCount>=MAXCastMembers)
        {
            throw Exception("Cast members reached more than required");
        }
        else
        {
        cast[CastMember::CastMemberCount-1]=new Actor(name,age,gender,exp,rating,salary,screenOnTime,actorType);
        }
    }
    void addMusician(string name,int age,string gender,int exp,float rating,int salary,int noOfSongs)
    {
        if(CastMember::CastMemberCount>=MAXCastMembers)
        {
            throw Exception("Cast members reached more than required");
        }
        else
        {
        cast[CastMember::CastMemberCount-1]=new Musician(name,age,gender,exp,rating,salary,noOfSongs);
        }
    }
    void addCrewMember(string name,int age,string gender,string Designation,int exp,int earningsFromShow)
    {
        if(CrewMember::CrewMemberCount>=MAXCrewMembers)
        {
            throw Exception("Crew members reached more than required");
        }
        else
        {
        crew[CrewMember::CrewMemberCount-1]=CrewMember(name,age,gender,Designation,exp,earningsFromShow);
        }
    }
    void addAudience(string name,int age,string gender)
    {
        if(Audience::AudienceCount>=MAX)
        {
            throw Exception("All the seats have been occupied");
        }
        else
        {
            aud[Audience::AudienceCount-1]=Audience(name,age,gender);
        }
    }
    void displayDrama()
    {
        int x;
        cout<<"Drama name: "<<DramaName<<"Ticket Price: "<<cost<<endl;
        cout<<"Do you want to see all audience ?"<<endl<<"Press 1 for Yes and 0 for No"<<endl;
        cin>>x;
        if(x==1)
        {
        cout<<"Audience: "<<endl;
        for(int i=0;i<Audience::AudienceCount;i++)
        {
            aud[i].display();
        }
        cout<<endl;
        }
        cout<<"Do you want to see all the crew members and CastMembers?"<<endl<<"Press 1 for Yes and 0 for No"<<endl;
        cin>>x;
        if(x==1)
        {
        cout<<"Crew Members: "<<endl;
        for(int i=0;i<CrewMember::CrewMemberCount;i++)
        {
            crew[i].display();
        }
        cout<<endl;
        cout<<"Cast Members: "<<endl;
        for(int i=0;i<CastMember::CastMemberCount;i++)
        {
            cast[i]->display();
        }
        cout<<endl;
        }
        cout<<"Do you want to see all the tickets ?"<<endl<<"Press 1 for Yes and 0 for No"<<endl;;
        cin>>x;
        if(x==1)
        {
        cout<<"Tickets:"<<endl;
        for(int i=1;i<Ticket::TicketCount;i++)
        {
            ticket[i].display();
        }
        cout<<endl;
        }
    }
    void HikeRatings()
    {
        for(int i=0;i<CastMember::CastMemberCount;i++)
        {
            cast[i]->HikeRating();
        }
    }
    void giveRating(string namee,float rat)
    {
        for(int i=0;i<Audience::AudienceCount;i++)
        {
            if(aud[i].name==namee)
            {
                aud[i].ratingsGiven=rat;
            }
        }
    }
};
Drama Drama::instance;
int Drama::cost;
string Drama::DramaName;


int main()
{
    string username,password;
    cout<<endl<<endl;
    cout<<"||Welcome To Drama Management System||"<<endl;
    cout<<endl<<endl;
    cout<<"UserName:"<<endl;
    cin>>username;
    cout<<"Password:"<<endl;
    cin>>password;
    Drama& drama=Drama::get("Drama",50);
    for(int i=1;i<=20;i++)
    {
        drama.ticket[i]=Ticket(i*10,i);
    }
    drama.addAudience("Verna",56,"Female");
    drama.addAudience("Lillian",46,"male");
    drama.addAudience("Julius",23,"male");
    drama.addAudience("Wesley",24,"Female");
    drama.addAudience("Dean",34,"male");
    drama.addAudience("Terry",35,"male");
    drama.addAudience("Duane",61,"Female");
    drama.addAudience("Kristina",59,"Female");
    drama.addAudience("Milton",37,"male");
    drama.addAudience("Keith",66,"Female");
    drama.addAudience("Kristin",26,"Female");
    drama.addAudience("Kevin",46,"male");
    drama.addAudience("Lindsa",43,"Female");
    drama.addAudience("Devin",34,"male");
    drama.addAudience("Edith",21,"male");
    drama.issueTicket(1,"Verna");
    drama.issueTicket(2,"Lillian");
    drama.issueTicket(3,"Julius");
    drama.issueTicket(4,"Wesley");
    drama.issueTicket(5,"Dean");
    drama.issueTicket(6,"Terry");
    drama.issueTicket(7,"Duane");
    drama.issueTicket(8,"Kristina");
    drama.issueTicket(9,"Milton");
    drama.issueTicket(10,"Keith");
    drama.issueTicket(11,"Kritin");
    drama.issueTicket(12,"Kevin");
    drama.issueTicket(13,"Lindsa");
    drama.issueTicket(14,"Devin");
    drama.issueTicket(15,"Edith");
    drama.giveRating("Verna",3.2);
    drama.giveRating("Lillian",2.2);
    drama.giveRating("Julius",4);
    drama.giveRating("Wesley",4);
    drama.giveRating("Dean",2.7);
    drama.giveRating("Terry",5);
    drama.giveRating("Duane",4.1);
    drama.giveRating("Kristina",3.2);
    drama.giveRating("Milton",3.2);
    drama.giveRating("Keith",4.2);
    drama.giveRating("Kristin",1.6);
    drama.giveRating("Kevin",4.5);
    drama.giveRating("Lindsa",3.5);
    drama.giveRating("Devin",2.2);
    drama.giveRating("Edith",4.9);
    drama.addActor("Christine",25,"Female",5,4.5,10000,30,"Main");
    drama.addActor("Sarah",21,"Female",1,3.1,2000,5,"Side");
    drama.addActor("Ray",27,"male",8,4.7,15000,35,"Main");
    drama.addActor("Daniel",35,"male",18,5,20000,28,"Main");
    drama.addActor("Jay",32,"male",4,2.7,5000,7,"Side");
    drama.addActor("Darryl",19,"male",0,0,2000,1,"Side");
    drama.addActor("Janis",61,"Female",31,4,40000,15,"Main");
    drama.addMusician("Eduardo",26,"male",8,5,20000,4);
    drama.addMusician("Randall",29,"Female",10,5,15000,3);
    drama.addMusician("Wallace",38,"male",18,4,10000,3);
    drama.addCrewMember("Miles",56,"male","Director",20,70000);
    drama.addCrewMember("Quinn",29,"Female","MakeupArtist",9,50000);
    drama.addCrewMember("Daniels",32,"Female","choreographer",5,20000);
    drama.addCrewMember("Smith",25,"male","Cameraman",7,25000);
    drama.addCrewMember("Castillo",67,"male","Producer",40,100000);
    int ch;
    while(1)
    {
        cout<<"Press:"<<endl<<"1: add audience\n"<<"2: add Actors\n"<<"3: add Musicians\n"<<"4: add CrewMembers\n"<<"5: Buy and cancel ticket\n"<<"6: Display Ratings\n"<<"7: Calculate Total Income \n"<<"8: Display\n"<<"9: Hike Salary\n"<<"10: Hike Rating\n"<<"11: Give Ratings \n"<<"12:Exit\n"<<endl;
        cin>>ch;
        switch(ch)
        {
            case 1:
            {
            string a,c;
            int b;
            cout<<"Enter Name,Age,Gender:"<<endl;
            cin>>a>>b>>c;
            try{
                drama.addAudience(a,b,c);
            }
            catch(Exception e)
            {
                e.displayError();
            }
            }
            break;
            case 2:
            {
            string a,b,c;
            int d,e,f,h;
            float g;
            cout<<"Enter Name,Age,Gender,Exp,Rating,Salary,ScreenOnTIme,Actor Type:"<<endl;
            cin>>a>>d>>b>>e>>g>>f>>h>>c;
            try
            {
                drama.addActor(a,d,b,e,g,f,h,c);
            }
            catch(Exception e)
            {
                e.displayError();
            }
            }
            break;
            case 3:
            {
                string a,b;
                int c,d,e,f;
                float g;
                cout<<"Enter Name,Age,Gender,Exp,Rating,Salary,NoOfSongs:"<<endl;
                cin>>a>>c>>b>>d>>g>>e>>f;
            try
            {
                drama.addMusician(a,c,b,d,g,e,f);
            }
            catch(Exception e)
            {
                e.displayError();
            }
            }
            break;
            case 4:
            {
                string a,b,c;
                int d,e,f;
                cout<<"Enter Name,Age,Gender,Designation,Experience,EarningsFromShow:"<<endl;
                cin>>a>>d>>b>>c>>e>>f;
            try
            {
                drama.addCrewMember(a,d,b,c,e,f);
            }
            catch(Exception e)
            {
                e.displayError();
            }
            }
            break;
            case 5:
            {
                cout<<"Buy or Cancel"<<endl;
                int choice;
                cin>>choice;
                int x;
                string y;
                cout<<"Enter seat number and Audience Name:"<<endl;
                cin>>x>>y;
                if(choice==1)
                    drama.issueTicket(x,y);
                else
                    drama.cancelTicket(x,y);
            }
            break;
            case 6:
            {
                drama.displayRating();
            }
            break;
            case 7:
            {
                drama.CalculateTotalEarning();
            }
            break;
            case 8:
            {
                drama.displayDrama();
            }
            break;
            case 9:
            {
                cout<<"Hike Salary of All the Cast Members:"<<endl;
                int per;
                cout<<"Enter the Percentage "<<endl;
                cin>>per;
                for(int i=0;i<CastMember::CastMemberCount;i++)
                {
                    drama.cast[i]->HikeSalary(per);
                }
            }
            break;
            case 10:
            {
                cout<<"Hiking Rating of Cast Members based on Drama Rating/Performance:"<<endl;
                if(drama.Rating>=4)
                    drama.HikeRatings();
                else
                    cout<<"Rating is not Hiked because the performace was not good enough"<<endl;
                break;
            }
            case 11:
            {
                cout<<"Enter the audience name and Enter the ratings :"<<endl;
                int rati;
                string namme;
                cin>>namme>>rati;
                drama.giveRating(namme,rati);
            }
            break;
            case 12:
            {
                cout<<"Closing..."<<endl;
                exit(0);
            }
            break;

            default:
            cout<<"invalid choice\n";
            break;
        }
    }
    return 0;
}
