#define DIM 3

class Particle{
    public:
        std::vector<double> position;
        std::vector<double> velocity;
        double mass;

        void update(std::vector<double> pos, std::vector<double> vel){
            this.position = pos;
            this.velocity = vel;
        }

}