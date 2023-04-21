# Team-010-23-homework4

### Members:
Lorenz Estrera (estre069)  
Jonathan Haak (haak0052)  
Emma Kindelsperger (kinde085)  
Ben Knight (knigh501)  

## Project Overview
This project represents a drone simulation system. In this simulation, users can schedule trips for robots on a map of the University of Minnesota campus. Users are in control of the robots' starting point, final destination, as well as path routing strategy. Drones will then pick up the scheduled robots, carry them to their destination using the appropriate routing strategy, and drop them off. 

## How to Run the Simulation


## Specifics of the Simulation
Drones can be instructed to use either Astar, DFS, or Dijkstra's search algorithms to determine the routes they take while carrying drones. However, when drones are flying to go pick up robots or to go recharge their battery at a recharging station, drones use the Beeline path strategy. While Astar, DFS, and Dijkstra all use actual path finding algorithms to calculate legitimate routes in between buildings on the map, Beeline just moves drones from one point to another in a completely linear movement. 

Upon arrival of a robot to its destination, both the robot and the drone will celebrate the successful delivery. The type of celebration depends on what routing strategy the user chose for the given robot. If Astar was chosen, then the drone and robot will celebrate by jumping up and down in place. If DFS was chosen, then the drone and robot will celebrate by first jumping, and then spinning around in place. If Dijkstra was chosen, then the drone and robot will celebrate by first spinning around, and then jumping.



## New Feature #1 - Battery Recharging
Our first extension was adding a battery to the drones that depletes over time with movement, as well as recharging stations placed around the map. As drones fly around picking up and dropping off robots, their battery life will slowly go down from 100% to 0%. When a drone's battery reaches 25% or less, then it will automatically go and find the nearest recharge station. 

//do drones also lose battery when not moving?
//logic of what to do when low battery while carrying a robot
//how edge cases are resolved (multiple drones and recharge stations)
//is recharging incremental or immediate?


## New Feature #2 - Data Collection


## Sprint Retrospective


## UML Diagram


## Docker link


