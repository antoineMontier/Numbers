#include "SDLComplexe.hpp"

using namespace std;

SDLComplexe::SDLComplexe() : SDL_Screen(1080, 720, "Complexe", 30.0) {
	cList = new LinkedList<Complexe>();
	zoom = 1;
	center_x = 0, center_y = 0;
}

void SDLComplexe::run(){
	SDLComplexe sc;
	sc.setFont(&sc.font, "Roboto-Light.ttf", 16);
	sc.addComplexe(1, 2);
	sc.addComplexe(2, -3);
	sc.addComplexe(-3, -4);
	sc.addComplexe(-2, 3);
	while(sc.isRunning()){
		sc.bg(255);
		sc.setColor(0);
		sc.axis_button();
		sc.drawAxis();
		sc.displayComplexes();
		sc.refreshAndEvents();
		//std::cout << "center : (" << sc.center_x << "," << sc.center_y << ")\nz=" << sc.zoom<<"\n";
	}
	TTF_CloseFont(sc.font);
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
						zoom *= 1.2;
						break;

					case SDLK_KP_MINUS:
						zoom /= 1.2;
						break;

					default:
						std::cout << "evt : " << e.key.keysym.sym << std::endl;
						break;
				}
				break;

			case SDL_MOUSEWHEEL:
				// std::cout << "case mouse\n";
				int scroll;
				scroll = e.wheel.y;
				if 		( scroll == 1  ) zoom *= 1.05;
				else if ( scroll == -1 ) zoom /= 1.05;
				break;

			case SDL_MOUSEMOTION:
                pmouseX = mouseX;
                pmouseY = mouseY;
                mouseX = e.button.x;
                mouseY = e.button.y;
                break;

			case SDL_MOUSEBUTTONDOWN:
                click = true;
				break;

			case SDL_MOUSEBUTTONUP:
                click = false;
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

	if(!display_axis) return;

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
	
	int x, y;

	std::string grad;
	double actual_grad = 0;
	// === graduations
	for(unsigned int i = 0 ; i <= graduation_count*2 + 2; i++) {
		
		x = int(center_x) % unit_cx + i*unit_cx;
		y = min(max(int(center_y + H()/2), 0), H());
		
		this->line( x, y - 5, x, y + 5); // horizontal

		// === horizontal graduations
		actual_grad = int(i - graduation_count - 1) - int(center_x / unit_cx);
			if(actual_grad != 0){
			if(actual_grad >= 0)	grad = std::to_string(actual_grad).substr(0, 4);
			else					grad = std::to_string(actual_grad).substr(0, 5);
			if(center_y < -330)	text(x - 4, y + 11, grad.c_str(), font);
			else 				text(x - 4, y - 25, grad.c_str(), font);
		}

		x = min(max(int(center_x + W()/2), 0), W());
		y = int(center_y) % unit_cy + i*unit_cy;

		this->line(	x - 5, y, x + 5, y); // vertical

		// === vertical graduations
		actual_grad = int(i - graduation_count - 1) - int(center_y / unit_cy);
		if(actual_grad != 0) {
			if(actual_grad >= 0)	grad = std::to_string(-actual_grad).substr(0, 5);
			else					grad = std::to_string(-actual_grad).substr(0, 4);
			if(center_x > 480)	text(x - 46, y-8, grad.c_str(), font);
			else 				text(x + 18, y-8, grad.c_str(), font);
		}
	}

}

void SDLComplexe::addComplexe(const Complexe c)					{ cList->push(c); 				 }
void SDLComplexe::addComplexe(const double re, const double im)	{ cList->push(Complexe(re, im)); }
void SDLComplexe::addComplexe(const double re)					{ cList->push(Complexe(re)); 	 }

void SDLComplexe::displayComplexes(){
	if (cList->size() == 0) return;
	for (int i = 0 ; i < cList->size() ; i++){
		// == load the complex
		Complexe current = cList->get(i);
		// == display the complex
		setColor(255, 0, 0);
		this->point(W()/2 + center_x + current.getRe() * unit_cx, H()/2 + center_y - current.getIm() * unit_cy, 5);
	}
}

void SDLComplexe::axis_button(){
	int sz = 25;
	int x = W() - sz - 10;
	int y = 10;
	int t_size = 4;
	emptyRect(x, y, sz, sz, 3); // draw the rectangle
	x -= 1;
	line(x + sz/2, y + 2, x + sz/2, y + sz - 2); // draw the vertical axis
	filledTriangle(x + sz/2 - t_size, y + t_size + 2, x + sz/2 + t_size, y + t_size + 2, x + sz/2, y + 2); // draw the vertical arrow
	
	x += 1; y += 2;

	line(x + 2, y + sz/2, x + sz - 2, y + sz/2); // draw the horizontal axis
	filledTriangle(x + sz - 2 - t_size, y + sz/2 - t_size, x + sz - 2 - t_size, y + sz/2 + t_size, x + sz - 2, y + sz/2); // draw the horizontal arrow 
	y -= 2;
	if (click && rollover(mouseX, mouseY, x, y, sz, sz)){ 
		display_axis = !display_axis; 
		click = false;
	}
}
