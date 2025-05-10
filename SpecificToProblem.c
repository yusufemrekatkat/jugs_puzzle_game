/* 
    These functions are compulsory for search algorithms but they are specific
    to problems. More clearly, you must must update their blocks but do not change
    their input and output parameters.
    
    Also, you can add new functions at the end of file by declaring them in GRAPH_SEARCH.h
*/

#include "GRAPH_SEARCH.h"
#include "data_types.h"
#include <stdio.h>
#include <stdlib.h>

//______________________________________________________________________________
State* Create_State()
{
	State *state = (State*)malloc(sizeof(State));
    if(state==NULL)
    	Warning_Memory_Allocation(); 
   
    for (int i=0; i<NUM_JUGS; i++) {
        state->jug_levels[i] = 0;
    }
    
    printf("Initial status: ");
    Print_State(state);
    printf("\n");

    return state;    
}

//______________________________________________________________________________
void Print_State(const State *const state)
{
    int i;
    if (state==NULL) {
        printf("NULL_State ");
        return;
    }

    for (i = 0; i < NUM_JUGS; i++) {
        printf("%d ", state->jug_levels[i]);
    }
    printf("\n");
}

//______________________________________________________________________________
void Print_Action(const enum ACTIONS action)
{
    switch(action){
         case FILL_JUG_0:     printf("FILL_JUG_0"); break;
         case FILL_JUG_1:     printf("FILL_JUG_1"); break;
         case FILL_JUG_2:     printf("FILL_JUG_2"); break; 
         case EMPTY_JUG_0:    printf("EMPTY_JUG_0"); break;
         case EMPTY_JUG_1:    printf("EMPTY_JUG_1"); break;
         case EMPTY_JUG_2:     printf("EMPTY_JUG_2"); break;
         case POUR_0_TO_1:   printf("POUR_0_TO_1"); break;
         case POUR_1_TO_0:   printf("POUR_1_TO_0"); break;
         case POUR_0_TO_2:   printf("POUR_0_TO_2"); break;
         case POUR_1_TO_2:   printf("POUR_1_TO_2"); break;
         case POUR_2_TO_0:   printf("POUR_2_TO_0"); break;
         case POUR_2_TO_1:   printf("POUR_2_TO_1"); break;
    }
}

