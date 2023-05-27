typedef struct Interval Interval;
struct Interval
{
	uvlong t0, t1;
	uvlong ∆t;	/* duration */

	int (*before)(Interval*, Interval*);
	int (*equals)(Interval*, Interval*);
	int (*overlaps)(Interval*, Interval*);
	int (*meets)(Interval*, Interval*);
	int (*during)(Interval*, Interval*);
	int (*intersects)(Interval*, Interval*);
};

Interval *mkinterval(uvlong, uvlong);
void rminterval(Interval*);
