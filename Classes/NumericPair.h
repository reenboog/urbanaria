//
//  NumericPair.h
//  urbanaria
//
//  Created by reenboog on 11.06.14.
//
//

#ifndef __urbanaria__NumericPair__
#define __urbanaria__NumericPair__

class NumericPair {
public:
//    enum NumericPairApplyResult {
//        NPAR_Normal,
//        NPAR_ValueChanged,
//        NPAR_Overflow
//    };
    
    virtual ~NumericPair() {
        
    }

    NumericPair(int lower, int higher): lower(lower), higher(higher) {
        
    }
    
    NumericPair(): NumericPair(0, 0) {
        
    }
    
    int getLower() const {
        return this->lower;
    }
    
    void setLower(int lower) {
        this->lower = lower;
    }
    
    int getHigher() const {
        return this->higher;
    }
    
    void setHigher(int higher) {
        this->higher = higher;
    }
    
    int apply(int value) {
        this->lower += value;
        
        if(this->lower == this->higher) {
            this->higher++;
            this->lower = 0;
            
            return value;
        } else if(this->lower > this->higher) {
            int diff = this->lower - this->higher;
            this->higher -= diff;
            this->lower = 0;
            
            return -diff;
        }
        
        return 0;
    }
    
private:
    NumericPair(const NumericPair &src);
    NumericPair& operator =(const NumericPair &src);
private:
    int lower;
    int higher;
};

#endif /* defined(__urbanaria__NumericPair__) */
