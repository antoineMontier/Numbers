#ifndef SDLCOMPLEXE_HPP
#define SDLCOMPLEXE_HPP

#include "SDL_Screen.hpp"
#include "Complexe.hpp"
#include "LinkedList.cpp"


using namespace std;

class SDLComplexe : public SDL_Screen{


    private:

        LinkedList<Complexe> * cList;
        // zoom level, ie, the separation between two graduations
        double zoom;
        // center of the screen, if (0 ; 0), the screen will be centered on th origin of the axis
        double center_x, center_y;

    public:

        SDLComplexe();

        static void run();

        void events() override;

        void drawAxis();

};

#endif