#include <ross.h>

#define TW_MAX_NAME_LEN 31

/* 2D grid */
#define NUM_CELLS_X 32     //256
#define NUM_CELLS_Y 32     //256

/* overlapping grid that divides 2D grid above into sections 
each processor gets a section
ex. splitting x and y in half creates four quadrants, 
one quadrant for each processor */

#define NUM_VP_X 4 
#define NUM_VP_Y 4

typedef int     Channel_t;
typedef int     Min_t;
typedef int     MethodName_t;

// CASE_NAME [case number]
#define UPDATE_METHOD 0
#define PREY_DIE 1
#define PREDATOR_DIE 2

#define CELL_TICK 1.0

/********* User Entity Classes ******************************************/

/* define state of "cell"
number of predators, number of prey, number of grass */
struct State
{
	double          Const_State_1;
	int             Const_State_2;
	int             Normal_Channels;
	int             Reserve_Channels;
	int             Portables_In;
	int             Portables_Out;
	int             Call_Attempts;
	int             Channel_Blocks;
	int             Busy_Lines;
	int             Handoff_Blocks;
	int             CellLocationX;
	int             CellLocationY;
	//initializing Predator, Prey, Grass
	int 	Predator;
	int 	Prey;
	int 	Grass;
};

/* reverse computing */ 
struct RC
{
	int             wl1;	
	//Reverse compute Predator, Prey, Grass
	int 	Predator;
	int 	Prey;
	int 	Grass;
};

/* ex. when prey or predator leaves space - send message
arrival prey / arrival predator and associated health factor */
struct Msg_Data
{
	MethodName_t    MethodName;
	double          CompletionCallTS;
	double          NextCallTS;
	double          MoveCallTS;
	Channel_t       ChannelType;
	struct RC       RC;
};

/* stats on the entire world
ex. number of predator that died, number of prey that died */ 
struct CellStatistics
{
	int             Call_Attempts;
	int             Channel_Blocks;
	int             Busy_Lines;
	int             Handoff_Blocks;
	int             Portables_In;
	int             Portables_Out;
	double          Blocking_Probability;

  //add statistic variables to print here
        int             Grass;
  
};

/* event handlers 
need to define my own 
ex. predator arrival, prey arrival, update cell */
tw_lpid         Cell_ComputeMove( tw_lpid lpid, int direction );
tw_peid         CellMapping_lp_to_pe(tw_lpid lpid);
tw_lp          *CellMapping_to_lp(tw_lpid lpid);
tw_lpid         CellMapping_to_local_index(tw_lpid lpid);
  
void            Cell_Init(struct State *SV, tw_lp * lp);
void            Cell_EventHandler(struct State *SV, tw_bf * CV, struct Msg_Data *M, tw_lp * lp);
void         RC_Cell_EventHandler(struct State *SV, tw_bf * CV, struct Msg_Data *M, tw_lp * lp);

void            CellStatistics_CollectStats(struct State *, tw_lp *lp);
void            CellStatistics_Compute();
void            CellStatistics_Print();

/* declares CellStats - makes it global to the model */
struct CellStatistics TWAppStats;
tw_lpid nlp_per_pe = 0; //global variable - determines how many LPs are there per MPI rank