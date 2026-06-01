struct Hashing{
    string s;
    int n;
    int primes;
    vector<ll> hashPrimes = {1000000009, 100000007};
    const ll base = 31;
    vector<vector<ll>> hashValues;
    vector<vector<ll>> powersOfBase;
    vector<vector<ll>> inversePowersOfBase;
    Hashing(string a){
        primes = hashPrimes.size();
        hashValues.resize(primes);
        powersOfBase.resize(primes);
        inversePowersOfBase.resize(primes);
        s = a;
        n = s.length(); 
        for(int i = 0; i < primes; i++) {
            powersOfBase[i].resize(n + 1);
            inversePowersOfBase[i].resize(n + 1);
            
            //powersOfBase[i][j] --> powers of the (base^j) % hashPrimes[i]
            powersOfBase[i][0] = 1;
            for(int j = 1; j <= n; j++){
                powersOfBase[i][j] = mod_mul(base,powersOfBase[i][j - 1],hashPrimes[i]);
            }
            
            //inversePowersOfBase[i][j] --> modular multiplicative inverse of powers of bases (base^j)
            inversePowersOfBase[i][n] = binpow(powersOfBase[i][n], hashPrimes[i]-2);
            for(int j = n - 1; j >= 0; j--){
                inversePowersOfBase[i][j] = mod_mul(inversePowersOfBase[i][j + 1], base, hashPrimes[i]);
            } 
        }
        
        //hashValues[i][j] --> prefix hashes from [0,j] % hashPrimes[i]
        for(int i = 0; i < primes; i++) {
            hashValues[i].resize(n);
            for(int j = 0; j < n; j++){
                hashValues[i][j] = mod_mul((s[j] - 'a' + 1),powersOfBase[i][j],hashPrimes[i]);
                    hashValues[i][j] = mod_add(hashValues[i][j],(j > 0 ? hashValues[i][j - 1] : 0LL),hashPrimes[i]);
            }
        }
    }
    vector<ll> substringHash(int l, int r){
        vector<ll> hash(primes);
        for(int i = 0; i < primes; i++){
            ll val1 = hashValues[i][r];
            ll val2 = l > 0 ? hashValues[i][l - 1] : 0LL;
            hash[i] = mod_mul(mod_sub(val1, val2, hashPrimes[i]), inversePowersOfBase[i][l], hashPrimes[i]);
        }
        return hash;
    }
};
