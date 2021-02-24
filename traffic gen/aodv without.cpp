
#include<iostream>
#include<cstdio>
#include<stdlib.h>
#include<math.h>
#include <time.h>
#include <iomanip>
#include "aodv without.h"
#include "shortpath.cpp"



int rrepqueue::copy(int dip,int dseq,int sip,int hc,int oip){
			delay1(waitrrep);
			this->size++;
			queuepointer[size].destip=dip;
			queuepointer[size].destseq=dseq;
			queuepointer[size].sourceip=sip;
			queuepointer[size].hopcount=hc;
			queuepointer[size].originip=oip;
			
		return 1;
}


int rreqqueue::copy(int dip,int dseq,int sip,int sseq,int hc,int bid,int oip){
			delay1(waitrreq);
			this->size++;
			queuepointer[size].destip=dip;
			queuepointer[size].destseq=dseq;
			queuepointer[size].sourceip=sip;
			queuepointer[size].sourceseq=sseq;
			queuepointer[size].hopcount=hc;
			queuepointer[size].broadcastid=bid;
			queuepointer[size].originip=oip;
			
		return 1;
		}


int node::checkroute(int d){
for(int i=0;i<max;i++)
		{
			if(rtablep.destip[i]==d)
				return i+1;
		}
		return 0;
	}

int node::buildrreq(int p,int q,int hc,int bid)
	{
		
		rreqp.destip=q;
		rreqp.destseq=0;
		rreqp.sourceip=p;
		rreqp.sourceseq=0;
		rreqp.hopcount=hc+1;
		rreqp.broadcastid=bid;
		rreqp.originip=this->ip;
	
	return 1;
	}

int node::buildrrep(int p,int q,int hc){
		
		rrepp.destip=q;
		rrepp.destseq=0;
		rrepp.hopcount=hc+1;
		rrepp.sourceip=p;
		rrepp.originip=this->ip;
	
	return 1;
	}


node nodep[max];

void init()
{
 s=0;
 d=0;
 bid=0;
 flag=0;  
 rflag=0; 
 done=0;
 nrreq=0;
 nrrep=0;
 ndp=0;
 sdp=0;
 bitrate=0.0;
 data=0;
 t=0;
for(int i=0;i<max;i++)
{
	nodep[i].rreqqueuep.size=-1;
	nodep[i].rrepqueuep.size=-1;

}
}



int node::broadcast(){
	flag=1;
	for(int i=0;i<max;i++)
	{
		if(nodegraph[this->ip][i]==1)
		{
			nrreq++;
						
		nodep[i].rreqqueuep.copy(rreqp.destip,rreqp.destseq,rreqp.sourceip,rreqp.sourceseq,rreqp.hopcount,rreqp.broadcastid,rreqp.originip);
		}

	}
	return 1;
	}

int processnodes()
{
	for(int i=0;i<max;i++)
	{
		//cout<<"\n###Processing queue at node:"<<nodep[i].ip<<"\n";


		if(nodep[i].rreqqueuep.size==-1)
		{
			//cout<<"\tQueue empty.\n";
			continue;
		}
		else{
			int dflag=0;
			for(int j=0;j<=nodep[i].rreqqueuep.size;j++)
			{
				int g=1;  //flag to check duplicate requests
				
				for(int z=j-1;z>=0;z--)
				{    //checking duplicate requests
					if(nodep[i].rreqqueuep.queuepointer[z].broadcastid==nodep[i].rreqqueuep.queuepointer[j].broadcastid)
					{
						
						g=0;
						break;
					}

				}
				
				if(g==0)
				{
					
					dflag++;
					continue;  //skipping duplicate requests
				}

				g=1;
				int k=0;
				for(k=0;k<=nodep[i].rtablep.entries;k++)  //check for path to source
				{
					if(nodep[i].rtablep.destip[k]==nodep[i].rreqqueuep.queuepointer[j].sourceip)
					{
						if(nodep[i].rtablep.hopcount[k]>=nodep[i].rreqqueuep.queuepointer[j].hopcount)
						{
							nodep[i].rtablep.hopcount[k]=nodep[i].rreqqueuep.queuepointer[j].hopcount+1;
							nodep[i].rtablep.nexthop[k]=nodep[i].rreqqueuep.queuepointer[j].originip;
						}
						g=0;
					}
				}
				if(g==1)  //back tracing
				{
					//cout<<"\tBacktracking...\n";
					k=nodep[i].rtablep.entries;
					nodep[i].rtablep.entries++;
					nodep[i].rtablep.destip[k+1]=nodep[i].rreqqueuep.queuepointer[j].sourceip;
					nodep[i].rtablep.hopcount[k+1]=nodep[i].rreqqueuep.queuepointer[j].hopcount+1;
					nodep[i].rtablep.seqno[k+1]=nodep[i].rreqqueuep.queuepointer[j].sourceseq;
					nodep[i].rtablep.nexthop[k+1]=nodep[i].rreqqueuep.queuepointer[j].originip;
					
				}
				//cout<<"\tChecking for path in routing table...\n";
				g=1;
				for(k=0;k<=nodep[i].rtablep.entries;k++)  //check for dest ip in routing table
				{

					if(nodep[i].rtablep.destip[k]== nodep[i].rreqqueuep.queuepointer[j].destip)
					{	//path found in intermediate node
						flag=1;
						rflag=1;
						nodep[i].buildrrep(s,nodep[i].rreqqueuep.queuepointer[j].destip,nodep[i].rtablep.hopcount[k]);
						
					//cout<<"\tPath found at interm node:"<<i<<"\n";
nodep[nodep[i].rreqqueuep.queuepointer[j].originip].rrepqueuep.copy(nodep[i].rrepp.destip,0,nodep[i].rrepp.sourceip,nodep[i].rrepp.hopcount,nodep[i].rrepp.originip);
						nrrep++;
						//return 1;
						g=0;
						//cout<<"\tRREP packet sent\n";
						break;
					}

					else if(nodep[i].ip==nodep[i].rreqqueuep.queuepointer[j].destip)
					{	//path found in destination node
						flag=1;
						rflag=1;
						nodep[i].buildrrep(s,nodep[i].rreqqueuep.queuepointer[j].destip,-1);
						//cout<<"\tPath found at dest node.\n";
nodep[nodep[i].rreqqueuep.queuepointer[j].originip].rrepqueuep.copy(nodep[i].rrepp.destip,0,nodep[i].rrepp.sourceip,nodep[i].rrepp.hopcount,nodep[i].rrepp.originip);
						nrrep++;
						//return 1;
						g=0;		
						//cout<<"\tRREP packet sent by dest\n";				
						break;
						
					}

			

				}
					if(g==1)
					{
					//cout<<"\tPath not found in routing table...\n";
					//cout<<"\tBroadcasting RREQ packets...\n";
					
					nodep[i].buildrreq(s,d,nodep[i].rreqqueuep.queuepointer[j].hopcount,bid);
					nodep[i].broadcast();
					}
				
				
			
			}
			//cout<<"\tDuplicate RREQ's: "<<dflag<<"\n";
			nodep[i].rreqqueuep.size=-1;
		}
	}

return 1;
}

