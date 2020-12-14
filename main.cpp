#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#define MAX 50
#define MAX1 5
using namespace std;

class busnode                      //class depicting information of different buses
{
	public:
    	string pname,from,to;
    	int dep,arr;
		int seatnumber;
		double busfare;
    	busnode *next;

};


class List:public busnode	    	//class depicting different buses
{
	public:
    	busnode *listptr,*temp;
    	int totseats;
};


class bus
{
  public:

        int V;
        List* array;

        void busset(int n)
        {
            V = n;
            array = new List [V];
            for (int i = 0; i < V; ++i)
            {
            	array[i].listptr = NULL;
            	array[i].temp = NULL;
			}

		}

        void setinfo(int i,string f,string t,int d,int a,int totlseats,double fare)     //Function to set details of the buses by admin
		{
        	array[i].arr=a;
        	array[i].dep=d;
        	array[i].to=t;
        	array[i].from=f;
        	array[i].totseats=totlseats;
        	array[i].busfare=fare;
		}

		void displayinfo(int busnumber)										//Function to display information of all the buses
		{
			cout<<"\n\n\nBus from: "<<array[busnumber].from;
			cout<<" to "<<array[busnumber].to;
			cout<<"\n\nDeparture time: "<<array[busnumber].dep;
			cout<<"\n\nArrival time: "<<array[busnumber].arr;
			cout<<"\n\nTotal seats : "<<array[busnumber].totseats;
			cout<<"\n\nBase fare for 1 seat Rs."<<array[busnumber].busfare;
			countseats(busnumber);
		}

        void create(int a,string name)									//Function for booking tickets by passenger
        {
      	 	busnode *newnode = new busnode;
            newnode->pname=name;
            newnode->next = NULL;
           	newnode->seatnumber=0;

            if(array[a].listptr==NULL)
            {

            	array[a].listptr=array[a].temp=newnode;
            }
            else
            {
            	array[a].temp->next=newnode;
              	array[a].temp=array[a].temp->next;
            }
        }
        void cancel(int busnum,int delseat1)           			//Function for cancellation of tickets
        {

        		int j=0;
				int i,delseat=0;
				busnode *busdel,*tem;
				busdel=array[busnum].listptr;
				tem=array[busnum].temp;
				if(delseat1==tem->seatnumber)                   //to delete the last seat
				{
					busnode *temp1,*t2;
					for(temp1=array[busnum].listptr;(temp1->next)->next!=NULL;temp1=temp1->next);
					t2=temp1->next;
					delete(t2);
					temp1->next=NULL;
					array[busnum].temp=temp1;
				}
				else
				{

					for(;busdel->seatnumber!=delseat1;delseat++,busdel=busdel->next);
					if(array[busnum].listptr==NULL)       			//to check whether a particular bus has been booked by the passenger
					{
						cout<<"\nNo tickets booked yet";
					}
					else if(delseat==0)  						   //to check deletion of first seats
					{
						busdel=array[busnum].listptr;
						array[busnum].listptr=array[busnum].listptr->next;
						delete(busdel);
					}
					else                                              //for deletion of any intermediate seats
					{
						int c=1;
						busnode *tmp1,*tmp2;
						for(tmp1=array[busnum].listptr;c<delseat-1;c++,tmp1=tmp1->next);
							tmp2=tmp1->next;

						if(tmp2->next==NULL)
						{
							array[busnum].temp=tmp1;
						}
						tmp1->next=tmp2->next;
						delete(tmp2);
					}

				}
		}

        int count(int number)                           //Function to count total numner of passengers in a particular bus
       	{
       		int i;
       		busnode *temp1;
       		string s=" ";
       		for(i=0,temp1=array[number].listptr;temp1!=NULL;temp1=temp1->next,i++);

			return i;
		}

		int countseats(int number) 						//Function for counting total number of seats in a bus
		{
			int i;
			i=count(number);
			array[number].totseats=array[number].totseats-i;
			cout<<"\n\nSeats left : "<<array[number].totseats;
		}

        void display()                                 //Function for displaying details of a particular bus along with passenger details
        {
            for (int i=0;i<V;i++)
            {
                busnode *temp1 = array[i].listptr;
                cout<<"\n:: Bus no. "<<i+1<<"::\n\n";
                while (temp1)
                {
                    cout<<"\nPassenger : "<<temp1->pname<<"\t\tSeat number: "<<temp1->seatnumber;
                    temp1 = temp1->next;
                    cout<<"\n";
                }

            }

        }
        void current_booking(int noofseats,int busno1)        //Function for displaying details of current passenger
		{
			cout<<"\n\n:: BOOKING DETAILS ::";
			int i,o=0;
        	busnode *t=array[busno1].listptr;
			i=count(busno1);
			for(t=array[busno1].listptr;(t->seatnumber)!=0;t=t->next);
			int curr=i-noofseats;
			//cout<<"Noofseats: "<<noofseats<<"\ti="<<t->seatnumber;
			if(curr==0)
			{
				while(t)
				{
					t->seatnumber=curr+1;
					cout<<"\n\nPassenger : "<<t->pname<<"\tSeat number : "<<t->seatnumber;
					t=t->next;
					curr++;
				}
			}
			else
			{
				for(o=1,t=array[busno1].listptr;o<curr+1;o++,t=t->next);
				while(t)
				{
					t->seatnumber=curr+1;
					cout<<"\nPassenger : "<<t->pname<<"\tSeat number : "<<t->seatnumber;
					t=t->next;
					curr++;
				}
			}
			cout<<"\n\nTotal Bill: Rs."<<array[busno1].busfare*noofseats;

		}

};

