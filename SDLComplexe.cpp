#include "SDLComplexe.hpp"

using namespace std;

SDLComplexe::SDLComplexe() : SDL_Screen(1080, 720, "Complexe", 30.0) {
	cList = new LinkedList<Complexe>();
	zoom = 1;
	center_x = 0, center_y = 0;
}

void SDLComplexe::run(){
	SDLComplexe sc;
	while(sc.isRunning()){
		
		sc.bg(255);
		sc.setColor(0);
		sc.drawAxis();
		sc.refreshAndEvents();
		// std::cout << "(" << sc.center_x << "," << sc.center_y << ")\nz=" << sc.zoom<<"\n";
	}
}

void SDLComplexe::events(){
	while (SDL_PollEvent(&e)){ // reads all the events (mouse moving, key pressed...)        //possible to wait for an event with SDL_WaitEvent
		switch (e.type){
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

					case 1073741904: // left arrow
						center_x -= 10;
						break;

					case 1073741903: // right arrow
						center_x += 10;
						break;

					case 1073741906: // up arrow
						center_y -= 10;
						break;

					case 1073741905: // down arrow
						center_y += 10;
						break;
					
					case SDLK_KP_PLUS:
						zoom *= 1.5;
						break;

					case SDLK_KP_MINUS:
						zoom /= 1.5;
						break;


					default:
						std::cout << "evt : " << e.key.keysym.sym << std::endl;
						break;
				}
				break;

			case SDL_KEYUP:
				switch (e.key.keysym.sym){

					default:
						break;
				}
				break;

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
	this->line(0, center_y + H()/2, W(), center_y + H()/2);
	// arrow
	this->filledTriangle(W()-10, center_y + int(H()/2)-10, W()-10, center_y + int(H()/2)+10, W(), center_y + int(H()/2));
	

	// === vertical axis

	// axis
	this->line(center_x + W()/2, 0, center_x + W()/2, H());
	//arrow
	this->filledTriangle(center_x + W()/2-10, 10, center_x + W()/2+10, 10, center_x + W()/2, 0);

	// === graduations
	for(unsigned int i = 1 ; i <= graduation_count*2 + 1 ; i++) {
		//if(i == graduation_count + 1) continue;
		this->line(int(center_x) % int(W()/2) + i*int(W()/(graduation_count*2 + 2)) % W(), center_y + int(H()/2) - 5, int(center_x) % int(W()/2) + i*int(W()/(graduation_count*2 + 2)) % W(), center_y + int(H()/2) + 5); // horizontal
		this->line(int(center_x + W()/2) - 5, center_y + i*int(H()/(graduation_count*2 + 2)), int(center_x + W()/2) + 5, center_y + i*int(H()/(graduation_count*2 + 2))); // vertical
	}
	

}