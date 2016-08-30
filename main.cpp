#include <stdio.h>
//#include <iostream>
#include <cstdlib>
#include <math.h>
#include "allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_image.h"
#include "allegroStart.h"
#include "iprocessing.h"



void point(unsigned char *pt, int xx, int yy,int r, int g, int b);

allegroStart mA(800,600);
ALLEGRO_DISPLAY *okno = mA.openWindow();
ALLEGRO_BITMAP  *bitmapa = mA.openBitmap(800,600);
ALLEGRO_BITMAP  *bitmapa_tlo = mA.openBitmap(800,600);
ALLEGRO_KEYBOARD_STATE klawisz;
ALLEGRO_LOCKED_REGION *lr;
unsigned char *ptr;




int main(int argc, char **argv)
{

    iprocessing ip(800,600);
//ip.ustaw_filter('a', 5, 5);
//ip.ustaw_filter('b', 5, 5);
//ip.ustaw_filter('c', 5, 5);
//ip.ustaw_filter('d', 5, 5);
//ip.ustaw_filter('e', 5, 5);
//ip.ustaw_filter('f', 5, 5);
//ip.ustaw_filter('g', 5, 5);
//ip.ustaw_filter('h', 5, 5);
//ip.ustaw_filter('i', 5, 5);

ip.ustaw_filter('j', 10, 10);
ip.showf();


	bitmapa_tlo = al_load_bitmap("fotka.bmp");
  //  al_draw_bitmap(bitmapa_tlo,0,0,0);

    bitmapa = ip.imageproces(bitmapa_tlo, bitmapa);

    while( !al_key_down( & klawisz, ALLEGRO_KEY_ESCAPE ) )    {

        bitmapa = ip.imageproces(bitmapa_tlo, bitmapa);
  //  ip.zwieksz_dk(3);


        lr = al_lock_bitmap(bitmapa, ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_WRITEONLY);
        ptr = (unsigned char *)lr->data;

   //     al_clear_to_color(al_map_rgba( 0, 0,0,0));
   //    al_draw_bitmap(bitmapa_tlo,0,0,0);
 //       point(ptr, 50,50,250,250,250);

        al_draw_bitmap(bitmapa,0,0,0);
        al_unlock_bitmap(bitmapa);

        al_flip_display();
        al_get_keyboard_state( & klawisz );
        al_rest(0.004);
	}


	return 0;
}



void point(unsigned char *pt, int xx, int yy,int r, int g, int b)
{

    if (xx<mA.screenW && yy<mA.screenH && xx>0 && yy>0) {
        int pixel;
        pixel = xx+yy*mA.screenW;
        pt[pixel*4] = r;
        pt[pixel*4+1] = g;
        pt[pixel*4+2] = b;
        pt[pixel*4+3] = 250;
    }
}


