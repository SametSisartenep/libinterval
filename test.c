#include <u.h>
#include <libc.h>
#include "interval.h"

char *
yn(int n)
{
	return n == 0? "no": "yes";
}

void
usage(void)
{
	fprint(2, "usage: %s\n", argv0);
	exits("usage");
}

void
main(int argc, char *argv[])
{
	Interval *a, *b;

	ARGBEGIN{
	default: usage();
	}ARGEND;
	if(argc != 0)
		usage();

	a = mkinterval(20, 30);
	b = mkinterval(25, 60);
	print("a before b:\t%s\n", yn(a->before(a, b)));
	print("a equals b:\t%s\n", yn(a->equals(a, b)));
	print("a overlaps b:\t%s\n", yn(a->overlaps(a, b)));
	print("a meets b:\t%s\n", yn(a->meets(a, b)));
	print("a during b:\t%s\n", yn(a->during(a, b)));
	print("a intersects b:\t%s\n", yn(a->intersects(a, b)));
	rminterval(a);
	rminterval(b);

	exits(nil);
}
