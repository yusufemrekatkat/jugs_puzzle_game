#ifndef DATA_TYPES_H
#define DATA_TYPES_H
#include <stdio.h>

const int NUM_JUGS=2; /*The number of jugs 
(In the future, we will make this value 3, because the teacher asked us for a 2 and 3 jugs solution.)*/
const int JUG_CAPACITIES[NUM_JUGS]={5,3}; //Jug capacities
const int TARGET_AMOUNT = 2; //Target

enum ACTIONS 
{
    FILL_JUG_0,	
    FILL_JUG_1,
    //FILL_JUG_2,   //For now, there is no need as we currently have two jugs.
    EMPTY_JUG_0,
    EMPTY_JUG_1,
    //EMPTY_JUG_2,
    POUR_0_TO_1,   
    POUR_1_TO_0
    //POUR_0_TO_2, 
	//POUR_1_TO_2, 
	//POUR_2_TO_0, 
	//POUR_2_TO_1
};

typedef struct State
{
    int jug_levels[NUM_JUGS]; //Water level in each jug
} State;

// ================== YOU DO NOT NEED TO CHANGE THIS PART ======================

enum METHODS
{
	BreastFirstSearch = 1,   UniformCostSearch = 2,        DepthFirstSearch = 3,    
	DepthLimitedSearch= 4,   IterativeDeepeningSearch = 5, GreedySearch = 6,
    AStarSearch = 7, GeneralizedAStarSearch = 8  
};

// This struct is used to determine a new state and action in transition model
typedef struct Transition_Model
{
    State new_state;
    float step_cost;
}Transition_Model;

typedef struct Node
{
    State state;
    float path_cost;
    enum ACTIONS action; //The action applied to the parent to generate this node
    struct Node *parent;
    int Number_of_Child; // required for depth-first search algorithms
}Node;

typedef struct Queue  // Used for frontier
{
    Node *node;
    struct Queue *next;
}Queue;



#endif
