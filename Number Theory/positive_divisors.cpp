ll divisors[1000002];
    memset(divisors,0,sizeof(divisors));
    for(ll i=1;i<=1000001;i++)
        for(ll j=i;j<=1000001;j+=i)
            ++divisors[j];