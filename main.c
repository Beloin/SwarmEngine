#include <stdio.h>
#include "physicsContext.h"
//#include <sys/time.h>
#include <time.h>

PhysicsContext const context = (PhysicsContext) {0, S};

void doSimulate();

int main() {
    printf("Hello, World!\n");
    int fps = 0;

    clock_t start_, step_; // start and step are in ms.
    step_ = start_ = clock();

    while (1) {
        fps++;

        double seconds = (double) (step_ - start_) / CLOCKS_PER_SEC; // This gives in seconds
        if (seconds >= 1) {
            printf("FPS: %d\n", fps);
            start_ = clock();
            fps = 0;
        }

        if (context.resolution == S) {
            if (seconds >= 1) {
                doSimulate();
            }
        } else if (context.resolution == MS_500) {
            if (seconds >= 0.5) {
                doSimulate();
            }
        } else if (context.resolution == MS_100) {
            if (seconds >= 0.1) {
                doSimulate();
            }
        }


        step_ = clock();
    }

    return 0;
}
