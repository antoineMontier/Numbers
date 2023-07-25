#include "SDLComplexe.hpp"

using namespace std;

SDLComplexe::SDLComplexe() : SDL_Screen(1080, 720, "Complexe", 30.0) {
    cList = new LinkedList<Complexe>();
}

void SDLComplexe::run(){
    SDLComplexe sc;
    while(sc.isRunning()){
        sc.bg(255);
        sc.setColor(0);
        sc.drawAxis();
        sc.refreshAndDetailsAndEvents();
    }
}

void SDLComplexe::events(){
    while (SDL_PollEvent(&e))
        { // reads all the events (mouse moving, key pressed...)        //possible to wait for an event with SDL_WaitEvent
            switch (e.type)
            {
            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_RESIZED)
                    updateSize();
                break;
            case SDL_QUIT:
                program_running = false; // quit the program if the user closes the window
                break;

            case SDL_KEYDOWN: // SDL_KEYDOWN : hold a key            SDL_KEYUP : release a key
                switch (e.key.keysym.sym){ // returns the key ('0' ; 'e' ; 'SPACE'...)

                case SDLK_ESCAPE:
                    program_running = false; // escape the program if user presses esc
                    break;

                default:
                    break;
                }

            case SDL_KEYUP:
                switch (e.key.keysym.sym){

                    default:
                        break;
                }

            default:
                break;
            }
        }
}

void SDLComplexe::drawAxis(){
    // number of graduations between a border of the screen and the origin
    unsigned int graduation_count = 5;
    
    // === horizontal axis

    // axis
    this->line(W()/2, 0, W()/2, H());
    // arrow
    this->filledTriangle(W()-10, int(H()/2)-10, W()-10, int(H()/2)+10, W(), int(H()/2));
    // graduations TODO: fix to not display the central graduation
    for( int i = int(W()/(graduation_count*2 + 2)) ; i < W() ; i += int(W()/(graduation_count*2 + 2)) ) if(i != W()/2) this->line(i, int(H()/2) - 5, i, int(H()/2) + 5);


    // === vertical axis

    // axis
    this->line(0, H()/2, W(), H()/2);
    //arrow
    this->filledTriangle(W()/2-10, 10, W()/2+10, 10, W()/2, 0);
    // graduations
    for( int i = int(H()/(graduation_count*2 + 2)) ; i < H() ; i += int(H()/(graduation_count*2 + 2)) ) this->line(int(W()/2) - 5, i, int(W()/2) + 5, i);


}