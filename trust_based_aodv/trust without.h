#define max 25
#define trustsrreq 24
#define trustsrrep 20
#define trustsrack 2
#define mintrust 0.4
#define deftrust 0.5
#define subtrust 0.05
#define trustmaxcom 10000
#define dttl 150
#define sttl 10
#define maxqueue 40
using namespace std;
//freopen("/my/newstdin", "r", stdin);

clock_t trustt1,trustt2;
//int nodegraph[max][max]={{0,1,1,0,0},{1,0,1,1,0},{1,1,0,0,0},{0,1,0,0,1},{0,0,0,1,0}};
int trustnodegraph[max][max];
int trusts,trustd,trustbid;
int trustflag=0;  //flag for complete broadcast check
int trustrflag=0; //flag to check for rrep packets
int trustdone=0;
int trustnrreq=0;
int trustnrrep=0;
int trustndp=0;
int trustsdp=0;
int trusttimes=0;
double trustbitrate=0.0,trustdata=0,trusttdata=0,trustt;

double trustnormalload[trustmaxcom]={0},trusttimetaken[trustmaxcom]={0},trustoverhead[trustmaxcom]={0},trusthopsum[trustmaxcom]={0},trustdatasent[trustmaxcom]={0};
int trustsource[trustmaxcom]={0},trustdestination[trustmaxcom]={0},trustssource=-1,trustsdestination=-1,trustsdatasent=-1;;
int trustsnormalload=-1,truststimetaken=-1,trustsoverhead=-1,trustshopsum=-1;
double trustwaitrreq=0,trustwaitrrep=0;

class trustrreq
{
	public:
		int destip,destseq;
		int sourceip,sourceseq;
		int hopcount;
		int broadcastid;
		int originip;
		float trust;
	trustrreq(){
		trust=deftrust;
	}
};

class trustrrep
{
	public:
	int destip,destseq;
	int sourceip;
	int originip;
	int hopcount;
};

class trustrrepqueue
{
	public:
		int size;
		trustrrep* queuepointer;
		trustrrepqueue(){
		size=-1;
		queuepointer=new trustrrep[maxqueue];
		}
		int copy(int dip,int dseq,int sip,int hc,int oip);
};

class trustrreqqueue
{
	public:
		int size;
		trustrreq* queuepointer;
		trustrreqqueue(){
		size=-1;
		queuepointer=new trustrreq[maxqueue];
		}
		int copy(int dip,int dseq,int sip,int sseq,int hc,int bid,int oip,float tr);
};

class trustrtable
{
public:
	int entries;
	int destip[max],hopcount[max];
	int seqno[max],nexthop[max];
	float trust[max];
	int ttl[max];
	trustrtable(){
	for(int i=0;i<max;i++)
	{
		destip[i]=-1;
		hopcount[i]=-1;
		seqno[i]=-1;
		nexthop[i]=-1;
		entries=-1;
		trust[i]=deftrust;
		ttl[i]=-1;
	}
	}	
};

void trustinit();
void trustdelay1(double);

class trustnode
{
public:
	int ip;
	trustrreqqueue rreqqueuep;
	trustrrepqueue rrepqueuep;
	trustrtable rtablep;
	trustrreq rreqp;
	trustrrep rrepp;

	void read(int k){
	this->ip=k;}	

	int checkroute(int d);
	int buildrreq(int p,int q,int hc,int bid,float tr);
	int buildrrep(int p,int q,int hc);
	int broadcast();
};	


int trustprocessnodes();
int trustprocessrrep();
