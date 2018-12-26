//
// Created by Tenton on 12/23/2018.
//


#include <pthread.h>
#include "../zenvm.h"
#include "../instructions.h"



unsigned int window_height = 200;
unsigned int window_width = 200;
char *window_title = "Window";

#if __linux__

#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *grid;

static void  print_hello(GtkWidget *widget, gpointer data) {
  g_print ("Hello World\n");
}


void zen_window() {
    switch (operand_2) {
        // show window
        case 0:  
            gtk_window_set_title(GTK_WINDOW(window), window_title);  
            gtk_window_set_default_size(GTK_WIDGET(window), window_width, window_height);
            gtk_container_set_border_width (GTK_CONTAINER (window), 10);
            //gtk_container_add (GTK_CONTAINER (window), grid);
       
            g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK(gtk_main_quit), NULL); 

            gtk_widget_show_all(window); 
            if(!g_thread_supported()) {
                g_thread_init(NULL);
            }

            gdk_threads_init();  

            g_thread_create((GThreadFunc)print_hello, NULL, FALSE, NULL);
          
            gdk_threads_enter();
            gtk_main ();
            gdk_threads_leave();
           
            break;

        // set window title
        case 1:
            window_title = local_data_seg[operand_3].value;
            break;

        // set window height
        case 2:
            window_height = local_data_seg[operand_3].value;
            break;
        
        // set window width
        case 3:
            window_width = local_data_seg[operand_3].value;
            break;
    }
}


void zen_button() {
    GtkWidget *button;
    button = gtk_button_new_with_label("button 1");

    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 10, 0, 1, 1);
    //gtk_container_add (GTK_CONTAINER (grid), button);
    gtk_widget_show(button);

    switch (operand_2) {
        case 0:
            break;
    }
}


void zen_ins_gui(int argc, char** argv) {
    // initial graphic user interface
    if (window == NULL) {
        gtk_init (NULL, NULL);
        window = gtk_window_new (GTK_WINDOW_TOPLEVEL);  
        grid = gtk_grid_new ();
        gtk_container_add (GTK_CONTAINER (window), grid);
         
    }
    
    switch (operand_1) {
        // window
        case 0:
            zen_window();
            break;

        // button
        case 1:
            zen_button();
            break;
    }
}


#elif _WIN32

#include <windows.h>

void zen_ins_gui(int argc, char** argv) {
    MessageBox(NULL, "Sorry, we haven't support running GUI programs on Windows Yet.", "Zen Virtual Machine", MB_OK);
}
    
#endif

/*
Window
    gui 0 0 0 ;show window
    gui 0 1 'title'
    gui 0 2 200  ;height
    gui 0 3 400  ;width

Button
    gui 1 0 0  ;add button
    gui 1 1 "title"
    gui 1 2 50
    gui 1 3 100
    gui 1 4 x
    gui 1 5 y
*/