#define max 25
#define srreq 24
#define srrep 20
#define srack 2
#define maxcom 10000
#define dttl 150
#define sttl 10
using namespace std;
//freopen("/my/newstdin", "r", stdin);

clock_t t1,t2;
//int nodegraph[max][max]={{0,1,1,0,0},{1,0,1,1,0},{1,1,0,0,0},{0,1,0,0,1},{0,0,0,1,0}};
int nodegraph[max][max];
int s,d,bid;
int flag=0;  //flag for complete broadcast check
int rflag=0; //flag to check for rrep packets
int done=0;
int nrreq=0;
int nrrep=0;
int ndp=0;
int sdp=0;
int times=0;
double bitrate=0.0,data=0,tdata=0,t;
double normalload[maxcom]={0},timetaken[maxcom]={0},overhead[maxcom]={0},hopsum[maxcom]={0},datasent[maxcom]={0};
int source[maxcom]={0},destination[maxcom]={0};
int snormalload=-1,stimetaken=-1,soverhead=-1,shopsum=-1,ssource=-1,sdestination=-1,sdatasent=-1;
double waitrreq=0,waitrrep=0;

class rreq
{
	public:
		int destip,destseq;
		int sourceip,sourceseq;
		int hopcount;
		int broadcastid;
		int originip;
};

class rrep
{
	public:
	int destip,destseq;
	int sourceip;
	int originip;
	int hopcount;
};

class rrepqueue
{
	public:
		int size;
		rrep* queuepointer;
		rrepqueue(){
		size=-1;
		queuepointer=new rrep[maxcom];
		}
		int copy(int dip,int dseq,int sip,int hc,int oip);
};

class rreqqueue
{
	public:
		int size;
		rreq* queuepointer;
		rreqqueue(){
		size=-1;
		queuepointer=new rreq[maxcom];
		}
		int copy(int dip,int dseq,int sip,int sseq,int hc,int bid,int oip);
};

class rtable
{
public:
	int entries;
	int destip[max],hopcount[max];
	int seqno[max],nexthop[max];
	int ttl[max];
	rtable(){
		for(int i=0;i<max;i++)
		{
			destip[i]=-1;
			hopcount[i]=-1;
			seqno[i]=-1;
			nexthop[i]=-1;
			entries=-1;
			ttl[i]=-1;
		}
	}	
};

void init();
void delay1(double);

class node
{
public:
	int ip;
	rreqqueue rreqqueuep;
	rrepqueue rrepqueuep;
	rtable rtablep;
	rreq rreqp;
	rrep rrepp;

	void read(int k){
	this->ip=k;}	

	int checkroute(int d);
	int buildrreq(int p,int q,int hc,int bid);
	int buildrrep(int p,int q,int hc);
	int broadcast();
};	

int processnodes();
int processrrep();
