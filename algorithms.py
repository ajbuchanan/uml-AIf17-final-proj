from util import *
from graph import graph

import sys

def depthFirstSearch(graph):
    frontier = Stack()
    frontier.push([(graph.getStartState(), "Stop", 0)])
    explored = list()
    

    while not frontier.isEmpty():
        currentNodeData = frontier.pop()

        currentNode = currentNodeData[len(currentNodeData)-1][0]

        if graph.isGoalState(currentNode):
            return [temp[1] for temp in currentNodeData][1:]

        if currentNode not in explored:
            explored.append(currentNode)

        for scsr in graph.getSuccessors(currentNode):
            
            if scsr[0] not in explored:
                newLoc = currentNodeData[:]
                newLoc.append(scsr)
                frontier.push(newLoc)

    return []

def breadthFirsSearch(graph):
    frontier = Queue()
    frontier.push((graph.getStartState(), [], 0))
    
    state, allocations, total_cost = frontier.pop()
    visited_states = [state]
    while (not graph.isGoalState(state)):
        successors = graph.getSuccessors(state)

        for next_state,action,cost in successors:
            if (not next_state in visited_states):
                frontier.push((next_state,allocations + [action], total_cost + cost))
                visited_states.append(next_state)
          
        state,allocations,total_cost = frontier.pop()
      
    return  allocations

def uniformCostSearch(graph):
    frontier = PriorityQueue()
    frontier.push((graph.getStartState(), [], 0), 0)
    
    state, allocations, total_cost = frontier.pop()
    visited_states = [(state,0)]
    
    while (not graph.isGoalState(state)):
        successors = graph.getSuccessors(state)

        for next_state, action, cost in successors:
            already_seen = False
            total_cost = graph.getCostOfActions(allocations+[action])

            for i in range(len(visited_states)):
                state_tmp, cost_tmp = visited_states[i]

                if (next_state == state_tmp) and (total_cost >= cost_tmp):
                    already_seen = True

            if (not already_seen):
                frontier.push((next_state, allocations + [action], total_cost), total_cost)
                visited_states.append((next_state,total_cost))
            
        state,allocations, total_cost = frontier.pop()
    
    return  allocations

def aStarSearch(graph):
    frontier = PriorityQueue()
    frontier.push((graph.getStartState(),[],0),0)
    
    state, allocations, total_cost = frontier.pop()
    visited_states=[(state,0)]
    
    while (not graph.isGoalState(state)):      
        successors=graph.getSuccessors(state)

        for next_state,action,cost in successors:
            total_cost=graph.getCostOfActions(allocations+[action])
            already_seen=False
                
            for i in range(len(visited_states)):
                state_tmp,cost_tmp=visited_states[i]

                if (next_state==state_tmp) and (total_cost>=cost_tmp):
                    already_seen=True

            if (not already_seen):
                total_cost=graph.getCostOfActions(allocations+[action])
                frontier.push((next_state,allocations+[action],total_cost),total_cost+heuristic(next_state,graph))
                visited_states.append((next_state,total_cost))
            
        state,allocations,total_cost=frontier.pop()
    
    return  allocations
