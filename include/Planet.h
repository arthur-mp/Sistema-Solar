#ifndef PLANET_H
#define PLANET_H


class Planet
{

    int raio;
    double r;
    double g;
    double b;

    public:
        Planet(int rai, double R, double G, double B){
            raio=rai;
            r = R;
            g = G;
            b = B;
        };

        virtual ~Planet();

    protected:

    private:
};

#endif // PLANET_H
