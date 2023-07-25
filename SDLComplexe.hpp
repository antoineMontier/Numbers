#ifndef SDLCOMPLEXE_HPP
#define SDLCOMPLEXE_HPP

#include "SDL_Screen.hpp"
#include "Complexe.hpp"
#include "LinkedList.cpp"


using namespace std;

class SDLComplexe : public SDL_Screen{


    private:

        LinkedList<Complexe> * cList;

    public:

        SDLComplexe();

        static void run();

        void events();

        void drawAxis();

};

#endif