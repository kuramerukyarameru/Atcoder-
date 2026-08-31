//AIが書いたコード　もちろんatcoder等では利用しません
いちじ的に載せます。

template<class S,auto op,auto e>
struct segtree{
    int n;
    vector<S> seg;

    segtree(int N){
        n=1;
        while(n<N)n*=2;
        seg.resize(2*n,e);
    }

    void set(int i,S x){
        i+=n;
        seg[i]=x;

        while(i>1){
            i>>=1;
            seg[i]=op(seg[i*2],seg[i*2+1]);
        }
    }

    S get(int i){
        return seg[n+i];
    }

    S prod(int l,int r){
        S L=e,R=e;

        l+=n;
        r+=n;

        while(l<r){
            if(l&1)L=op(L,seg[l++]);
            if(r&1)R=op(seg[--r],R);

            l>>=1;
            r>>=1;
        }

        return op(L,R);
    }

    S all_prod(){
        return seg[1];
    }

    template<class F>
    int max_right(int l,F f){
        if(l==n)return n;

        l+=n;
        S sm=e;

        do{
            while((l&1)==0)l>>=1;

            if(!f(op(sm,seg[l]))){
                while(l<n){
                    l*=2;

                    if(f(op(sm,seg[l]))){
                        sm=op(sm,seg[l]);
                        l++;
                    }
                }

                return l-n;
            }

            sm=op(sm,seg[l]);
            l++;

        }while((l&-l)!=l);

        return n;
    }

    template<class F>
    int min_left(int r,F f){
        if(r==0)return 0;

        r+=n;
        S sm=e;

        do{
            --r;

            while(r>1 && (r&1))r>>=1;

            if(!f(op(seg[r],sm))){
                while(r<n){
                    r=r*2+1;

                    if(f(op(seg[r],sm))){
                        sm=op(seg[r],sm);
                        --r;
                    }
                }

                return r+1-n;
            }

            sm=op(seg[r],sm);

        }while((r&-r)!=r);

        return 0;
    }
};
