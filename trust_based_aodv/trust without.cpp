#include<iostream>
#include<cstdio>
#include<stdlib.h>
#include<math.h>
#include <time.h>
#include <iomanip>
#include "trust without.h"
//#include "shortpath.cpp"

int trustrrepqueue::copy(int dip,int dseq,int sip,int hc,int oip){
			trustdelay1(trustwaitrrep);
			this->size++;
			queuepointer[size].destip=dip;
			queuepointer[size].destseq=dseq;
			queuepointer[size].sourceip=sip;
			queuepointer[size].hopcount=hc;
			queuepointer[size].originip=oip;
			
		return 1;
}

int trustrreqqueue::copy(int dip,int dseq,int sip,int sseq,int hc,int bid,int oip,float tr){
			trustdelay1(trustwaitrreq);
			this->size++;
			queuepointer[size].destip=dip;
			queuepointer[size].destseq=dseq;
			queuepointer[size].sourceip=sip;
			queuepointer[size].sourceseq=sseq;
			queuepointer[size].hopcount=hc;
			queuepointer[size].broadcastid=bid;
			queuepointer[size].originip=oip;
			queuepointer[size].trust=tr;
			
		return 1;
}


int trustnode::checkroute(int d){
		for(int i=0;i<=rtablep.entries;i++)
		{
			if(rtablep.destip[i]==d)
				return i+1;
		}
		return 0;
}

int trustnode::buildrreq(int p,int q,int hc,int bid,float tr)
	{
		
		rreqp.destip=q;
		rreqp.destseq=0;
		rreqp.sourceip=p;
		rreqp.sourceseq=0;
		rreqp.hopcount=hc+1;
		rreqp.broadcastid=bid;
		rreqp.originip=this->ip;
		rreqp.trust=tr;
	
	return 1;
}

int trustnode::buildrrep(int p,int q,int hc){
		
		rrepp.destip=q;
		rrepp.destseq=0;
		rrepp.hopcount=hc+1;
		rrepp.sourceip=p;
		rrepp.originip=this->ip;
	
	return 1;
}


trustnode trustnodep[max];

void trustinit()
{
 trusts=0;
 trustd=0;
 trustbid=0;
 trustflag=0;  
 trustrflag=0; 
 trustdone=0;
 trustnrreq=0;
 trustnrrep=0;
 trustndp=0;
 trustsdp=0;
 trustbitrate=0.0;
 trustdata=0;
 trustt=0;
for(int i=0;i<max;i++)
{
	trustnodep[i].rreqqueuep.size=-1;
	trustnodep[i].rrepqueuep.size=-1;

}
}



int trustnode::broadcast(){
	trustflag=1;
	int g=1;
	for(int i=0;i<max;i++)
	{
		g=1;
		if(trustnodegraph[this->ip][i]==1)
		{

		for(int k=0;k<=rtablep.entries;k++)  //check for path to source
		{
			if(rtablep.destip[k]==trustnodep[i].ip)
			{
				
				if(rtablep.trust[k]>=mintrust){
				
				if(ip==trusts){			//decrement the trust at source
					
				rtablep.trust[k]=rtablep.trust[k]-subtrust;
				}				
				rreqp.trust=(rreqp.trust+rtablep.trust[k])/2; 
				g=1;
				}
				else 
					g=0;
				break;	
			}
		}
		if(g){
			trustnrreq++;
			trustnodep[i].rreqqueuep.copy(rreqp.destip,rreqp.destseq,rreqp.sourceip,rreqp.sourceseq,rreqp.hopcount,rreqp.broadcastid,rreqp.originip,rreqp.trust);
		//cout<<"Broadcasted from "<<ip<<" to "<<trustnodep[i].ip<<"\n";
		}
		}

	}
	return 1;
	}

