#ifndef SDLCOMPLEXE_HPP
#define SDLCOMPLEXE_HPP

#include "SDL_Screen.hpp"
#include "Complexe.hpp"
#include "LinkedList.cpp"


using namespace std;

class SDLComplexe : public SDL_Screen{


    private:
        
        // linked list to keep the complex numbers 
        std::vector<Complexe>   cList;
        std::vector<double>        divergence;

        // zoom level, ie, the separation between two graduations
        double zoom;

        // center of the screen, if (0 ; 0), the screen will be centered on th origin of the axis
        double center_x, center_y;

	    // number of graduations between a border of the screen and the origin
        unsigned int graduation_count = 5;

        int unit_cx = int(W() / (graduation_count*2 + 2));  
		int unit_cy = int(H() / (graduation_count*2 + 2));

        // boolean variable indicating whether or not display the axis and graduations
        bool display_axis = true;

        // coordinates and previous coordinates of the mouse
        int mouseX = 0, mouseY = 0, pmouseX = 0, pmouseY = 0;

        // indicates whether or not the mouse is pressed
        bool click = false;

        TTF_Font *font;

        int it_max = 2550;	// max amount of iterations when computing mandelbrot


    public:

        SDLComplexe();

        static void run();

        void events() override;

        void drawAxis();

        void addComplexe(const Complexe c);
        void addComplexe(const double re, const double im);
        void addComplexe(const double re);

        void displayComplexes();

        void axis_button();

        void load_mandelbrot(double min_x, double min_y, double max_x, double max_y, double precision);

        void complexe_to_pixel(Complexe c, double *x, double *y);

        void pixel_to_complexe(double x, double y, Complexe *c);

        void pixel_to_complexe(double x, double y, double *Re, double *Im);

        int compute_mandelbrot(Complexe c);



};

#endif