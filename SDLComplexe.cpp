#include "SDLComplexe.hpp"

using namespace std;

SDLComplexe::SDLComplexe() : SDL_Screen(1080, 720, "Complexe", 30.0) {
	zoom = .5;
	center_x = 0, center_y = 0;
}

void SDLComplexe::run(){
	SDLComplexe sc;
	sc.setFont(&sc.font, "Roboto-Light.ttf", 16);
	while(sc.isRunning()){
		sc.bg(255);
		sc.setColor(0);
		sc.displayComplexes();
		sc.drawAxis();
		sc.axis_button();
		sc.draw_center();
		sc.refreshAndEvents();
		// std::cout << "center : (" << sc.center_x << "," << sc.center_y << ")\nz=" << sc.zoom<<"\n";
	}
	TTF_CloseFont(sc.font);
}

void SDLComplexe::events(){
	while (SDL_PollEvent(&e)){ // reads all the events (mouse moving, key pressed...)        //possible to wait for an event with SDL_WaitEvent
		double c_x, c_y;
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
						center_x += 10;
						break;

					case 1073741903: // right arrow
						center_x -= 10;
						break;

					case 1073741906: // up arrow
						center_y += 10;
						break;

					case 1073741905: // down arrow
						center_y -= 10;
						break;

					case SDLK_r: // reload
						double min_x, max_x, min_y, max_y;
						pixel_to_complexe(0, 0, &min_x, &min_y);
						pixel_to_complexe(W(), H(), &max_x, &max_y);
						//std::cout << "loading\n" << min_x << " " << max_y << " -- " << max_x << " " << min_y << "\n";
						load_mandelbrot(min_x, max_y, max_x, min_y, zoom/100);
						break;
					
					case SDLK_c: // center on a point
						double x, y;
						std::cout << "center on : \n";
						std::cin >> x >> y;
						std::cout << "centering on : (" << x << "," << y << ")\n";
						center_on(x, y);
						break;
					
					case SDLK_KP_PLUS:
						// save the center of the window : 
						get_center(&c_x, &c_y);
						zoom /= 1.2;
						// put again the center : 
						center_on(c_x, c_y);
						break;

					case SDLK_KP_MINUS:
						// save the center of the window : 
						get_center(&c_x, &c_y);
						zoom *= 1.2;
						// put again the center : 
						center_on(c_x, c_y);
						break;

					default:
						std::cout << "evt : " << e.key.keysym.sym << std::endl;
						break;
				}
				break;

			case SDL_MOUSEWHEEL:
				// save the center of the window : 
				get_center(&c_x, &c_y);
				int scroll;
				scroll = e.wheel.y;
				if 		( scroll == 1  ) zoom /= 1.05;
				else if ( scroll == -1 ) zoom *= 1.05;
				// put again the center :
				center_on(c_x, c_y);
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
	setColor(0);
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
			if(actual_grad >= 0)	grad = std::to_string(zoom*actual_grad).substr(0, 4);
			else					grad = std::to_string(zoom*actual_grad).substr(0, 5);
			if(center_y <-H()/2+30)	text(x - 4, y + 11, grad.c_str(), font);
			else 					text(x - 4, y - 25, grad.c_str(), font);
		}

		x = min(max(int(center_x + W()/2), 0), W());
		y = int(center_y) % unit_cy + i*unit_cy;

		this->line(	x - 5, y, x + 5, y); // vertical

		// === vertical graduations
		actual_grad = int(i - graduation_count - 1) - int(center_y / unit_cy);
		if(actual_grad != 0) {
			if(actual_grad >= 0)	grad = std::to_string(-zoom*actual_grad).substr(0, 5);
			else					grad = std::to_string(-zoom*actual_grad).substr(0, 4);
			if(center_x > W()/2-60)	text(x - 46, y-8, grad.c_str(), font);
			else 					text(x + 18, y-8, grad.c_str(), font);
		}
	}

}

void SDLComplexe::addComplexe(const Complexe c)					{ cList.push_back(c); 				 }
void SDLComplexe::addComplexe(const double re, const double im)	{ cList.push_back(Complexe(re, im)); }
void SDLComplexe::addComplexe(const double re)					{ cList.push_back(Complexe(re)); 	 }

void SDLComplexe::displayComplexes(){
	if (cList.size() == 0) return;
	bool color = divergence.size() != 0;
	for (int i = 0 ; i < int(cList.size()) ; i++){
		// == load the complex
		Complexe current = cList[i];
		double x, y;
		complexe_to_pixel(current, &x, &y);
		if(x < W() && x > 0 && y < H() && y > 0){
			// == display the complex
			if (color)	setColor(divergence[i], 0, 0);
			else 		setColor(255/10, 0, 0);
			this->point(x, y);
		}
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

void SDLComplexe::load_mandelbrot(double min_re, double min_im, double max_re, double max_im,double precision){

	precision = fabs(precision);
	// display top progression bar
	std::cout << "[------------------------|------------------------|------------------------|-------------------------]\n[" << std::flush;
	int prog = 0;
	for(double re = min_re; re <= max_re; re += precision){
		// incement the progression bar
		if(prog < (re -min_re)*100/(max_re - min_re)){
			std::cout << "*" << std::flush;
			prog++;
		}
		for(double im = min_im; im <= max_im; im += precision){
			Complexe z(re, im);
			int n = compute_mandelbrot(z);
			if(n <= 3) continue;
			addComplexe(z);
			// std::cout << n << " " << std::endl;
			divergence.push_back(n);
		}
	}
	std::cout << "]\n";
}

int SDLComplexe::compute_mandelbrot(Complexe c){
	Complexe z;
	int n = 0;
	while (n++ < it_max - 1 && z.distance(Complexe(0)) < 2) z = z*z + c;
	return n;
}

void SDLComplexe::complexe_to_pixel(Complexe c, double *x, double *y){
	*x = W()/2 + center_x + c.getRe()/zoom * unit_cx;
	*y = H()/2 + center_y - c.getIm()/zoom * unit_cy;
}

void SDLComplexe::pixel_to_complexe(double x, double y, Complexe *c){
	c->setRe((x - W()/2 - center_x)*zoom/unit_cx);
	c->setIm(-(y - H()/2 - center_y)*zoom/unit_cy);
}

void SDLComplexe::pixel_to_complexe(double x, double y, double *Re, double *Im){
	*Re = (x - W()/2 - center_x)*zoom/unit_cx;
	*Im = -(y - H()/2 - center_y)*zoom/unit_cy;
}

void SDLComplexe::center_on(double x, double y){
	center_x = -x*unit_cx/zoom;
	center_y = 	y*unit_cy/zoom;
}

void SDLComplexe::get_center(double*x, double*y){
	*x = -zoom*center_x/unit_cx;
	*y =  zoom*center_y/unit_cy;
}

void SDLComplexe::draw_center(){
	setColor(255, 0, 0);
	point(W()/2, H()/2, 5); // mark the center of the screen
	line(0, H()/2, W(), H()/2);
	line(W()/2, 0, W()/2, H());
}