int trustprocessnodes()
{
	for(int i=0;i<max;i++)
	{
		//cout<<"\n###Processing queue at node:"<<nodep[i].ip<<"\n";


		if(trustnodep[i].rreqqueuep.size==-1)
		{
			//cout<<"\tQueue empty.\n";
			continue;
		}
		else{
			int dflag=0;
			for(int j=0;j<=trustnodep[i].rreqqueuep.size;j++)
			{
				int g=1;  //flag to check duplicate requests
				
				for(int z=j-1;z>=0;z--)
				{    //checking duplicate requests
					if(trustnodep[i].rreqqueuep.queuepointer[z].broadcastid==trustnodep[i].rreqqueuep.queuepointer[j].broadcastid)
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
				int k=0;
				g=1;
				if(trustnodep[i].ip!=trustnodep[i].rreqqueuep.queuepointer[j].sourceip)
				{
								
				for(k=0;k<=trustnodep[i].rtablep.entries;k++)  //check for path to source
				{
					if(trustnodep[i].rtablep.destip[k]==trustnodep[i].rreqqueuep.queuepointer[j].sourceip)
					{
						if(trustnodep[i].rtablep.hopcount[k]>=trustnodep[i].rreqqueuep.queuepointer[j].hopcount)
						{
							trustnodep[i].rtablep.hopcount[k]=trustnodep[i].rreqqueuep.queuepointer[j].hopcount+1;
							trustnodep[i].rtablep.nexthop[k]=trustnodep[i].rreqqueuep.queuepointer[j].originip;
							trustnodep[i].rtablep.trust[k]=deftrust;
							trustnodep[i].rtablep.ttl[k]=dttl;
						}
						g=0;
					}
				}
				if(g==1)  //back tracing
				{

					//cout<<"\tBacktracking...\n"<<"Dest: "<<trustnodep[i].rreqqueuep.queuepointer[j].sourceip<<"Next hop: "<<trustnodep[i].rreqqueuep.queuepointer[j].originip<<"\n";
					k=trustnodep[i].rtablep.entries;
					trustnodep[i].rtablep.entries++;
					trustnodep[i].rtablep.destip[k+1]=trustnodep[i].rreqqueuep.queuepointer[j].sourceip;
					trustnodep[i].rtablep.hopcount[k+1]=trustnodep[i].rreqqueuep.queuepointer[j].hopcount+1;
					trustnodep[i].rtablep.seqno[k+1]=trustnodep[i].rreqqueuep.queuepointer[j].sourceseq;
					trustnodep[i].rtablep.nexthop[k+1]=trustnodep[i].rreqqueuep.queuepointer[j].originip;
					trustnodep[i].rtablep.trust[k+1]=deftrust;		
					trustnodep[i].rtablep.ttl[k+1]=dttl;

				}
			}

				if(trustnodep[i].ip==trustnodep[i].rreqqueuep.queuepointer[j].destip)  //at dest getting max trust rreq packet
				{	
					int psize=0,tempbid=trustnodep[i].rreqqueuep.queuepointer[j].broadcastid;
					float temptrust=0;
					for(int z=j;z<=trustnodep[i].rreqqueuep.size;z++)
					{
						if((trustnodep[i].rreqqueuep.queuepointer[j].trust>temptrust)&&(tempbid==trustnodep[i].rreqqueuep.queuepointer[z].broadcastid))
						{
							temptrust=trustnodep[i].rreqqueuep.queuepointer[j].trust;
							psize=z;
						}	
					}
					

						trustflag=1;
						trustrflag=1;
						trustnodep[i].buildrrep(trusts,trustnodep[i].rreqqueuep.queuepointer[j].destip,-1);
					//	cout<<"\tPath found at dest node.\n";
trustnodep[trustnodep[i].rreqqueuep.queuepointer[psize].originip].rrepqueuep.copy(trustnodep[i].rrepp.destip,0,trustnodep[i].rrepp.sourceip,trustnodep[i].rrepp.hopcount,trustnodep[i].rrepp.originip);
						trustnrrep++;
						//return 1;
						g=0;		
						//cout<<"\tRREP packet sent by dest\n";				
				}





				else{
				//cout<<"\tChecking for path in routing table...\n";
				g=1;
				for(k=0;k<=trustnodep[i].rtablep.entries;k++)  //check for dest ip in routing table
				{

					if(trustnodep[i].rtablep.destip[k]== trustnodep[i].rreqqueuep.queuepointer[j].destip)
					{	//path found in intermediate node
						trustflag=1;
						trustrflag=1;
						trustnodep[i].buildrrep(trusts,trustnodep[i].rreqqueuep.queuepointer[j].destip,trustnodep[i].rtablep.hopcount[k]);
						
					//cout<<"\tPath found at interm node:"<<i<<"\n";
trustnodep[trustnodep[i].rreqqueuep.queuepointer[j].originip].rrepqueuep.copy(trustnodep[i].rrepp.destip,0,trustnodep[i].rrepp.sourceip,trustnodep[i].rrepp.hopcount,trustnodep[i].rrepp.originip);
						trustnrrep++;
						//return 1;
						g=0;
						//cout<<"\tRREP packet sent\n";
						break;
					}
/*
					else if(nodep[i].ip==nodep[i].rreqqueuep.queuepointer[j].destip)
					{	//path found in destination node
						flag=1;
						rflag=1;
						nodep[i].buildrrep(s,nodep[i].rreqqueuep.queuepointer[j].destip,-1);
						cout<<"\tPath found at dest node.\n";
nodep[nodep[i].rreqqueuep.queuepointer[j].originip].rrepqueuep.copy(nodep[i].rrepp.destip,0,nodep[i].rrepp.sourceip,nodep[i].rrepp.hopcount,nodep[i].rrepp.originip);
						nrrep++;
						//return 1;
						g=0;		
						cout<<"\tRREP packet sent by dest\n";				
						break;
						
					}*/

			

				}
				}
					if(g==1)
					{
					//cout<<"\tPath not found in routing table...\n";
					//cout<<"\tBroadcasting RREQ packets...\n";
					
					trustnodep[i].buildrreq(trusts,trustd,trustnodep[i].rreqqueuep.queuepointer[j].hopcount,trustbid,trustnodep[i].rreqqueuep.queuepointer[j].trust);
					trustnodep[i].broadcast();
					}
				
				
			
			}
			//cout<<"\tDuplicate RREQ's: "<<dflag<<"\n";
			trustnodep[i].rreqqueuep.size=-1;
		}
	}
	

return 1;
}

int trustprocessrrep()
{
	
	for(int i=0;i<max;i++)
	{
		//cout<<"##Processing rrep queue at node: "<<i<<"source: "<<trusts<<"Dest: "<<trustd<<"\n";
		if(trustnodep[i].rrepqueuep.size==-1)
		{
			//cout<<"Queue empty\n";
			continue;
		}
		else{

			for(int j=0;j<=trustnodep[i].rrepqueuep.size;j++)
			{
				//if(trustnodep[i].ip==trustnodep[i].rrepqueuep.queuepointer[j].destip)
					//continue;
				int g=1;
				for(int k=0;k<=trustnodep[i].rtablep.entries;k++)  //check for path to dest if already exists
				{
					if(trustnodep[i].rtablep.destip[k]==trustnodep[i].rrepqueuep.queuepointer[j].destip)
					{
						if(trustnodep[i].rtablep.hopcount[k]>=trustnodep[i].rrepqueuep.queuepointer[j].hopcount)
						{
							trustnodep[i].rtablep.hopcount[k]=trustnodep[i].rrepqueuep.queuepointer[j].hopcount+1;
							trustnodep[i].rtablep.nexthop[k]=trustnodep[i].rrepqueuep.queuepointer[j].originip;
							trustnodep[i].rtablep.ttl[k]=dttl;
						}
						g=0;
					}
				}
								
				
				if(trustnodep[i].ip==trustnodep[i].rrepqueuep.queuepointer[j].sourceip)
					{	
						trustflag=0;
						trustrflag=0;
						//cout<<"Path found at node:"<<i<<"dest:"<<nodep[i].rreqqueuep.queuepointer[j].destip<<"\n";
						if(g==1)
						{	

						g=trustnodep[i].rtablep.entries;
						trustnodep[i].rtablep.entries++;
						trustnodep[i].rtablep.destip[g+1]=trustnodep[i].rrepqueuep.queuepointer[j].destip;
						trustnodep[i].rtablep.hopcount[g+1]=trustnodep[i].rrepqueuep.queuepointer[j].hopcount+1;
						trustnodep[i].rtablep.seqno[g+1]=trustnodep[i].rrepqueuep.queuepointer[j].destseq;
						trustnodep[i].rtablep.nexthop[g+1]=trustnodep[i].rrepqueuep.queuepointer[j].originip;
						trustnodep[i].rtablep.ttl[g+1]=dttl;
						
						}
						trustnodep[i].rtablep.trust[trustnodep[i].rrepqueuep.queuepointer[j].originip]+=subtrust;
						//cout<<"\nRREP at source node:\n";
						trustdone=1;
						trusthopsum[++trustshopsum]=trustnodep[i].rtablep.hopcount[g+1];
						return 1;
					}


				//cout<<"\nRREP at interm node:"<<nodep[i].ip<<"\n";
				for(int k=0;k<=trustnodep[i].rtablep.entries;k++)  //check for dest ip in routing table
				{
					if(trustnodep[i].rtablep.destip[k]== trustnodep[i].rrepqueuep.queuepointer[j].sourceip)
					{	//path found in intermediate node
						trustflag=1;
						trustrflag=1;
				//cout<<"\tunicasting RREP packet...to: "<<trustnodep[i].rtablep.nexthop[k]<<"\n";
				trustnodep[i].buildrrep(trusts,trustnodep[i].rreqqueuep.queuepointer[j].destip,trustnodep[i].rrepqueuep.queuepointer[j].hopcount);

				
trustnodep[trustnodep[i].rtablep.nexthop[k]].rrepqueuep.copy(trustnodep[i].rrepp.destip,0,trustnodep[i].rrepp.sourceip,trustnodep[i].rrepp.hopcount,trustnodep[i].rrepp.originip);
				trustnrrep++;
					}
				}

				if(g==1)
				{					
					g=trustnodep[i].rtablep.entries;
					trustnodep[i].rtablep.entries++;
					trustnodep[i].rtablep.destip[g+1]=trustnodep[i].rrepqueuep.queuepointer[j].destip;
					trustnodep[i].rtablep.hopcount[g+1]=trustnodep[i].rrepqueuep.queuepointer[j].hopcount+1;
					trustnodep[i].rtablep.seqno[g+1]=trustnodep[i].rrepqueuep.queuepointer[j].destseq;
					trustnodep[i].rtablep.nexthop[g+1]=trustnodep[i].rrepqueuep.queuepointer[j].originip;
					trustnodep[i].rtablep.ttl[g+1]=dttl;
					
				}
					
			
			}
			trustnodep[i].rrepqueuep.size=-1;
		}
	}



return 1;
}

void trustdelay1(double p){
clock_t q;
q=clock();
//while(((clock()-q)/(double) CLOCKS_PER_SEC)<=p);
}
