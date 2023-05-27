/*
 * for reference:
 * - James F. Allen, Maintaining Knowledge about Temporal Intervals, CACM November 1983, Vol. 26, No. 11
 * - https://www.ncbi.nlm.nih.gov/pmc/articles/PMC6188649/
 */
#include <u.h>
#include <libc.h>
#include "interval.h"

static int
interval_before(Interval *i, Interval *ii)
{
	return i->t1 < ii->t0;
}

static int
interval_equals(Interval *i, Interval *ii)
{
	return i->t0 == ii->t0 &&
		i->t1 == ii->t1;
}

static int
interval_overlaps(Interval *i, Interval *ii)
{
	return i->t0 < ii->t0 &&
		i->t1 > ii->t0 &&
		i->t1 < ii->t1;
}

static int
interval_meets(Interval *i, Interval *ii)
{
	return i->t1 == ii->t0;
}

static int
interval_during(Interval *i, Interval *ii)
{
	return (i->t0 > ii->t0 && i->t1 <= ii->t1) ||
		(i->t0 >= ii->t0 && i->t1 < ii->t1);
}

static int
interval_intersects(Interval *i, Interval *ii)
{
	return i->equals(i, ii) ||
		i->overlaps(i, ii) ||
		ii->overlaps(ii, i) ||
		i->during(i, ii) ||
		ii->during(ii, i);
}

Interval *
mkinterval(uvlong t0, uvlong t1)
{
	Interval *i;

	assert(t0 <= t1);

	i = malloc(sizeof(Interval));
	if(i == nil)
		sysfatal("mkinterval: %r");

	i->t0 = t0;
	i->t1 = t1;
	i->∆t = t1-t0;
	i->before = interval_before;
	i->equals = interval_equals;
	i->overlaps = interval_overlaps;
	i->meets = interval_meets;
	i->during = interval_during;
	i->intersects = interval_intersects;

	return i;
}

void
rminterval(Interval *i)
{
	free(i);
}
