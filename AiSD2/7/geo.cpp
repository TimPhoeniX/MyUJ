bool SegmentsIntersect(p1,p2,p3,p4)
{
	auto d1 = Direction(p3,p4,p1);
	auto d2 = Direction(p3,p4,p2);
	auto d3 = Direction(p1,p2,p3);
	auto d4 = Direction(p1,p2,p4);
	if( ((d1 >0 && d2 < 0) || (d1 < 0 && d2 >0)) && ((d3 >0 && d4 <0) || (d3<0 && d4 > 0))) return true;
	else if(d1==0 && OnSegment(p3,p4,p1)) return true;
	else if(d2==0 && OnSegment(p3,p4,p2)) return true;
	else if(d3==0 && OnSegment(p1,p2,p3)) return true;
	else if(d4==0 && OnSegment(p1,p2,p4)) return true;
	return false;
}

double Direction(pi,pj,pk)
{
	return (pk-pi)X(pj-pi);
}

bool OnSegment(pi,pj,pk)
{
	return ( min(pi.x,pj.x) <= pk.x <= max(pi.x,pj.x) && min(pi.y,pj.y) <= pk.y <= max(pi.y,pj.y) );
}