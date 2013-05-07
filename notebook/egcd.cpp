// when res = extended_gcd(a,b), gcd(a,b) = a*res.F + b*res.S;
pair<ll, ll> extended_gcd(ll a, ll b) {
	if (a%b == 0) return mp(0, 1);
	pair<ll, ll> temp = extended_gcd(b, a%b);
	return mp(temp.S, temp.F - a/b*temp.S);
}
