#include "Simulation.hpp"

int main(){
    sm::Simulation simulation;

    while(simulation.isRunning()){
        
        simulation.update();

        simulation.render();

    }


    return 0;
}