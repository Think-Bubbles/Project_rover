<p align="center" width="100%">
    <img width="33%" src="https://github.com/Think-Bubbles/Project_rover/blob/main/Mars_rover.png">
</p>


Welcome to the Mars Project Simulator! This project is a C-based simulation of a rover navigating the challenging terrain of Mars to return to its base station. Using an efficient pathfinding algorithm, the simulator calculates the most cost-effective route, optimizing for energy and time.

<p align="center" width="100%">
    | <a href=🚀"#🚀-features">Features</a> | <a href="🛠#🛠️-getting-started">Getting Started</a> | <a href="⚙️#⚙️-installation">Installation</a> | <a href="#known-bugs">Known bugs</a> | <a href="👥#👥-contributors">Contributors</a> |
</p>

## 🚀 Features

Our Mars Project Simulator offers an engaging solution to simulate efficient pathfinding on Mars, written in C. This project demonstrates how autonomous systems can overcome challenges in unfamiliar environments, such as rugged Martian terrain, to find the most cost-effective path to safety.

For now, we have implemented the following features:

 - Pre-Designed Maps: The simulator includes a selection of maps, each with the base station positioned at different coordinates. The rover begins at a random edge position, facing a random direction.
 - Card Selection System: On the first attempt, we randomly select 9 cards from a deck of 100, and out of those 9, we can only use 5. These cards influence the rover's initial moves.
 - Iterative Pathfinding: If the base station is not reached on the first attempt, our algorithm recalculates the closest or most efficient path based on the current state. The rover resumes from there, restarting the process until the base is reached.
 - Custom Tree Structure: The rover’s decision-making process is modeled as a tree:
     - The root node has 9 children, each with 8 children, and so on, down to 5 at the bottom layer.
     - The tree is rebuilt iteratively, starting with the optimal leaf from the previous iteration.

## 🛠️ Getting Started 

Since this is a simulation, there isn’t much for the user to do! Simply follow the on-screen instructions to select a map, and then sit back and watch the simulation unfold as the rover navigates its way back to the base station.
No additional input is required during the process. Enjoy observing the efficiency of our algorithm in action!

## ⚙️ Installation

To set up and run the Mars Project Simulator:

Clone the repository:

```bash
git clone https://github.com/Think-Bubbles/Project_rover.git
```
Navigate to the project directory:

```bash
cd [WHATEVER YOUR REPOSITORY IS CALLED]
```

Compile the code using your preferred C compiler (e.g., gcc):

```bash
gcc -o mars_simulator mars_simulator.c
```
Run the simulation:

```bash
./mars_simulator
```

In order to use this program, please insure that you have the following installed
- [Clion](https://www.jetbrains.com/fr-fr/clion/download/#section=windows) and at the very least version 3.27!

## Known bugs 

None currently, but please if you find any inconsistencies please inform us!

## 👥 Contributors 

- ROBERT William       (william.robert@efrei.net)
- HAMZAOGULLARI Batur  (batur.hamzaogullari@efrei.net)
- HIM James            (james.him@efrei.net)

[Link to our Github:](https://github.com/Think-Bubbles/Project_rover)
