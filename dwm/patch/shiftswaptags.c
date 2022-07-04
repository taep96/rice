/* swaps "tags" (all the clients) with the next/prev tag. */
void
shiftswaptags(const Arg *arg)
{
	Arg shifted;
	shifted.ui = selmon->tagset[selmon->seltags];

	if (arg->i > 0) /* left circular shift */
		shifted.ui = ((shifted.ui << arg->i) | (shifted.ui >> (NUMTAGS - arg->i)));
	else /* right circular shift */
		shifted.ui = ((shifted.ui >> -arg->i) | (shifted.ui << (NUMTAGS + arg->i)));
	swaptags(&shifted);
}
