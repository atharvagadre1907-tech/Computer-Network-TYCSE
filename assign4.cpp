#include <iostream>
#include <vector>
#define n 4
#define infi 999
using namespace std;
class DistRouting
{
    private:
    vector <vector<int>> cost;
    vector <vector<int>> dist;
    vector <vector<int>> nextHop;
    public:
    DistRouting(): cost(n, vector<int>(n, infi)), dist(n, vector<int>(n)), nextHop(n, vector<int>(n))
    {
    }
    void setCost()
    {
        int c;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<=i; j++)
            {
                cout<<"\nEnter cost from node "<<i<<" to "<<j<<": ";
                cin>>c;
                cost[i][j]=c;
                cost[j][i]=c;
            }
        }
    }
    void setDistance()
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                dist[i][j]=cost[i][j];
                if(i==j)
                {
                    nextHop[i][j]=i;
                }
                else if(cost[i][j]!=infi)
                {
                    nextHop[i][j]=j;
                }
                else
                {
                    nextHop[i][j]=-1;
                }
            }
        }
    }

    void updateDistance()
    {
        int update=0;
        while(update==0)
        {
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<n; j++)
                {
                    for(int k=0; k<n; k++)
                    {
                        if((dist[i][k]!=infi) && (dist[k][j]!=infi) && (dist[i][j]>dist[i][k]+dist[k][j]))
                        {
                            dist[i][j]=dist[i][k]+dist[k][j];
                            nextHop[i][j]=nextHop[i][k];
                            update=1;
                        }
                    }
                }
            }
        }
    }

    void displayRoutingTable()
    {
        for(int i=0; i<n; i++)
        {
            cout<<"\nRouting table for router "<<i<<" is:\n";
            for(int j=0; j<n; j++)
            {
                cout<<i<<j<<dist[i][j]<<nextHop[i][j]<<endl;
            }
            cout<<"-------------------------";
        }
    }
};

int main()
{
    DistRouting d1;
    d1.setCost();
    d1.setDistance();
    d1.updateDistance();
    d1.displayRoutingTable();
    return 0;
}
