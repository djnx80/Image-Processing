#include <iostream>
#include <cstdio>
#include <string>
#include "allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_image.h"
#include "iprocessing.h"

//usingnamespace std;
using namespace std;
iprocessing::iprocessing(int iX, int iY)
{
    imageW = iX;
    imageH = iY;
   // dynamic allocation
    buf1 = new int*[imageW];
    for(int i = 0; i < imageW; ++i)
    buf1[i] = new int[imageH];
}

iprocessing::~iprocessing()
{
    for(int i = 0; i < imageW; ++i)
    delete [] buf1[i];
    delete [] buf1;
}

void iprocessing::showf()
{
    cout <<filterW<<" "<<filterH<<"\n";
    for (int i = 0; i<filterH; i++)  {
        for (int j = 0; j<filterW; j++)  {
            cout <<filter[i][j]<<" ";
        }
        cout <<"\n";
    }
}

void iprocessing::ustaw_filter(char tryb, int fW, int fH)
{
    filterW = fW;
    filterH = fH;
    float ff[5][5];
    float ff1[9][9];

    dkolor=0;

    if (tryb == 'a')    {
        cout <<"blur\n";
        ile_p=5;
        float ff[5][5] = {
            {1,0,0,0,0},
            {0,1,1,1,0},
            {0,0,1,0,0},
            {0,1,1,1,0},
            {0,0,0,0,1} };
    }

    if (tryb == 'b')    {
        cout <<"sharpen\n";
        ile_p=2;
        float ff[5][5] = {
            {0,0,-1,0,0},
            {0,0,-1,0,0},
            {-1,-1,8,-1,-1},
            {0,0,-1,0,0},
            {0,0,-1,0,0} };
    }

    if (tryb == 'c')    {
        cout <<"edges\n";
        ile_p=1;
        dkolor=0;
        float ff[5][5] = {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {-1,-1,2,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0} };
    }

    if (tryb == 'd')    {
        cout <<"edges 2\n";
        ile_p=1;
        float ff[5][5] = {
            {-1,-1,-1,-1,-1},
            {-1,1,1,1,-1},
            {-1,1,8,1,-1},
            {-1,1,1,1,-1},
            {-1,-1,-1,-1,-1} };
    }

    if (tryb == 'e')    {
        cout <<"edges 3\n";
        ile_p=1;
        float ff[5][5] = {
            {0,0,0,0,0},
            {0,1,1,1,0},
            {0,1,-7,1,0},
            {0,1,1,1,0},
            {0,0,0,0,0} };
    }

    if (tryb == 'f')    {
        cout <<"emboss \n";
        ile_p=1;
        dkolor=64;
        float ff[5][5] = {
            {0, 0, 0,0,0},
            {0,-1,-1,0,0},
            {0,-1, 0,1,0},
            {0, 0, 1,1,0},
            {0, 0, 0,0,0} };
    }

    if (tryb == 'g')    {
        cout <<"emboss 2\n";
        ile_p=1;
        float ff[5][5] = {
            {-1,-1,-1,-1, 0},
            {-1,-1,-1, 0, 1},
            {-1,-1, 0, 1, 1},
            {-1, 0, 1, 1, 1},
            { 0, 1, 1, 1, 1} };
    }

    if (tryb == 'h')    {
        cout <<"grey scale\n";
        ile_p=1;
        float ff[5][5] = {
            {1, 0, 0, 0, 1},
            {0,-1, 0,-1, 0},
            {0, 0, 1, 0, 0},
            {0,-1, 0,-1, 0},
            {1, 0, 0, 0, 1}};
    }

    if (tryb == 'i')    {
        cout <<"dont know\n";
        ile_p=1;
        float ff[5][5] = {
            {0, 0, 1, 1, 0},
            {1, 1, 1, 1, 0},
            {1, 1, -15, 1, 1},
            {0, 1, 1, 1, 1},
            {0, 1, 1, 0, 0}};
    }

// dziala na tablicy ff1, trzeba pozmieniac w petlach nizej
    if (tryb == 'j')    {
        cout <<"10 x 10\n";
        ile_p=1;
        dkolor=0;
        float ff1[9][9] = {
            {0, 0, 0, 0,  1, 0, 0, 0, 0},
            {0, 0, 0, 0,  1, 0, 0, 0, 0},
            {0, 0, 0, 0,  1, 0, 0, 0, 0},
            {0, 0, 0, 0,  1, 0, 0, 0, 0},
            {1, 1, 1, 1,-16, 1, 1, 1, 1},
            {0, 0, 0, 0,  1, 0, 0, 0, 0},
            {0, 0, 0, 0,  1, 0, 0, 0, 0},
            {0, 0, 0, 0,  1, 0, 0, 0, 0},
            {0, 0, 0, 0,  1, 0, 0, 0, 0}};
    }


    for (int i = 0; i<filterH; i++)  {
        for (int j = 0; j<filterW; j++)  {
            filter[i][j]=ff[i][j];
        }
    }

}