int processrrep()
{
	for(int i=0;i<max;i++)
	{
		if(nodep[i].rrepqueuep.size==-1)
		{
			continue;
		}
		else{
			for(int j=0;j<=nodep[i].rrepqueuep.size;j++)
			{
				
				int g=1;
				for(int k=0;k<=nodep[i].rtablep.entries;k++)  //check for path to dest if already exists
				{
					if(nodep[i].rtablep.destip[k]==nodep[i].rrepqueuep.queuepointer[j].destip)
					{
						if(nodep[i].rtablep.hopcount[k]>=nodep[i].rrepqueuep.queuepointer[j].hopcount)
						{
							nodep[i].rtablep.hopcount[k]=nodep[i].rrepqueuep.queuepointer[j].hopcount+1;
							nodep[i].rtablep.nexthop[k]=nodep[i].rrepqueuep.queuepointer[j].originip;
						}
						g=0;
					}
				}
								
				
				if(nodep[i].ip==nodep[i].rrepqueuep.queuepointer[j].sourceip)
					{	//path found in destination node
						flag=0;
						rflag=0;
						
						if(g==1)
						{	
						g=nodep[i].rtablep.entries;
						nodep[i].rtablep.entries++;
						nodep[i].rtablep.destip[g+1]=nodep[i].rrepqueuep.queuepointer[j].destip;
						nodep[i].rtablep.hopcount[g+1]=nodep[i].rrepqueuep.queuepointer[j].hopcount+1;
						nodep[i].rtablep.seqno[g+1]=nodep[i].rrepqueuep.queuepointer[j].destseq;
						nodep[i].rtablep.nexthop[g+1]=nodep[i].rrepqueuep.queuepointer[j].originip;
						}
						//cout<<"\nRREP at source node:\n";
						done=1;
						hopsum[++shopsum]=nodep[i].rtablep.hopcount[g+1];

	//cout<<"\nsource: "<< nodep[i].ip+1<<"  dest: "<< nodep[i].rtablep.destip[g+1]+1<<"  hop: "<<nodep[i].rtablep.hopcount[g+1]<<"   "<<nodep[i].rrepqueuep.queuepointer[j].hopcount+1<<"\n";
						return 1;
					}


				//cout<<"\nRREP at interm node:"<<nodep[i].ip<<"\n";
				for(int k=0;k<=nodep[i].rtablep.entries;k++)  //check for dest ip in routing table
				{
					if(nodep[i].rtablep.destip[k]== nodep[i].rrepqueuep.queuepointer[j].sourceip)
					{	//path found in intermediate node
						flag=1;
						rflag=1;
				//cout<<"\tunicasting RREP packet...\n";
				nodep[i].buildrrep(s,nodep[i].rreqqueuep.queuepointer[j].destip,nodep[i].rrepqueuep.queuepointer[j].hopcount);

				
nodep[nodep[i].rtablep.nexthop[k]].rrepqueuep.copy(nodep[i].rrepp.destip,0,nodep[i].rrepp.sourceip,nodep[i].rrepp.hopcount,nodep[i].rrepp.originip);
				nrrep++;
					}
				}

				if(g==1)
				{					
					g=nodep[i].rtablep.entries;
					nodep[i].rtablep.entries++;
					nodep[i].rtablep.destip[g+1]=nodep[i].rrepqueuep.queuepointer[j].destip;
					nodep[i].rtablep.hopcount[g+1]=nodep[i].rrepqueuep.queuepointer[j].hopcount+1;
					nodep[i].rtablep.seqno[g+1]=nodep[i].rrepqueuep.queuepointer[j].destseq;
					nodep[i].rtablep.nexthop[g+1]=nodep[i].rrepqueuep.queuepointer[j].originip;
					
				}
					
			
			}
			nodep[i].rrepqueuep.size=-1;
		}
	}



return 1;
}

void delay1(double p){
clock_t q;
q=clock();
//while(((clock()-q)/(double) CLOCKS_PER_SEC)<=p);
}




