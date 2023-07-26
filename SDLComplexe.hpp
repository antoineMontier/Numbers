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

	    // number of graduations between a border of the screen and the origin
        unsigned int graduation_count = 5;

        int unit_cx = int(W() / (graduation_count*2 + 2));  
		int unit_cy = int(H() / (graduation_count*2 + 2));

    public:

        SDLComplexe();

        static void run();

        void events() override;

        void drawAxis();

        void addComplexe(const Complexe c);
        void addComplexe(const double re, const double im);
        void addComplexe(const double re);

        void displayComplexes();

};

#endif