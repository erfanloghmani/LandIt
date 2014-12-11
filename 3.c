/*
 * main.c
 *
 *  Created on: Nov 9, 2014
 *      Author: Rmin
 */

#include <stdio.h>
#include <math.h>
#include <gtk/gtk.h>
#include <stdlib.h>
GtkWidget *window, *darea;
int windowWidth = 500, windowHeight = 500;
double x=15, y=1;
double dt = 1;
double posX[100] = {0};
double posY[100] = {0};
double velX[100] = {0};
double velY[100] = {0};
int n;
int p=0;
void draw2();
//double distance(double x1, double y1, double x2, double y2);
//void screenClick(GtkWidget *widget, GdkEventButton *event);
int draw(GtkWidget *widget, cairo_t *cr);
/*void mouseMove(GtkWidget *widget, GdkEventMotion *event);
  void cueMove(GtkWidget* widget, GdkEventMotion* event, int* number);
  void cueRelease(GtkWidget* widget, GdkEventButton* event, int* number);

  double timeInterval;
  int gTimerID = 0;
#define eps 1e-3

double distance(double x1, double y1, double x2, double y2) { // get two points in 2D and return their distance
return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void cueMove(GtkWidget *widget, GdkEventMotion *event, int *number) { // function that call when mouse moved after clicking on the ball that number is number and before releasing the mouse
printf("!!!!!!!!!!!    %d\n",*number);
printf("Cue Move : %lf %lf \n",event->x, event->y);
x[*number] = event->x;
y[*number] = event->y;
gtk_widget_queue_draw(darea);
}

void cueRelease(GtkWidget *widget, GdkEventButton *event, int *number) { // function that call when mouse released after clicking on the ball that its number is number
g_signal_handlers_disconnect_by_func(widget, G_CALLBACK(cueMove), number); // disconnect signal of mouse moving for ball that number is number
g_signal_handlers_disconnect_by_func(widget, G_CALLBACK(cueRelease), number); // // disconnect signal of mouse release for ball that number is number
g_signal_connect(G_OBJECT(widget), "motion-notify-event",
G_CALLBACK(mouseMove), NULL);	// connect default signal of Mouse moving on window
printf("Cue Release : %lf %lf \n",event->x, event->y);
x[*number] = event->x;
y[*number] = event->y;
gtk_widget_queue_draw(darea);
}

int number;
void screenClick(GtkWidget *widget, GdkEventButton *event) {
printf("Screen Clicked : %f %f\n", event->x, event->y);
int i;
for (i = 0; i < 2; i++)
if (distance(x[i], y[i], event->x, event->y) < 15) {	// if mouse clicked on ball with number i
printf("BALL NUMBER : %d\n",i);
number = i;
g_signal_handlers_disconnect_by_func(widget, G_CALLBACK(mouseMove),
NULL);	// disconnect signal of default mouse moving
g_signal_connect(G_OBJECT(widget), "motion-notify-event",
G_CALLBACK(cueMove), &number);	// connect signal of Mouse Moving for ball with number i
g_signal_connect(G_OBJECT(widget), "button-release-event",
G_CALLBACK(cueRelease), &number); // connect signal of releasing mouse for ball with number i

}
gtk_widget_queue_draw(darea);	// Tell drawing area draw itself
}

void mouseMove(GtkWidget *widget, GdkEventMotion *event) {
printf("Mouse Moved : %f %f\n", event->x, event->y);
//	x=event->x;
//	y=event->y;
//	gtk_widget_queue_draw(darea);
}*/

int draw(GtkWidget *widget, cairo_t *cr) {
	// widget = A widget that draw signal happened for it (darea)
	// cr = An object that use for draw something on drawing area
	printf("DRAWWWWW\n");
	//	cairo_set_source_rgb(cr, 0, 1, 0);	// Set color of rectangle
	//	cairo_rectangle(cr, 0, 0, windowWidth, windowHeight);	// Set rectangle in cr
	//	cairo_fill(cr);	// Draw rectangle in drawing area
//	cairo_surface_t *image = cairo_image_surface_create_from_png("bg.png"); // create image from png file
//	cairo_set_source_surface(cr, image, 0, 0);	// set position of image
//	cairo_paint(cr); // paint image on drawing area
//	cairo_surface_destroy(image);
	cairo_rectangle(cr, 0, 0, windowWidth, windowHeight);	// Set rectangle in cr
	cairo_set_source_rgb(cr, 0.1, 0.1, 0);	// Set color of rectangle
	cairo_fill(cr);	// Draw rectangle in drawing area

	{
		int i;
		for(i = 0 ; i < n ; i++){
			cairo_surface_t *image = cairo_image_surface_create_from_png("ball.png"); 
			cairo_set_source_surface(cr, image, posX[i] - 15, posY[i] - 15);	
			cairo_paint(cr); // paint image on drawing area
			cairo_surface_destroy(image);	// destroy image that creates before
		}
	}
	return 0;	// tell drawing area that drawing was successful
}

void draw2(){
	/*
	if(x<500-15){
		p=1;
		printf("!");
		x++;
		y++;
		gtk_widget_queue_draw(darea);
	}*/
	int i;
	for(i = 0 ; i < n ; i++){
		posX[i] += velX[i] * dt;	
		posY[i] += velY[i] * dt;	
	}	
	gtk_widget_queue_draw(darea);


}

void addRandom(){
	posX[n] = 0;
	posY[n] = rand()  % windowHeight;
	velX[n] = 10;
	velY[n] = 0;
	n ++;

}
int main(int argc, char** argv) {
	setbuf(stdout, NULL);		// Set buffer

	gtk_init(&argc, &argv);		// Tell compiler We have to use gtk

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);	// Declare Window
	darea = gtk_drawing_area_new();					// Declare Drawing Area

	gtk_widget_set_size_request(GTK_WIDGET(window), windowWidth, windowHeight);	// Set Size of Window
	gtk_window_set_title(GTK_WINDOW(window), "Airport");// Set Title for window
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);// Set Position of Window
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);// Set Fixed Size for window

	gtk_container_add(GTK_CONTAINER(window), darea);// Add drawing area to window

	/** PROPAGATION **/
	gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);	// For Screen Click
	//	gtk_widget_add_events(window, GDK_BUTTON_MOTION_MASK);	// Drag when pressing
	//	gtk_widget_add_events(window, GDK_BUTTON_RELEASE_MASK); // Drop when pressing
	//	gtk_widget_add_events(window, GDK_POINTER_MOTION_MASK);	// Mouse Move

	// Run gtk_main_quit when window destroyed
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit),
			NULL);

	// Run screenClick when press on the window
	g_signal_connect(G_OBJECT(window), "button-press-event",
			G_CALLBACK(draw2), NULL);

	// Run draw function when drawing area want to draw
	g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(draw), NULL);

	// Run mouseMove function when mouse moved
	//	g_signal_connect(G_OBJECT(window), "motion-notify-event",
	//			G_CALLBACK (mouseMove), NULL);
	g_timeout_add(10, (GSourceFunc) draw2,NULL);
	g_timeout_add(1000, (GSourceFunc) addRandom,NULL);
/*	n = 1;
	posX[0] = 20;
	posY[0] = 20;
	velX[0] = 10;
	velY[0] = 10;
*/
	gtk_widget_set_app_paintable(window, TRUE);

	gtk_widget_show_all(window); // Show window
	gtk_main(); // Infinite Loop that check signals until program exits

	return 0;
}