class choice                                        //Class for accessing users choice
{
	public:
	bus bu;
	int num;
	double fare;
	int admin()                                      //Admin function
	{
		int s,se,i,n,dep,arr,k,totlseats,rm;
    	string r,from,to;
		char ch;
		char cho,cho1;

		cout<<"\nEnter number of buses : ";
		cin>>num;
		bu.busset(num);
		cout<<"\n::ENTER BUS INFORMATION::\n ";
		for(i=0;i<num;i++)
		{
			cout<<"\nFor Bus no. :"<<i+1;
			cout<<"\n\nEnter From: ";
			cin>>from;
			cout<<"\nEnter To: ";
			cin>>to;
			cout<<"\nEnter Departure Time : ";
			cin>>dep;
			cout<<"\nEnter Arrival Time : ";
			cin>>arr;
			cout<<"\nEnter Total Number of Seats : ";
			cin>>totlseats;
			cout<<"\nEnter base fare: ";
			cin>>fare;
			bu.setinfo(i,from,to,dep,arr,totlseats,fare);
		}

		cout<<"\n\n::: DISPLAYING BUS INFORMATION :::";
		for(i=0;i<num;i++)
		{
			bu.displayinfo(i);
		}
		return num;

	}

	void user()                                                //Users function
	{
		int s,s1,se,i,n,d1,dep,arr,k,totlseats,rm,x,q=1;
    	string r,from,to;
		char ch;
		char cho,cho1;

		do
		{
			q=1;
			cout<<"\n\n::: DISPLAYING BUS INFORMATION :::";
			for(i=0;i<num;i++)
			{
				cout<<"\n\nBus number:"<<i+1;
				bu.displayinfo(i);
			}
			cout<<"\n\n\n\n\t\t      PRESS 1 FOR BOOKING TICKET  \n\t\t      PRESS 2 TO CANCEL TICKET";

			cin>>n;

			switch(n)
			{
				case 1: cout<<"\n::: BOOK TICKET :::";
						cout<<"\n\nEnter No. of Seats :";
						cin>>se;
						cout<<"\nEnter Bus Number :  ";
						cin>>s;
						s--;
						for(i=0;i<se;i++)
						{
							cout<<"\nEnter Passenger Name : ";
							cin>>r;
							bu.create(s,r);
						}

						bu.current_booking(se,s);

						break;


				case 2: cout<<"\nEnter Bus Number :";
						cin>>s1;
						s1--;

						while(q==1)
						{
							cout<<"\nEnter seat number: ";
							cin>>k;
							bu.cancel(s1,k);
							cout<<"\nSeat Number "<<k<<" is Canceled";
							cout<<"\n\nPress 1 To Cancel More Seats   : ";
							cin>>q;
						}

						cout<<"\n\n:::TICKET CANCELLATION SUCESSFUL:::";
						cout<<"\nAmount will be refunded according to cancellation policy shortly in your account ";
						break;

				case 3: bu.display();
					    break;


			}
			cout<<"\n\n\nCONTINUE WITH CUSTOMER LOGIN ??? (Y/N) :: ";
			cin>>ch;

		}while(ch=='y'||ch=='Y');
	}

};

int main()                                                //Main 0
{
	choice obj;
    int s,se,i,n,dep,arr,k,totlseats,p,rm;
    string r,from,to;
	char ch;
	char cho,cho1;
	int x;
	do
	{
		cout<<"\t\t\t*********************";
		cout<<"\n\t\t\t         MENU\n";
		cout<<"\t\t\t*********************";
		cout<<"\n\t\t              A.ADMIN\n\t\t              B.CUSTOMER\n";
		cout<<"\n\t\t              ENTER : ";
		cin>>cho;

		switch(cho)
		{
			case 'A' : 	obj.admin();
						break;

			case 'a' :	obj.admin();
		 		   		break;

	    	case 'B' : obj.user();
				  		break;

			case 'b' : obj.user();
		           		break;
		    //case 't': obj.display();
		}

	cout<<"\n\nRETURN TO MAIN MENU (PRESS Y) ";
	cin>>cho1;

	}while(cho1=='y'||cho1=='Y');

}