//______________________________________________________________________________
int Result(const State *const parent_state, const enum ACTIONS action, Transition_Model *const trans_model)
{
    State next_state;
    next_state=*parent_state;
    
	int amount_to_pour;
    int empty_space_in_target;
    
    if (action==FILL_JUG_2 || action==EMPTY_JUG_2 || action==POUR_0_TO_2 ||action==POUR_2_TO_0 || action==POUR_1_TO_2 || action==POUR_2_TO_1) {
        if (NUM_JUGS < 3) {
            return 0;
        }

    switch(action) {

        case FILL_JUG_0:
            if (next_state.jug_levels[0]==JUG_CAPACITIES[0]) return 0;
            next_state.jug_levels[0]=JUG_CAPACITIES[0];
            break;
        case FILL_JUG_1:
            if (next_state.jug_levels[1]==JUG_CAPACITIES[1]) return 0;
            next_state.jug_levels[1]=JUG_CAPACITIES[1];
            break;
        case FILL_JUG_2:
            if (next_state.jug_levels[2]==JUG_CAPACITIES[2]) return 0;
            next_state.jug_levels[2]=JUG_CAPACITIES[2];
            break;
        case EMPTY_JUG_0:
            if (next_state.jug_levels[0]==0) return 0;
            next_state.jug_levels[0]=0;
            break;
        case EMPTY_JUG_1:
            if (next_state.jug_levels[1]==0) return 0;
            next_state.jug_levels[1]=0;
            break;
        case EMPTY_JUG_2:
            if (next_state.jug_levels[2]==0) return 0;
            next_state.jug_levels[2]=0;
            break;
        case POUR_0_TO_1:
            if (next_state.jug_levels[0]==0 || next_state.jug_levels[1]==JUG_CAPACITIES[1]) return 0;
            amount_to_pour=next_state.jug_levels[0];
            empty_space_in_target=JUG_CAPACITIES[1]-next_state.jug_levels[1];
            if (amount_to_pour>empty_space_in_target) amount_to_pour=empty_space_in_target;
            next_state.jug_levels[0]-=amount_to_pour;
            next_state.jug_levels[1]+=amount_to_pour;
            break;
        case POUR_1_TO_0:
            if (next_state.jug_levels[1]==0 || next_state.jug_levels[0]==JUG_CAPACITIES[0]) return 0;
            amount_to_pour=next_state.jug_levels[1];
            empty_space_in_target=JUG_CAPACITIES[0]-next_state.jug_levels[0];
            if (amount_to_pour>empty_space_in_target) amount_to_pour=empty_space_in_target;
            next_state.jug_levels[1]-=amount_to_pour;
            next_state.jug_levels[0]+=amount_to_pour;
            break;
        case POUR_0_TO_2:
            if (next_state.jug_levels[0]==0 || next_state.jug_levels[2]==JUG_CAPACITIES[2]) return 0;
            amount_to_pour=next_state.jug_levels[0];
            empty_space_in_target=JUG_CAPACITIES[2]-next_state.jug_levels[2];
            if (amount_to_pour>empty_space_in_target) amount_to_pour=empty_space_in_target;
            next_state.jug_levels[0]-=amount_to_pour;
            next_state.jug_levels[2]+=amount_to_pour;
            break;
        case POUR_2_TO_0:
            if (next_state.jug_levels[2]==0 || next_state.jug_levels[0]==JUG_CAPACITIES[0]) return 0;
            amount_to_pour=next_state.jug_levels[2];
            empty_space_in_target=JUG_CAPACITIES[0]-next_state.jug_levels[0];
            if (amount_to_pour>empty_space_in_target) amount_to_pour=empty_space_in_target;
            next_state.jug_levels[2]-=amount_to_pour;
            next_state.jug_levels[0]+=amount_to_pour;
            break;
        case POUR_1_TO_2:
            if (next_state.jug_levels[1]==0 || next_state.jug_levels[2]==JUG_CAPACITIES[2]) return 0;
            amount_to_pour=next_state.jug_levels[1];
            empty_space_in_target=JUG_CAPACITIES[2]-next_state.jug_levels[2];
            if (amount_to_pour>empty_space_in_target) amount_to_pour=empty_space_in_target;
            next_state.jug_levels[1]-=amount_to_pour;
            next_state.jug_levels[2]+=amount_to_pour;
            break;
        case POUR_2_TO_1:
            if (next_state.jug_levels[2]==0 || next_state.jug_levels[1]==JUG_CAPACITIES[1]) return 0;
            amount_to_pour=next_state.jug_levels[2];
            empty_space_in_target=JUG_CAPACITIES[1]-next_state.jug_levels[1];
            if (amount_to_pour>empty_space_in_target) amount_to_pour=empty_space_in_target;
            next_state.jug_levels[2]-=amount_to_pour;
            next_state.jug_levels[1]+=amount_to_pour;
            break;
        default:
             printf("ERROR in Result Func", action);
             return 0;
    }
    trans_model->new_state=next_state;
    trans_model->step_cost = 1.0f;
    return 1;                                      
}

//______________________________________________________________________________
float Compute_Heuristic_Function(const State *const state, const State *const goal)
{
      const float SLD[CITY_NUMBER][CITY_NUMBER] =   // CALCULATED ROUGHLY!!!
        {   {  0, 366, 300, 220, 590, 235, 430, 535, 420, 168, 225, 355, 110, 290, 185, 130, 105, 435, 470,  67},  // Arad
            {366,   0, 160, 242, 161, 176,  77, 151, 226, 244, 241, 234, 380, 100, 193, 253, 329,  80, 199, 374},  // Bucharest
			{300, 160,   0, 102, 325, 210, 142, 325, 368, 145, 110, 388, 355, 133, 138, 190, 220, 220, 385, 330},  // Craiova
			{220, 242, 102,   0, 390, 245, 240, 380, 400, 100,  70, 460, 310, 190, 155, 205, 150, 302, 410, 265},  // Drobeta
			{590, 161, 325, 390,   0, 325, 205,  80, 245, 400, 375, 350, 595, 265, 340, 395, 555, 130, 260, 593},  // Eforie
			{235, 176, 210, 245, 325,   0, 200, 251, 180, 175, 185, 135, 220, 102,  85,  95, 255, 195, 200, 227},  // F 
			{430,  77, 142, 240, 205, 200,   0, 213, 297, 245, 280, 285, 410, 125, 225, 285, 330, 120, 230, 520},  // G
			{535, 151, 325, 380,  80, 251, 213,   0, 205, 370, 370, 260, 535, 220, 345, 365, 495,  92, 130, 535},  // H
			{440, 226, 368, 400, 245, 180, 297, 205,   0, 330, 350,  80, 365, 250, 260, 280, 450, 190,  85, 390},  // I
			{168, 244, 145, 100, 400, 175, 245, 370, 330,   0,  66, 290, 240, 140,  95, 135, 100, 285, 360, 205},  // L 
			{225, 241, 110,  70, 375, 185, 280, 370, 350,  66,   0, 305, 300, 140, 120, 175, 130, 280, 370, 260},  // M
			{355, 234, 388, 460, 350, 135, 285, 260,  80, 290, 305,   0, 273, 220, 260, 250, 330, 235, 155, 310},  // N
			{110, 380, 355, 310, 595, 220, 410, 535, 365, 240, 300, 273,   0, 305, 200, 140, 213, 415, 435,  66},  // O
			{290, 100, 133, 190, 265, 102, 125, 220, 250, 140, 140, 220, 305,   0, 115, 150, 230, 140, 185, 297},  // P
			{185, 193, 138, 155, 340,  85, 225, 345, 260,  95, 120, 260, 200, 115,   0,  75, 150, 230, 290, 193},  // R
			{130, 253, 190, 205, 395,  95, 285, 365, 280, 135, 175, 250, 140, 150,  75,   0, 137, 300, 330, 135},  // S
			{105, 329, 220, 150, 555, 255, 330, 495, 450, 100, 130, 330, 213, 230, 150, 137,   0, 380, 455, 155},  // T
			{435,  80, 220, 302, 130, 195, 120,  92, 190, 285, 280, 235, 415, 140, 230, 300, 380,   0, 132, 425},  // U
			{470, 199, 385, 410, 260, 200, 230, 130,  85, 360, 370, 155, 435, 185, 290, 330, 455, 132,   0, 452},  // V
			{ 67, 374, 330, 265, 593, 227, 520, 535, 390, 205, 260, 310,  66, 297, 193, 135, 155, 425, 452,   0}   // Z
		};
	     //    A    B    C    D    E    F    G    H    I    L    M    N    O    P    R    S    T    U    V    Z   
         
        return SLD[state->city][goal->city];   
}

//_______________ Update if your goal state is not determined initially ___________________________________
int Goal_Test(const State *const state, const State *const goal_state)
{
	if(PREDETERMINED_GOAL_STATE)	
		return Compare_States(state, goal_state); 
	else
		return 1;
}

// ==================== WRITE YOUR OPTIONAL FUNCTIONS (IF REQUIRED) ==========================

int Get_Actions(const State *const state, enum ACTIONS applicable_actions[]) {
    int count=0;
    enum ACTIONS action_to_test;
    Transition_Model temp_trans_model;

    for (action_to_test=FILL_JUG_0; action_to_test<ACTIONS_COUNT; action_to_test++) {
        if (Result(state,action_to_test,&temp_trans_model)==1) {
            if (count<ACTIONS_COUNT) {
                applicable_actions[count]=action_to_test;
                count++;
            } else {
                printf("ERROR in Get Act");
                break;
            }
        }
    }
    return count;
}

/*
The main purpose of this function is to find all applicable actions that can be taken at that moment 
for a current water container state and save them in an array (applicable_actions). 
Finally, it returns how many valid actions there are.
-riza
*/

// TR: Uygulanabilir eylemleri diziye atar ve kac eylem gerektigini verir.

int main()
{
	/*This place should be written, 
	it is empty for now because we have not determined the state of the heuritistic function 
	-riza*/
}
