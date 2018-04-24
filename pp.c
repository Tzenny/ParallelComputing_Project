#include "pp.h"

tw_lpid g_vp_per_proc =0; // set in main
tw_lpid g_cells_per_vp_x = NUM_CELLS_X/NUM_VP_X;
tw_lpid g_cells_per_vp_y = NUM_CELLS_Y/NUM_VP_Y;
tw_lpid g_cells_per_vp = (NUM_CELLS_X/NUM_VP_X)*(NUM_CELLS_Y/NUM_VP_Y);

tw_lpid Cell_ComputeMove( tw_lpid lpid, int direction )
{
  tw_lpid lpid_x, lpid_y;
  tw_lpid n_x, n_y;
  tw_lpid dest_lpid;

  lpid_y = lpid / NUM_CELLS_X;
  lpid_x = lpid - (lpid_y * NUM_CELLS_X);

  switch( direction )
    {
    case 0: // SOUTH
      n_x = ((lpid_x - 1) + NUM_CELLS_X) % NUM_CELLS_X;
      n_y = lpid_y;
      break;

    case 1: // NORTH
      n_x = (lpid_x + 1) % NUM_CELLS_X;
      n_y = lpid_y;
      break;

    case 2: // EAST
      n_x = lpid_x;
      n_y = ((lpid_y - 1) + NUM_CELLS_Y) % NUM_CELLS_Y;
      break;

    case 3: // WEST
      n_x = lpid_x;
      n_y = (lpid_y + 1) % NUM_CELLS_Y;
      break;

    default:
      tw_error( TW_LOC, "Bad direction value \n");
    }

  dest_lpid = (tw_lpid) (n_x + (n_y * NUM_CELLS_X));
  // printf("ComputeMove: Src LP %llu (%d, %d), Dir %u, Dest LP %llu (%d, %d)\n", lpid, lpid_x, lpid_y, direction, dest_lpid, n_x, n_y);
  return( dest_lpid );
}

tw_peid CellMapping_lp_to_pe(tw_lpid lpid)
{
  long lp_x = lpid % NUM_CELLS_X;
  long lp_y = lpid / NUM_CELLS_X;
  long vp_num_x = lp_x/g_cells_per_vp_x;
  long vp_num_y = lp_y/g_cells_per_vp_y;
  long vp_num = vp_num_x + (vp_num_y*NUM_VP_X);
  tw_peid peid = vp_num/g_vp_per_proc;
  return peid;
}

tw_lp *CellMapping_to_lp(tw_lpid lpid)
{
  tw_lpid lp_x = lpid % NUM_CELLS_X; //lpid -> (lp_x,lp_y)
  tw_lpid lp_y = lpid / NUM_CELLS_X;
  tw_lpid vp_index_x = lp_x % g_cells_per_vp_x;
  tw_lpid vp_index_y = lp_y % g_cells_per_vp_y;
  tw_lpid vp_index = vp_index_x + (vp_index_y * (g_cells_per_vp_x));
  tw_lpid vp_num_x = lp_x/g_cells_per_vp_x;
  tw_lpid vp_num_y = lp_y/g_cells_per_vp_y;
  tw_lpid vp_num = vp_num_x + (vp_num_y*NUM_VP_X);
  vp_num = vp_num % g_vp_per_proc;
  tw_lpid index = vp_index + vp_num*g_cells_per_vp;

#ifdef ROSS_runtime_check
  if( index >= g_tw_nlp )
    tw_error(TW_LOC, "index (%llu) beyond g_tw_nlp (%llu) range \n", index, g_tw_nlp);
#endif /* ROSS_runtime_check */

  return g_tw_lp[index];
}

tw_lpid CellMapping_to_local_index(tw_lpid lpid)
{
  tw_lpid lp_x = lpid % NUM_CELLS_X; //lpid -> (lp_x,lp_y)
  tw_lpid lp_y = lpid / NUM_CELLS_X;
  tw_lpid vp_index_x = lp_x % g_cells_per_vp_x;
  tw_lpid vp_index_y = lp_y % g_cells_per_vp_y;
  tw_lpid vp_index = vp_index_x + (vp_index_y * (g_cells_per_vp_x));
  tw_lpid vp_num_x = lp_x/g_cells_per_vp_x;
  tw_lpid vp_num_y = lp_y/g_cells_per_vp_y;
  tw_lpid vp_num = vp_num_x + (vp_num_y*NUM_VP_X);
  vp_num = vp_num % g_vp_per_proc;
  tw_lpid index = vp_index + vp_num*g_cells_per_vp;

  if( index >= g_tw_nlp )
    tw_error(TW_LOC, "index (%llu) beyond g_tw_nlp (%llu) range \n", index, g_tw_nlp);

  return( index );
}

