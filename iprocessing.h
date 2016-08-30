class iprocessing {
    private:
//       ALLEGRO_COLOR kolor[100];
        float filter[10][10];
        int **buf1;
        int filterW, filterH;
        int imageW, imageH;
        float ile_p;
        float dkolor;
        unsigned char *ptrb;
        unsigned char *ptrb_dest;
   //     ALLEGRO_BITMAP *bmap;

    public:
        iprocessing(int, int);
        ~iprocessing();
        void showf();
        void ustaw_filter(char, int, int);
        ALLEGRO_BITMAP* imageproces(ALLEGRO_BITMAP *, ALLEGRO_BITMAP *);
        void czytaj_pixel(int, int, unsigned char &, unsigned char &, unsigned char &);
        void point(int, int, int, int, int);
        void zwieksz_dk(float);
};

