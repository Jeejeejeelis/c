
// Cargo: what the vessel is carrying
struct cargo {
    const char *title;
    int quantity;
    double weight;
};

struct truck {
	char *name;
	double length;
	double weight;
	struct cargo crg;
};

// Define the vessel structure here

struct vessel create_vessel(const char *name, double length, double depth,
			    struct cargo crg);

void print_vessel(const struct vessel *ship);