void Cell_Init(struct State *SV, tw_lp * lp)
{
  tw_lpid currentcell = 0, newcell = 0;
  int             i, dest_index = 0;
  tw_stime          ts;

  struct Msg_Data TMsg;
  struct Msg_Data * TWMsg;
  tw_event *CurEvent;

  SV->Normal_Channels = 0;
  SV->Reserve_Channels = 0;
  SV->Portables_In = 0;
  SV->Portables_Out = 0;
  SV->Call_Attempts = 0;
  SV->Channel_Blocks = 0;
  SV->Handoff_Blocks = 0;
  SV->Busy_Lines = 0;
  SV->Handoff_Blocks = 0;
  SV->CellLocationX = lp->gid % NUM_CELLS_X;
  SV->CellLocationY = lp->gid / NUM_CELLS_X;
  //setting initial Predator, Prey, Grass
  SV->Predator = 50;
  SV->Prey = 100;
  SV->Grass = 1000;

  if (SV->CellLocationX >= NUM_CELLS_X ||
      SV->CellLocationY >= NUM_CELLS_Y)
    {
      tw_error(TW_LOC, "Cell_Init: Bad CellLocations %d %d \n",
	       SV->CellLocationX, SV->CellLocationY);
    }

  ts = tw_rand_exponential(lp->rng, CELL_TICK);
  CurEvent = tw_event_new(lp->gid, ts, lp);
  TWMsg = tw_event_data(CurEvent);
  TWMsg->MethodName = UPDATE_METHOD;
  tw_event_send(CurEvent);
}


void
Cell_EventHandler(struct State *SV, tw_bf * CV, struct Msg_Data *M, tw_lp * lp)
{
  *(int *)CV = (int)0;
  M->RC.wl1 = 0;
  tw_stime          ts;
  struct Msg_Data * TWMsg;
  tw_event *CurEvent;

  switch (M->MethodName)
    {
    case UPDATE_METHOD:
      ts = tw_rand_exponential(lp->rng, CELL_TICK);
      CurEvent = tw_event_new(lp->gid, ts, lp);
      TWMsg = tw_event_data(CurEvent);
      TWMsg->MethodName = UPDATE_METHOD;
      tw_event_send(CurEvent);
      //update Grass each tick
      SV->Grass += 50;
      break;

    case PREY_DIE:
      if (SV->Predator > SV->Prey) SV->Prey-=1;
      break;

    case PREDATOR_DIE:
      if (SV->Prey == 0) SV->Predator-=1;
      break;

    default:
      tw_error(TW_LOC, "APP_ERROR (%d): InValid MethodName(%d)\n",
	       lp->gid, M->MethodName);
    }
}


void
RC_Cell_EventHandler(struct State *SV, tw_bf * CV, struct Msg_Data *M, tw_lp * lp)
{
#ifdef LPTRACEON
  long            seeds[4];
#endif

  switch (M->MethodName)
    {
    case UPDATE_METHOD:
      tw_rand_reverse_unif(lp->rng);
      SV->Grass -= 50;
      break;

    case PREY_DIE:
      SV->Prey+=1;
      break;

    case PREDATOR_DIE:
      SV->Predator+=1;
      break;
    }
}

void
CellStatistics_CollectStats(struct State *SV, tw_lp * lp)
{
  // need to implement - used below as example
  TWAppStats.Call_Attempts += SV->Call_Attempts;
  TWAppStats.Channel_Blocks += SV->Channel_Blocks;
  TWAppStats.Busy_Lines += SV->Busy_Lines;
  TWAppStats.Handoff_Blocks += SV->Handoff_Blocks;
  TWAppStats.Portables_In += SV->Portables_In;
  TWAppStats.Portables_Out += SV->Portables_Out;

  //PP STATS
  TWAppStats.Grass += SV->Grass;
}

void
CellStatistics_Compute(struct CellStatistics *CS)
{
  //  CS->Blocking_Probability = ((double)CS->Channel_Blocks + (double)CS->Handoff_Blocks) / ((double)CS->Call_Attempts - (double)CS->Busy_Lines);
  // Need to implement
}

void
CellStatistics_Print(struct CellStatistics *CS)
{
  printf("Call Attempts......................................%d\n",
	 CS->Call_Attempts);
  printf("Channel Blocks.....................................%d\n",
	 CS->Channel_Blocks);
  printf("Busy Lines.........................................%d\n",
	 CS->Busy_Lines);
  printf("Handoff Blocks.....................................%d\n",
	 CS->Handoff_Blocks);
  printf("Portables In.......................................%d\n",
	 CS->Portables_In);
  printf("Portables Out......................................%d\n",
	 CS->Portables_Out);
  printf("Blocking Probability...............................%f\n",
	 CS->Blocking_Probability);
  printf("*****************************************************\n");
  printf("Grass..............................................%d\n",
	 CS->Grass);
}

/******** Initialize_Appl *************************************************/

#define	TW_CELL	1

tw_lptype       mylps[] =
  {
    {
      (init_f) Cell_Init,
      (pre_run_f) NULL,
      (event_f) Cell_EventHandler,
      (revent_f) RC_Cell_EventHandler,
      (commit_f) NULL,
      (final_f) CellStatistics_CollectStats,
      (map_f) CellMapping_lp_to_pe,
      sizeof(struct State)
    },
    {0},
  };