void iprocessing::zwieksz_dk(float dk)
{
        dkolor=dkolor+dk;

}

ALLEGRO_BITMAP* iprocessing::imageproces(ALLEGRO_BITMAP *bmap, ALLEGRO_BITMAP *bmap_dest)
{
    ALLEGRO_COLOR tkolor;
    unsigned char r,g,b;
    float rr,gg,bb;
    ALLEGRO_LOCKED_REGION *alr;
    ALLEGRO_LOCKED_REGION *alrd;

    alr = al_lock_bitmap(bmap, ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_READWRITE);
    ptrb = (unsigned char *)alr->data;

    alrd = al_lock_bitmap(bmap_dest, ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_WRITEONLY);
    ptrb_dest = (unsigned char *)alrd->data;


    for (int x=1; x<imageW-15; x++)    {
        for (int y=1; y<imageH-15; y++)    {

      //      czytaj_pixel(x,y,r,g,b);
            if (r>0 || g>0 || b>0)
            {
   //             cout <<x<<" "<<y<<" "<<(int)r<<"  "<<(int)g<<" "<<(int)b<<"\n";
    //            getchar();
   //             point(x,y,(int)r, (int)g, (int)b);
 //                   point(x,y,100,100,100);
            }
            rr=0; gg=0; bb=0;
            for (int fx=0; fx<filterW; fx++)    {
                for (int fy=0; fy<filterH; fy++)    {
                    czytaj_pixel(x+fx,y+fy,r,g,b);
                    rr=rr+((float)r*filter[fx][fy]);
                    gg=gg+((float)g*filter[fx][fy]);
                    bb=bb+((float)b*filter[fx][fy]);
                }
            }
            rr=(rr/ile_p)+dkolor;
            gg=(gg/ile_p)+dkolor;
            bb=(bb/ile_p)+dkolor;
            if (rr>255) rr=255;
            if (rr<0)   rr=0;
            if (gg>255) gg=255;
            if (gg<0)   gg=0;
            if (bb>255) bb=255;
            if (bb<0)   bb=0;

            point(x,y,(int)rr, (int)gg, (int)bb);
        }
   //                     cout <<x<<" "<<(int)r<<"  "<<(int)g<<" "<<(int)b<<"\n";
    }
        al_unlock_bitmap(bmap);
        al_unlock_bitmap(bmap_dest);

    return bmap_dest;
}

void iprocessing::czytaj_pixel(int px, int py, unsigned char &r, unsigned char &g, unsigned char &b)
{
 //   cout <<"a";
        int pixel;
        pixel = px+py*imageW;
        r = ptrb[pixel*4];
        g = ptrb[pixel*4+1];
        b = ptrb[pixel*4+2];
//        ptr_to_bitmap[pixel*4+3];
}

void iprocessing::point(int xx, int yy,int rr, int gg, int bb)
{
    if (rr<0) rr=0;
    if (rr>255) rr=255;

    if (xx<imageW && yy<imageH && xx>0 && yy>0) {
        int pixel;
        pixel = xx+yy*imageW;
        ptrb_dest[pixel*4] = rr;
        ptrb_dest[pixel*4+1] = gg;
        ptrb_dest[pixel*4+2] = bb;
        ptrb_dest[pixel*4+3] = 250;
    }
}