void pcs_grid_mapping()
{
  tw_lpid         x, y;
  tw_lpid         lpid, kpid;
  tw_lpid         num_cells_per_kp, vp_per_proc;
  tw_lpid         local_lp_count;

  num_cells_per_kp = (NUM_CELLS_X * NUM_CELLS_Y) / (NUM_VP_X * NUM_VP_Y);
  vp_per_proc = (NUM_VP_X * NUM_VP_Y) / ((tw_nnodes() * g_tw_npe)) ;
  g_tw_nlp = nlp_per_pe;
  g_tw_nkp = vp_per_proc;

  local_lp_count=0;
  for (y = 0; y < NUM_CELLS_Y; y++)
    {
      for (x = 0; x < NUM_CELLS_X; x++)
	{
	  lpid = (x + (y * NUM_CELLS_X));
	  if( g_tw_mynode == CellMapping_lp_to_pe(lpid) )
	    {

	      kpid = local_lp_count/num_cells_per_kp;
	      local_lp_count++; // MUST COME AFTER!! DO NOT PRE-INCREMENT ELSE KPID is WRONG!!

	      if( kpid >= g_tw_nkp )
		tw_error(TW_LOC, "Attempting to mapping a KPid (%llu) for Global LPid %llu that is beyond g_tw_nkp (%llu)\n",
			 kpid, lpid, g_tw_nkp );

	      tw_lp_onpe(CellMapping_to_local_index(lpid), g_tw_pe[0], lpid);
	      if( g_tw_kp[kpid] == NULL )
		tw_kp_onpe(kpid, g_tw_pe[0]);
	      tw_lp_onkp(g_tw_lp[CellMapping_to_local_index(lpid)], g_tw_kp[kpid]);
	      tw_lp_settype( CellMapping_to_local_index(lpid), &mylps[0]);
	    }
	}
    }
}

int
main(int argc, char **argv)
{
  tw_lpid         num_cells_per_kp, vp_per_proc;
  unsigned int    additional_memory_buffers;

  // printf("Enter TWnpe, TWnkp, additional_memory_buffers \n" );
  // scanf("%d %d %d",
  //	&TWnpe, &TWnkp, &additional_memory_buffers );

  tw_init(&argc, &argv);

  nlp_per_pe = (NUM_CELLS_X * NUM_CELLS_Y) / (tw_nnodes() * g_tw_npe);
  additional_memory_buffers = 2 * g_tw_mblock * g_tw_gvt_interval;

  g_tw_events_per_pe = (nlp_per_pe * 16) +  additional_memory_buffers;

  if( tw_ismaster() )
    {
      printf("Running simulation with following configuration: \n" );
      printf("    Buffers Allocated Per PE = %d\n", g_tw_events_per_pe);
      printf("\n\n");
    }

  num_cells_per_kp = (NUM_CELLS_X * NUM_CELLS_Y) / (NUM_VP_X * NUM_VP_Y);
  vp_per_proc = (NUM_VP_X * NUM_VP_Y) / ((tw_nnodes() * g_tw_npe)) ;
  g_vp_per_proc = vp_per_proc;
  g_tw_nlp = nlp_per_pe;
  g_tw_nkp = vp_per_proc;

  g_tw_mapping = CUSTOM;
  g_tw_custom_initial_mapping = &pcs_grid_mapping;
  g_tw_custom_lp_global_to_local_map = &CellMapping_to_lp;

  /*
   * Some some of the settings.
   */
  if( tw_ismaster() )
    {
      printf("\n\n");
      printf("/**********************************************/\n");
      printf("NUM CELLS X      = %d\n", NUM_CELLS_X);
      printf("NUM CELLS Y      = %d\n", NUM_CELLS_Y);
      printf("CELL_TICK        = %lf\n", CELL_TICK);
      printf("NUM KPs per PE   = %lu \n", g_tw_nkp);
      printf("NUM LPs per PE   = %lu \n", g_tw_nlp);
      printf("g_vp_per_proc    = %lu \n", g_vp_per_proc);
      printf("/**********************************************/\n");
      printf("\n\n");
      fflush(stdout);
    }

  tw_define_lps(nlp_per_pe, sizeof(struct Msg_Data));

  /*
   * Initialize App Stats Structure
   */
  TWAppStats.Call_Attempts = 0;
  TWAppStats.Call_Attempts = 0;
  TWAppStats.Channel_Blocks = 0;
  TWAppStats.Busy_Lines = 0;
  TWAppStats.Handoff_Blocks = 0;
  TWAppStats.Portables_In = 0;
  TWAppStats.Portables_Out = 0;
  TWAppStats.Blocking_Probability = 0.0;

  //PP MODEL STATS
  TWAppStats.Grass = 0;

  
  tw_run();

  if( tw_ismaster() )
    {
      CellStatistics_Compute(&TWAppStats);
      CellStatistics_Print(&TWAppStats);
    }

  tw_end();

  return 0;
}